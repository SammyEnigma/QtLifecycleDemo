#pragma once

#include "../../lifecycle/Impl.h"

#include "ui_SubForm.h"

struct SubPageVmView : public BaseView<Ui::SubForm> {

    void setupUi(QWidget* parent) override;
};

struct SubPageVmPrivate : public ImplPrivate {
    Q_DECLARE_PUBLIC(SubPageVm);

    void init() override;
    void bindView(QWidget* parent) override;

    SubPageVmView view;
};