#pragma once

#include "qwidget.h"

#include "ui_SubForm.h"
#include "../../lifecycle/LifeCycleWidget.h" 

const char subpage[] = "subpage";
class SubPage : public LifeCycleWidget<Mode_SingleTop, subpage> {

public:
    SubPage(QWidget* parent);
    ~SubPage();

private:
    Ui::SubForm ui;
};

