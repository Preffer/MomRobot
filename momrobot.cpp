#include "momrobot.h"
#include "ui_momrobot.h"

momRobot::momRobot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::momRobot)
{
    ui->setupUi(this);
}

momRobot::~momRobot()
{
    delete ui;
}
