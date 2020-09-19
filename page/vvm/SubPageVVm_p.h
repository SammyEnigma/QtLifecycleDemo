#pragma once

#include "../../lifecycle/Impl.h"

#include "../../livedata/LiveData.h"

#include <qtableview.h>

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



