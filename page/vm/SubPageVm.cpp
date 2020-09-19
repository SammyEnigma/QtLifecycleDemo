#include "SubPageVm.h"
#include "SubPageVm_p.h"

#include <qevent.h>
#include <qdebug.h>

SubPageVm::SubPageVm(QWidget* parent) 
    : LifeCycleWidget(*new SubPageVmPrivate, parent)
{
    Q_D(SubPageVm);
    d->init();
}

SubPageVm::~SubPageVm() {
}

void SubPageVmView::setupUi(QWidget* parent) {
    ui->setupUi(parent);
}

void SubPageVmPrivate::init() {
    Q_Q(SubPageVm);
    bindView(q);
}

void SubPageVmPrivate::bindView(QWidget* parent) {
    Q_Q(SubPageVm);
    view.setupUi(parent);

    connect(view()->pushButton, &QPushButton::clicked, [=] {
        q->navigateTo("subpage2");
        q->finish();
    });

    connect(view()->back, &QPushButton::clicked, [=] {
        q->navigateBack();
    });
}