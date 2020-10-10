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
static void comboBox_activated_int(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), qOverload<int>(&QComboBox::activated), [=](int index) {
        liveData->setData(index);
    });
}

template<typename T>
static void comboBox_activated_str(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), qOverload<const QString&>(&QComboBox::activated), [=](int index) {
        liveData->setData(index);
    });
}

template<typename T>
static void comboBox_currentIndexChanged_int(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), qOverload<int>(&QComboBox::currentIndexChanged), [=](int index) {
        liveData->setData(index);
    });
}

template<typename T>
static void comboBox_currentIndexChanged_str(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), qOverload<const QString&>(&QComboBox::currentIndexChanged), [=](int index) {
        liveData->setData(index);
    });
}

template<typename T>
static void comboBox_currentTextChanged(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), &QComboBox::currentTextChanged, [=](const QString& text) {
        liveData->setData(text);
    });
}

template<typename T>
static void comboBox_editTextChanged(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), &QComboBox::editTextChanged, [=](const QString& text) {
        liveData->setData(text);
    });
}

template<typename T>
static void comboBox_highlighted_int(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), qOverload<int>(&QComboBox::highlighted), [=](int index) {
        liveData->setData(index);
    });
}

template<typename T>
static void comboBox_highlighted_str(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), qOverload<const QString&>(&QComboBox::highlighted), [=](int index) {
        liveData->setData(index);
    });
}

//for 5.14
template<typename T>
static void comboBox_textActivated(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), &QComboBox::textActivated, [=](const QString& text) {
        liveData->setData(text);
    });
}

//for 5.14
template<typename T>
static void comboBox_textHighlighted(QWidget* widget, LiveData<T>* liveData) {
    QObject::connect(castComboBoxWithCheck(widget), &QComboBox::textHighlighted, [=](const QString& text) {
        liveData->setData(text);
    });
}