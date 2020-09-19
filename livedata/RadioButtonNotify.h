#pragma once

#include "LiveData.h"
#include "LiveDataDefaultConverter.h"

#include <qradiobutton.h>

static QRadioButton* castRadiobuttonWithCheck(QWidget* widget) {
    auto radioButton = dynamic_cast<QRadioButton*>(widget);
    Q_ASSERT_X(radioButton != nullptr, "radioButtonnotify", "cannot cast widget");
    return radioButton;
}

template<typename T>
static void radiobutton_clicked(QWidget* widget, LiveData<T>* livedata) {
    QObject::connect(castRadiobuttonWithCheck(widget), &QRadioButton::clicked, [=](bool checked) {
        livedata->setData(checked);
    });
}