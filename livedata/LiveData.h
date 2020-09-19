#pragma once

#include <qwidget.h>
#include <functional>

class LiveDataWrapper : public QObject {
    Q_OBJECT

signals:
    void dataChanged();
    void viewChanged();
};

template<typename T>
static QVariant noconvt(const T& src) {
    return src;
}

template<typename T, typename D>
void viewDataConverter(T& t, const D& d);

template<typename T>
class LiveData : LiveDataWrapper {
public:
    LiveData() {
        propertyName = "text";
    }

    LiveData(const LiveData&) = delete;
    LiveData& operator=(const LiveData&) = delete;

    LiveData& operator+(QWidget* w) {
        widgets << w;
        return *this;
    }

    LiveData& operator+(const char* propertyName) {
        this->propertyName = propertyName;
        return *this;
    }

    LiveData& operator+(QVariant(*converter)(const T&)) {
        for (auto w : widgets) {
            connect(this, &LiveDataWrapper::dataChanged, this, [&, w, converter] {
                w->setProperty(this->propertyName, converter(data));
            });
        }
        return *this;
    }

    LiveData& operator+(void(*notify)(QWidget*, LiveData<T>*)) {
        for (auto w : widgets) {
            notify(w, this);
        }
        return *this;
    }

    LiveData& operator+(LiveData<T>& other) {
        other.observe([&] {
            this->operator=(other.data);
        });
        return *this;
    }

    void operator=(const T& d) {
        data = d;
        dataChanged();
    }

    const T& operator()() const {
        return data;
    }

    template<typename F>
    void observe(F fun) {
        connect(this, &LiveDataWrapper::dataChanged, fun);
        connect(this, &LiveDataWrapper::viewChanged, fun);
    }

    template<typename W, typename F>
    void observe(W* w, F fun) {
        connect(this, &LiveDataWrapper::dataChanged, w, fun);
        connect(this, &LiveDataWrapper::viewChanged, w, fun);
    }

    template<typename D>
    void setData(const D& d) {
        viewDataConverter(data, d);
        viewChanged();
    }

private:
    T data;
    QList<QWidget*> widgets;
    const char* propertyName;
};