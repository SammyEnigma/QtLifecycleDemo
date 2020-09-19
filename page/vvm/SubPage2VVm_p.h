#pragma once

#include "../../lifecycle/Impl.h"

struct SubPage2VVmView;
struct SubPage2VVmPrivate : public ImplPrivate {
    Q_DECLARE_PUBLIC(SubPage2VVm);

    void init() override;
    void bindView(QWidget* parent) override;

    void clickedGotoPage3();
    void clickedBack();

    SubPage2VVmView* view;

    ~SubPage2VVmPrivate() {
        delete view;
    }
};