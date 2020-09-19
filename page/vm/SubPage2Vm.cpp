#include "SubPage2Vm.h"
#include "SubPage2Vm_p.h"

SubPage2Vm::SubPage2Vm(QWidget* parent)
    : LifeCycleWidget(*new SubPage2VmPrivate, parent)
{
    Q_D(SubPage2Vm);
    d->init();
}

SubPage2Vm::~SubPage2Vm() {
}

void SubPage2VmView::setupUi(QWidget* parent) {
    ui->setupUi(parent);
}

void SubPage2VmPrivate::init() {
    Q_Q(SubPage2Vm);
    bindView(q);
}

void SubPage2VmPrivate::bindView(QWidget* parent) {
    Q_Q(SubPage2Vm);
    view.setupUi(parent);

    connect(view()->pushButton, &QPushButton::clicked, [=] {
        q->navigateTo("subpage3");
        q->finish();
    });

    connect(view()->back, &QPushButton::clicked, [=] {
        q->navigateBack();
    });
}