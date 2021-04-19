#pragma once

#include <qwidget.h>
#include <qvariant.h>

#include "Impl.h"

class LifeCycleWidgetWrapper : public ImplClass {
    Q_OBJECT

public:
    using ImplClass::ImplClass;

    virtual bool attempClose() {
        return true;
    }

    inline void setNavigateData(const QVariant& data) {
        this->navigateData = data;
    }

    inline void setNavigateResultData(const QVariant& data) {
        if (data.isValid()) {
            onNavigateResult(data);
        }
    }

protected:
    virtual void onNavigateResult(const QVariant& data) {};

signals:
    void navigateTo(QString pageName, QVariant data = QVariant());
    void navigateBack(QVariant data = QVariant());
    void finish();

protected:
    QVariant navigateData;
};

enum LaunchMode {
    Mode_Standard,
    Mode_SingleTask,
    Mode_SingleTop
};

template<LaunchMode M, const char* pagename>
class LifeCycleWidget : public LifeCycleWidgetWrapper {
public:
    LifeCycleWidget(ImplPrivate& pd, QWidget* parent)
        : LifeCycleWidgetWrapper(pd, parent)
        , firstShow(true) {}

    LifeCycleWidget(QWidget* parent)
        : LifeCycleWidgetWrapper(*new ImplPrivate, parent)
        , firstShow(true) {}

    enum {
        launchMode = M
    };

    static const char* pageName;

protected:
    void showEvent(QShowEvent*) override {
        if (firstShow) {
            onViewLoad();
            firstShow = false;
        } else {
            onReshow();
        }
    }

    void resizeEvent(QResizeEvent*) override {
        onResizeWindow();
    }

    void hideEvent(QHideEvent*) override {
        onHidden();
    }

protected:
    virtual void onViewLoad() {}
    virtual void onReshow() {}
    virtual void onHidden() {}
    virtual void onResizeWindow() {}

protected:
    QVariant getNavigateData(bool clear = true) {
        auto data = navigateData;
        if (clear) {
            navigateData = QVariant();
        }
        return data;
    }

private:
    bool firstShow;
};

template<LaunchMode M, const char* pagename>
const char* LifeCycleWidget<M, pagename>::pageName = pagename;