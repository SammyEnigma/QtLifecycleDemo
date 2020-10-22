#pragma once

#include "LiveData.h"

template<typename T>
inline void viewDataConverter(T& data, const T& src) {
    data = src;
}

template<>
inline void viewDataConverter(int& data, const QString& src) {
    data = src.toInt();
}

template<>
inline void viewDataConverter(QString& data, const int& src) {
    data = QString::number(src);
}

template<>
inline void viewDataConverter(qreal& data, const QString& src) {
    data = src.toDouble();
}

template<>
inline void viewDataConverter(QString& data, const qreal& src) {
    data = QString::number(src);
}

template<>
inline void viewDataConverter(bool& data, const int& src) {
    data = (bool)src;
}

template<>
inline void viewDataConverter(int& data, const bool& src) {
    data = src ? 1 : 0;
}