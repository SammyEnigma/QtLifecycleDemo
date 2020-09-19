#pragma once

#include "qwidget.h"

#include "../../lifecycle/LifeCycleWidget.h" 

const char subpagevm[] = "subpage";
struct SubPageVmPrivate;
class SubPageVm : public LifeCycleWidget<Mode_SingleTop, subpagevm> {
    Q_DECLARE_PRIVATE(SubPageVm);

public:
    SubPageVm(QWidget* parent);
    ~SubPageVm();

};

