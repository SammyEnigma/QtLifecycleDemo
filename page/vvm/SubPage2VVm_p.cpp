#include "SubPage2VVm.h"
#include "SubPage2VVm_p.h"

#include "ui_SubForm2.h"

struct SubPage2VVmView : public BaseView<Ui::SubForm2> {

    void setupUi(QWidget* parent) override {
        ui->setupUi(parent);
        //do other view init..
    }
};

void SubPage2VVmPrivate::bindView(QWidget* parent) {
    view = new SubPage2VVmView;
    view->setupUi(parent);

    connect(view->ui->pushButton, &QPushButton::clicked, [=] {
        clickedGotoPage3();
    });

    connect(view->ui->back, &QPushButton::clicked, [=] {
        clickedBack();
    });
}