#pragma once

#include "../../lifecycle/LifeCycleWidget.h"

const char subpage2vm[] = "subpage2";
struct SubPage2VmPrivate;
class SubPage2Vm : public LifeCycleWidget<Mode_Standard, subpage2vm> {
    Q_DECLARE_PRIVATE(SubPage2Vm)

public:
    SubPage2Vm(QWidget* parent);
    ~SubPage2Vm();
};

