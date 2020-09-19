#pragma once

#include "LiveData.h"
#include "LiveDataDefaultConverter.h"

#include <qdatetimeedit.h>

static QDateTimeEdit* castDateTimeEditWithCheck(QWidget* widget) {
    auto dateTimeEdit = dynamic_cast<QDateTimeEdit*>(widget);
    Q_ASSERT_X(dateTimeEdit != nullptr, "datetimeEditnotify", "cannot cast widget");
    return dateTimeEdit;
}

template<typename T>
static void datetimeEdit_dateChanged(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castDateTimeEditWithCheck(widget), &QDateTimeEdit::dateChanged, [=](const QDate& date) {
        liveData->setData(date);
    });
}

template<typename T>
static void datetimeEdit_dateTimeChanged(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castDateTimeEditWithCheck(widget), &QDateTimeEdit::dateTimeChanged, [=](const QDateTime& date) {
        liveData->setData(date);
    });
}

template<typename T>
static void datetimeEdit_timeChanged(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castDateTimeEditWithCheck(widget), &QDateTimeEdit::timeChanged, [=](const QTime& date) {
        liveData->setData(date);
    });
}

