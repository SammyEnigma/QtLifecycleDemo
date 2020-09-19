#pragma once

#include "../../lifecycle/LifeCycleWidget.h"

const char subpage2vvm[] = "subpage2";
struct SubPage2VVmPrivate;
class SubPage2VVm : public LifeCycleWidget<Mode_Standard, subpage2vvm> {
    Q_DECLARE_PRIVATE(SubPage2VVm)

public:
    SubPage2VVm(QWidget* parent);
    ~SubPage2VVm();
};