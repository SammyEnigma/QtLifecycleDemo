#include "SubPageVVm.h"
#include "SubPageVVm_p.h"

#include "ui_SubForm.h"

#include "../../livedata/LineEditNotify.h"
#include "../../RunnableHandler.h"

struct SubPageVVmView : public BaseView<Ui::SubForm> {

    void setupUi(QWidget* parent) override {
        ui->setupUi(parent);
        //do other view init..
        ui->tableView->verticalHeader()->hide();
    }
};

QVariant srtTConvert(const StrT& src) {
    return src.data;
}

template<>
inline void viewDataConverter(StrT& data, const QString& src) {
    data.data = src;
}

void SubPageVVmPrivate::bindView(QWidget* parent) {
    view = new SubPageVVmView;
    view->setupUi(parent);

    styleData + "styleSheet" + view->ui->lineEdit + view->ui->lineEdit_3 + srtTConvert;

    strData + view->ui->lineEdit + view->ui->lineEdit_3 + noconvt + lineEdit_textChanged;

    strData2 + view->ui->lineEdit_2 + noconvt + strData;

    connect(view->ui->pushButton, &QPushButton::clicked, [=] {
        clickedGotoPage2();
    });

    connect(view->ui->back, &QPushButton::clicked, [=] {
        clickedBack();
    });

    connect(view->ui->pushButton_2, &QPushButton::clicked, [&] {
        RunnableHandler<SubPageVVmPrivate>::exec(this, &SubPageVVmPrivate::updateInThread);
    });

    connect(view->ui->btnreset, &QPushButton::clicked, [&] {
        resetModel();
    });

    connect(view->ui->btnappend, &QPushButton::clicked, [&] {
        addData2Model();
    });

    connect(view->ui->btnupdate, &QPushButton::clicked, [&] {
        updateModel();
    });

    connect(view->ui->btneditrow, &QPushButton::clicked, [&] {
        editModel();
    });
}

QTableView* SubPageVVmPrivate::getTableView() {
    return view->ui->tableView;
}
