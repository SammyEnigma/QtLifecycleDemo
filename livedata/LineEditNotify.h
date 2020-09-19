#pragma once

#include "LiveData.h"
#include "LiveDataDefaultConverter.h"

#include <qlineedit.h>

static QLineEdit* castLineEditWithCheck(QWidget* widget) {
    auto lineEdit = dynamic_cast<QLineEdit*>(widget);
    Q_ASSERT_X(lineEdit != nullptr, "lineEditnotify", "cannot cast widget");
    return lineEdit;
}

template<typename T>
static void lineEdit_editingFinished(QWidget* widget, LiveData<T>* liveData) {
    auto lineEdit = castLineEditWithCheck(widget);
    QObject::connect(lineEdit, &QLineEdit::editingFinished, [=] {
        liveData->setData(lineEdit->text());
    });
}

template<typename T>
static void lineEdit_textChanged(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castLineEditWithCheck(widget), &QLineEdit::textChanged, [=] (const QString& text) {
        liveData->setData(text);
    });
}

template<typename T>
static void lineEdit_textEdited(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castLineEditWithCheck(widget), &QLineEdit::textEdited, [=](const QString& text) {
        liveData->setData(text);
    });
}