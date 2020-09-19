#pragma once

#include "LiveData.h"
#include "LiveDataDefaultConverter.h"

#include <qcombobox.h>

static QComboBox* castComboBoxWithCheck(QWidget* widget) {
    auto comboBox = dynamic_cast<QComboBox*>(widget);
    Q_ASSERT_X(comboBox != nullptr, "comboBoxnotify", "cannot cast widget");
    return comboBox;
}

template<typename T>
static void comboBox_activated(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), &QComboBox::activated, [&](int index) {
        liveData->setData(index);
    });
}

template<typename T>
static void comboBox_currentIndexChanged(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), &QComboBox::currentIndexChanged, [&](int index) {
        liveData->setData(index);
    });
}

template<typename T>
static void comboBox_currentTextChanged(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), &QComboBox::currentTextChanged, [&](const QString& text) {
        liveData->setData(text);
    });
}

template<typename T>
static void comboBox_editTextChanged(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), &QComboBox::editTextChanged, [&](const QString& text) {
        liveData->setData(text);
    });
}

template<typename T>
static void comboBox_highlighted(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), &QComboBox::highlighted, [&](int index) {
        liveData->setData(index);
    });
}

template<typename T>
static void comboBox_textActivated(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), &QComboBox::textActivated, [&](const QString& text) {
        liveData->setData(text);
    });
}

template<typename T>
static void comboBox_textHighlighted(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), &QComboBox::textHighlighted, [&](const QString& text) {
        liveData->setData(text);
    });
}