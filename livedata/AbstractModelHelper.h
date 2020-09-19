#pragma once

#include <qobject.h>
#include <qstandarditemmodel.h>
#include <qabstractitemview.h>
#include <functional>

template<typename T>
class AbstractModelHelpter;

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

    friend class AbstractModelHelpter<T>;

private:
    T* data;
    std::function<void()> callback;

    ItemDataEditor(T* data, std::function<void()> callback) {
        this->data = data;
        this->callback = callback;
    }
};

template<typename T>
class AbstractModelHelpter : QObject {
public:
    AbstractModelHelpter(QAbstractItemView* view)
        : QObject(view) 
        , model(new QStandardItemModel(this))
        , view(view)
    {
        view->setModel(model);
    }

    void reset() {
        model->clear();
        createHeader(getHeaders());
    }

    int append(const T& d) {
        data.append(d);
        int colSize = model->columnCount();
        QList<QStandardItem*> items;
        for (int i = 0; i < colSize; i++) {
            auto item = new QStandardItem;
            data2View(d, i, item);
            items << item;
        }
        model->appendRow(items);
        return model->rowCount() - 1;
    }

    void update() {
        int rowSize = model->rowCount();
        int colSize = model->columnCount();
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                view2Data(data[i], j, model->item(i, j));
            }
        }
    }

    ItemDataEditor<T>& editRow(int rowIndex) {
        return *new ItemDataEditor<T>(&data[rowIndex], [=] {
            rowDataReseted(rowIndex);
        });
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
            data2View(data[rowIndex], j, model->item(rowIndex, j));
        }
    }

protected:
    virtual void data2View(const T& data, int index, QStandardItem* item) = 0;
    virtual void view2Data(T& data, int index, const QStandardItem* item) {}

    virtual QStringList getHeaders() = 0;

    virtual void onHeaderCreated(int colSize) {}

protected:
    QList<T> data;
    QStandardItemModel* model;
    QAbstractItemView* view;
};