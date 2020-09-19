#include "SubPage2.h"

SubPage2::SubPage2(QWidget* parent) : LifeCycleWidget(parent) {
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, [&] {
        navigateTo("subpage3");
    });
    
    connect(ui.back, &QPushButton::clicked, [&] {
        navigateBack();
    });
}
