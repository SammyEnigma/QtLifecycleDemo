#pragma once

#include "LiveData.h"
#include "LiveDataDefaultConverter.h"

#include <qcheckbox.h>

static QCheckBox* castCheckBoxWithCheck(QWidget* widget) {
    auto checkbox = dynamic_cast<QCheckBox*>(widget);
    Q_ASSERT_X(checkbox != nullptr, "checkboxnotify", "cannot cast widget");
    return checkbox;
}

template<typename T>
static void checkbox_statechanged(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castCheckBoxWithCheck(widget), &QCheckBox::stateChanged, [=](int state) {
        liveData->setData(state);
    });
}