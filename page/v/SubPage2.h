#pragma once

#include "ui_SubForm2.h"
#include "../../lifecycle/LifeCycleWidget.h"

const char subpage2[] = "subpage2";
class SubPage2 : public LifeCycleWidget<Mode_Standard, subpage2> {
public:
    SubPage2(QWidget* parent);

private:
    Ui::SubForm2 ui;
};

