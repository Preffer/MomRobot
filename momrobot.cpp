#include "momrobot.h"
#include "ui_momrobot.h"
#include <QDebug>

momRobot::momRobot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::momRobot)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
}

momRobot::~momRobot()
{
    delete ui;
}

void momRobot::on_textButton_clicked()
{

    textFilePath = QFileDialog::getOpenFileName(this,"Open File", "","文本文件 (*)");
    ui->textFilePath->setText(textFilePath);
}

void momRobot::on_excelButton_clicked()
{
    excelFilePath = QFileDialog::getOpenFileName(this,"Open File", "","Excel文件 (*.xlsx *.xls)");
    ui->excelFilePath->setText(excelFilePath);
}

void momRobot::on_startButton_clicked()
{
    QTime start =  QTime::currentTime ();
    try{
        txtReader = (QSharedPointer<textReader>) new textReader(textFilePath);
        xlsReader = (QSharedPointer<excelReader>) new excelReader(excelFilePath);
        xlsReader->exec(txtReader->exec());
    }
    catch(std::invalid_argument& e){
        QMessageBox::critical (this, "出现错误", e.what());
        return;
    }
    QTime end = QTime::currentTime();
    QMessageBox::information(this, "操作完成", QString("操作完成!  用时 %1 ms \n已保存到 %2").arg(start.msecsTo(end)).arg(xlsReader->saveFilePath));
}
