#pragma once

#include "LiveData.h"

template<>
inline void viewDataConverter(QString& data, const QString& src) {
    data = src;
}

template<>
inline void viewDataConverter(int& data, const int& src) {
    data = src;
}

template<>
inline void viewDataConverter(qreal& data, const qreal& src) {
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