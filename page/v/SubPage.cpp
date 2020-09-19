#include "SubPage.h"

#include <qevent.h>
#include <qdebug.h>

SubPage::SubPage(QWidget* parent) : LifeCycleWidget(parent) {
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, [&] {
        navigateTo("subpage2");
        finish();
    });

    connect(ui.back, &QPushButton::clicked, [&] {
        navigateBack();
    });
}

SubPage::~SubPage() {
}


