#include "QtLifecycle.h"

#include <qevent.h>
#include <qdebug.h>

#include "page/vvm/SubPageVVm.h"
#include "page/vvm/SubPage2VVm.h"

QtLifecycle::QtLifecycle(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, [&] {
        fragmentManager->navigateTo("subpage");
    });

    connect(ui.pushButton_2, &QPushButton::clicked, [&] {
        fragmentManager->navigateTo("subpage2");
    });

    connect(ui.printstack, &QPushButton::clicked, [&] {
        fragmentManager->printFragmentStack();
    });

    fragmentManager = new FragmentManager(ui.stackedWidget);
    fragmentManager->registerPage<SubPageVVm, SubPage2VVm>();
}


