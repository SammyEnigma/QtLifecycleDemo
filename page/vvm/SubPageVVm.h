#pragma once

#include "qwidget.h"

#include "../../lifecycle/LifeCycleWidget.h" 

const char subpagevvm[] = "subpage";
struct SubPageVVmPrivate;
class SubPageVVm : public LifeCycleWidget<Mode_SingleTop, subpagevvm> {
    Q_DECLARE_PRIVATE(SubPageVVm);

public:
    SubPageVVm(QWidget* parent);
    ~SubPageVVm();

};
