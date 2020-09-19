#pragma once

#include <qobject.h>
#include <functional>
#include <qhash.h>
#include <qstackedwidget.h>
#include <qvariant.h>

#include "LifeCycleWidget.h"

struct FragmentCreator {
    std::function<LifeCycleWidgetWrapper* ()> creator;
    LaunchMode launchMode;
};

struct FragmentItem {
    LifeCycleWidgetWrapper* widget;
    QString itemName;
};

class FragmentManager : public QObject {
public:
    FragmentManager(QStackedWidget* container);

    void navigateTo(QString pageName, QVariant data = QVariant());
    void replaceTo(QString pageName, QVariant data = QVariant());
    void navigateBack(QVariant data = QVariant());

    void printFragmentStack();

    template<typename... T>
    void registerPage() {
        RgHelper<T...>::registerPage(this);
    }

private:
    void fragmentCreated(const FragmentItem& item);
    void removeLastFragment();

    template<typename... T> struct RgHelper;
    template<typename T0, typename... T> 
    struct RgHelper<T0, T...> {
        static void registerPage(FragmentManager* manager) {
            manager->loadPage<T0>();
            RgHelper<T...>::registerPage(manager);
        }
    };

    template<> struct RgHelper<> {
        static void registerPage(FragmentManager*) {}
    };

    template<typename T>
    void loadPage() {
        FragmentCreator fcreator;
        fcreator.creator = [&] {
            auto t = new T(container);

            FragmentItem item;
            item.widget = t;
            item.itemName = typename T::pageName;
            fragmentCreated(item);

            return t;
        };
        fcreator.launchMode = (LaunchMode) typename T::launchMode;
        pageCreatorList.insert(typename T::pageName, fcreator);
    }

private:
    QHash<QString, FragmentCreator> pageCreatorList;
    QList<FragmentItem> fragmentsStack;

    QStackedWidget* container;
};

