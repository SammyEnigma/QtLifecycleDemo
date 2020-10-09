#pragma once

#include <qobject.h>
#include <qstandarditemmodel.h>
#include <qabstractitemview.h>
#include <functional>

#include <qtableview.h>
#include <qheaderview.h>

template<typename T>
class AbstractModelHelper;

template<typename T>
class ItemDataEditor : QObject {
public:
    ItemDataEditor() = delete;

    T& operator()() {
        return *data;
    }

    void apply() {
        callback();
        deleteLater();
    }

    friend class AbstractModelHelper<T>;

private:
    T* data;
    std::function<void()> callback;

    ItemDataEditor(T* data, std::function<void()> callback) {
        this->data = data;
        this->callback = callback;
    }
};

#define BIND_COL(member) [](auto& data) -> auto& { return data.member; }

template<typename T>
class ModelCaster {
public:
    template<typename E>
    ModelCaster& next(E&(*ptr)(T&), Qt::ItemDataRole role = Qt::DisplayRole, bool editable = true) {
        setters << [=](T& data, QStandardItem* item) {
            if (ptr != nullptr) {
                item->setData(ptr(data), role);
            }
            item->setEditable(editable);
        };

        getters << [=](T& data, const QStandardItem* item) {
            if (ptr != nullptr) {
                ptr(data) = item->data(role).value<E>();
            }
        };

        return *this;
    }

    ModelCaster& next(bool editable = true) {
        setters << [=](T& data, QStandardItem* item) {
            item->setEditable(editable);
        };

        getters << [=](T& data, const QStandardItem* item) {};

        return *this;
    }

    friend class AbstractModelHelper<T>;

private:
    QList<std::function<void(T&, QStandardItem*)>> setters;
    QList<std::function<void(T&, const QStandardItem*)>> getters;
};

template<typename T>
class AbstractModelHelper : QObject {
public:
    AbstractModelHelper(QAbstractItemView* view)
        : QObject(view) 
        , model(new QStandardItemModel(this))
        , view(view)
    {
        view->setModel(model);
    }

    void reset() {
        model->clear();
        data.clear();
        createHeader(getHeaders());
    }

    int append(T& d) {
        data.append(d);
        int colSize = model->columnCount();
        QList<QStandardItem*> items;
        for (int i = 0; i < colSize; i++) {
            auto item = new QStandardItem;
            modelCaster.setters.at(i)(d, item);
            items << item;
        }
        model->appendRow(items);
        return model->rowCount() - 1;
    }

    T takeRow(int index) {
        model->removeRow(index);
        return data.takeAt(index);
    }

    T takeLast() {
        return takeRow(model->rowCount() - 1);
    }

    T takeFirst() {
        return takeRow(0);
    }

    int getRowCount() {
        return model->rowCount();
    }

    const QList<T>& getData() {
        return data;
    }

    void update() {
        int rowSize = model->rowCount();
        int colSize = model->columnCount();
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                modelCaster.getters.at(j)(data[i], model->item(i, j));
            }
        }
    }

    ItemDataEditor<T>& editRow(int rowIndex) {
        return *new ItemDataEditor<T>(&data[rowIndex], [=] {
            rowDataReseted(rowIndex);
        });
    }

    QStandardItemModel* getModel() {
        return model;
    }

    QAbstractItemView* getView() {
        return view;
    }

    template<typename V>
    V* getView() {
        return dynamic_cast<V*>(view);
    }

private:
    void createHeader(const QStringList& headers) {
        if (!headers.isEmpty()) {
            model->setColumnCount(headers.size());
            int col = 0;
            for (const auto& h : headers) {
                model->setHeaderData(col++, Qt::Horizontal, h, Qt::DisplayRole);
            }
        } else {
            model->setColumnCount(1);
        }
        onHeaderCreated(model->columnCount());
    }

    void rowDataReseted(int rowIndex) {
        int colSize = model->columnCount();
        for (int j = 0; j < colSize; j++) {
            modelCaster.setters.at(j)(data[rowIndex], model->item(rowIndex, j));
        }
    }

protected:
    virtual QStringList getHeaders() = 0;

    virtual void onHeaderCreated(int colSize) {}

    ModelCaster<T>& getModelCaster() {
        return modelCaster;
    }

    QHeaderView* tbHHeader() {
        return static_cast<QTableView*>(view)->horizontalHeader();
    }

    QHeaderView* tbVHeader() {
        return static_cast<QTableView*>(view)->verticalHeader();
    }

protected:
    QList<T> data;
    QStandardItemModel* model;
    QAbstractItemView* view;

    ModelCaster<T> modelCaster;
};

