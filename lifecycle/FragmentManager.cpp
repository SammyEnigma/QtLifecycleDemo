#include "FragmentManager.h"

#include <qdebug.h>

FragmentManager::FragmentManager(QStackedWidget* container)
    : QObject(container)
    , container(container)
    , onNewPageSetEvent(nullptr)
{
}

void FragmentManager::navigateTo(QString pageName, QVariant data) {
    Q_ASSERT_X(pageCreatorList.contains(pageName), "fragmentManager", "page not register!");
    const auto& creator = pageCreatorList.value(pageName);
    LifeCycleWidgetWrapper* widget = nullptr;
    switch (creator.launchMode) {
        case Mode_Standard:
            widget = pageCreatorList.value(pageName).creator();
            break;
        case Mode_SingleTop:
            if (!fragmentsStack.isEmpty() && fragmentsStack.last().itemName == pageName) {
                widget = fragmentsStack.last().widget;
            } else {
                widget = pageCreatorList.value(pageName).creator();
            }
            break;
        case Mode_SingleTask:
            int i = 0, j = -1;
            while (i < fragmentsStack.size()) {
                if (j != -1) {
                    auto f = fragmentsStack.at(j);
                    container->removeWidget(f.widget);
                    f.widget->deleteLater();
                    fragmentsStack.removeAt(j);
                    continue;
                }
                if (fragmentsStack.at(i).itemName == pageName) {
                    widget = fragmentsStack.at(i).widget;
                    container->setCurrentWidget(widget);
                    j = i + 1;
                }
                i++;
            }
            if (j == -1) {
                widget = pageCreatorList.value(pageName).creator();
            }
            break;
    }
    widget->setNavigateData(data);
}

void FragmentManager::replaceTo(QString pageName, QVariant data) {
    if (!fragmentsStack.isEmpty()) {
        if (!fragmentsStack.last().widget->attempClose()) {
            return;
        }
        removeLastFragment();
    }
    navigateTo(pageName, data);
}

void FragmentManager::navigateBack(QVariant data) {
    if (!fragmentsStack.isEmpty()) {
        if (!fragmentsStack.last().widget->attempClose()) {
            return;
        }
        removeLastFragment();
        if (!fragmentsStack.isEmpty()) {
            fragmentsStack.last().widget->setNavigateResultData(data);
            container->setCurrentWidget(fragmentsStack.last().widget);
        }
    }
}

void FragmentManager::printFragmentStack() {
    QStringList stackNames;
    for (const auto& f : fragmentsStack) {
        stackNames << f.itemName;
    }
    qDebug() << "current fragment stack:" << stackNames;
}

void FragmentManager::fragmentCreated(const FragmentItem& item) {
    fragmentsStack.append(item);
    if (onNewPageSetEvent != nullptr) {
        onNewPageSetEvent(item);
    }
    container->addWidget(item.widget);
    container->setCurrentWidget(item.widget);

    connect(item.widget, &LifeCycleWidgetWrapper::navigateTo, [&] (QString name, QVariant data) {
        navigateTo(name, data);
    });

    connect(item.widget, &LifeCycleWidgetWrapper::navigateBack, [&](QVariant data) {
        navigateBack(data);
    });

    connect(item.widget, &LifeCycleWidgetWrapper::finish, [&, item]() {
        for (int i = fragmentsStack.size() - 1; i >= 0; i--) {
            if (fragmentsStack.at(i).widget == item.widget) {
                if (item.widget->attempClose()) {
                    fragmentsStack.removeAt(i);
                    container->removeWidget(item.widget);
                    item.widget->deleteLater();
                }
                break;
            }
        }
    });

}

void FragmentManager::removeLastFragment() {
    auto f = fragmentsStack.takeLast();
    container->removeWidget(f.widget);
    f.widget->deleteLater();
}
