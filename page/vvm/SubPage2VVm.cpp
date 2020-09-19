#include "SubPage2VVm.h"
#include "SubPage2VVm_p.h"

SubPage2VVm::SubPage2VVm(QWidget* parent)
    : LifeCycleWidget(*new SubPage2VVmPrivate, parent) {
    Q_D(SubPage2VVm);
    d->init();
}

SubPage2VVm::~SubPage2VVm() {
}

void SubPage2VVmPrivate::init() {
    Q_Q(SubPage2VVm);
    bindView(q);
}

void SubPage2VVmPrivate::clickedGotoPage3() {
    Q_Q(SubPage2VVm);
    q->navigateTo("subpage3");
    q->finish();
}

void SubPage2VVmPrivate::clickedBack() {
    Q_Q(SubPage2VVm);
    q->navigateBack();
}
