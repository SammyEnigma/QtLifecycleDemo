#pragma once

#include "LiveData.h"
#include "LiveDataDefaultConverter.h"

#include <qprogressbar.h>

static QProgressBar* castProgressbarWithCheck(QWidget* widget) {
    auto progressbar = dynamic_cast<QProgressBar*>(widget);
    Q_ASSERT_X(progressbar != nullptr, "progressbarnotify", "cannot cast widget");
    return progressbar;
}

template<typename T>
static void progressbar_valueChanged(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castProgressbarWithCheck(widget), &QProgressBar::valueChanged, [=] (int value) {
        liveData->setData(value);
    });
}