#include "CultrueThingsNamer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CultrueThingsNamer w;
    
    w.show();
    return a.exec();
}
