#include "momrobot.h"
#include "ui_momrobot.h"
#include "textreader.h"
#include <QDebug>

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

void momRobot::on_textButton_clicked()
{

    QString filePath = QFileDialog::getOpenFileName(this,"Open File", "","Plain Text File (*.txt)");
    textReader* reader = new textReader(filePath);
    reader->getIndex();
    reader->getData();
}
