#pragma once

#include "../../lifecycle/Impl.h"

#include "ui_SubForm2.h"

struct SubPage2VmView : public BaseView<Ui::SubForm2> {

    void setupUi(QWidget* parent) override;
};

struct SubPage2VmPrivate : public ImplPrivate {
    Q_DECLARE_PUBLIC(SubPage2Vm);

    void init() override;
    void bindView(QWidget* parent) override;

    SubPage2VmView view;
};