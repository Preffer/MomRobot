#include "momrobot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    momRobot w;
    w.show();

    return a.exec();
}