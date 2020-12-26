#pragma once

#include "../../lifecycle/Impl.h"

#include "../../livedata/LiveData.h"

#include "../../livedata/AbstractModelHelper.h"

struct StrT {
    QString data;
    int a;
};

class ModelHelper;

class SubPageVVmView;
struct SubPageVVmPrivate : public ImplPrivate {
    Q_DECLARE_PUBLIC(SubPageVVm);

    void init() override;
    void bindView(QWidget* parent) override;
    QTableView* getTableView();

    void clickedGotoPage2();
    void clickedBack();

    void resetModel();
    void addData2Model();
    void updateModel();
    void editModel();

    void updateInThread();

    SubPageVVmView* view;

    LiveData<StrT> styleData;
    LiveData<QString> strData;
    LiveData<QString> strData2;

    ModelHelper* modelHelper;

    ~SubPageVVmPrivate() {
        delete view;
    }
};

struct ItemData {
    QString name;
    QString phone;
    int age;
    bool male;
};

class ModelHelper : public AbstractModelHelper<ItemData> {
public:
    ModelHelper(QAbstractItemView* view) : AbstractModelHelper(view) {
        getModelCaster()
            .next<QString>(BIND_COL(name))
            .next<QString>(BIND_COL(phone))
            .next<int>(BIND_COL(age))
            .next<bool>(BIND_COL(male))
            ;
    }

protected:
    QStringList getHeaders() override {
        return QStringList() << u8"姓名" << u8"电话" << u8"年龄" << u8"男";
    }

    void onHeaderCreated(int colSize) override {
        tbHHeader()->resizeSection(0, 120);
    }
};
