#include "wheelcontrol.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WheelControl w;
    w.show();

    return a.exec();
}
