#include "momrobot.h"
#include "ui_momrobot.h"
#include "textreader.h"
#include "excelreader.h"
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

    textFilePath = QFileDialog::getOpenFileName(this,"Open File", "","Plain Text File (*)");
    ui->textFilePath->setText(textFilePath);
}

void momRobot::on_excelButton_clicked()
{
    excelFilePath = QFileDialog::getOpenFileName(this,"Open File", "","Microsoft Office (*.xlsx *.xls)");
    ui->excelFilePath->setText(excelFilePath);
}

void momRobot::on_startButton_clicked()
{
    QSharedPointer<textReader> txtReader = (QSharedPointer<textReader>) new textReader(textFilePath);
    QSharedPointer<excelReader> xlsReader = (QSharedPointer<excelReader>) new excelReader(excelFilePath);
    xlsReader->exec(txtReader->exec());
}
