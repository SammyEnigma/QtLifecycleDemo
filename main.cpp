#include "QtLifecycle.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtLifecycle w;
    w.show();
    return a.exec();
}
