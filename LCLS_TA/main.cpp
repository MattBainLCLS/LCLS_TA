#include "LCLS_TA.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LCLS_TA w;
    w.show();
    return a.exec();
}
