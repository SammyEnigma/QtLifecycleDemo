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
        observerBlocking = false;
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

    void operator^=(const T& d) {
        data = d;
        observerBlocking = true;
        dataChanged();
        observerBlocking = false;
    }

    const T& operator()() const {
        return data;
    }

    template<typename F>
    void observe(F fun) {
        connect(this, &LiveDataWrapper::dataChanged, [=] {
            if (!observerBlocking) {
                fun();
            }
        });

        connect(this, &LiveDataWrapper::viewChanged, [=] {
            if (!observerBlocking) {
                fun();
            }
        });
    }

    template<typename W, typename F>
    void observe(W* w, F fun) {
        connect(this, &LiveDataWrapper::dataChanged, w, [=] {
            if (!observerBlocking) {
                fun();
            }
        });

        connect(this, &LiveDataWrapper::viewChanged, w, [=] {
            if (!observerBlocking) {
                fun();
            }
        });
    }

    template<typename D>
    void setData(const D& d) {
        viewDataConverter(data, d);
        viewChanged();
    }

    void publishBlock() {
        observerBlocking = true;
    }

    void publishUnBlock() {
        observerBlocking = false;
    }

private:
    T data;
    QList<QWidget*> widgets;
    const char* propertyName;
    bool observerBlocking;
};