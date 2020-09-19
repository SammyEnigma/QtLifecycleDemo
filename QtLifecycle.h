#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtLifecycle.h"

#include "lifecycle/FragmentManager.h"

class QtLifecycle : public QWidget
{
    Q_OBJECT

public:
    QtLifecycle(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtLifecycleClass ui;
    FragmentManager* fragmentManager;
};
