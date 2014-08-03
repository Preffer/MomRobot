#include "momrobot.h"

int main(int argc, char *argv[])
{
    QSharedPointer<QApplication> app = (QSharedPointer<QApplication>) new QApplication(argc, argv);
    QSharedPointer<momRobot> widget = (QSharedPointer<momRobot>) new momRobot();

    widget->show();

    return app->exec();
}
