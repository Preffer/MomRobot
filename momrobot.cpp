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

void momRobot::updateConfig()
{
    txtReader->keyName = ui->txtKeyName->text();
    txtReader->valueName = ui->txtValueName->text();
    txtReader->dataPrefix = ui->txtDataPrefix->text();
    txtReader->valueOffset = ui->txtValueOffset->text().toInt();

    xlsReader->keyName = ui->excelKeyName->text();
    xlsReader->valueName = ui->excelValueName->text();
    xlsReader->dateName = ui->excelDateName->text();
    xlsReader->keyLength = ui->excelKeyLength->text().toInt();
    xlsReader->headerWithin = ui->excelHeaderWithin->text().toInt();
    xlsReader->newMonthBound = ui->excelNewMonthBound->text().toInt();
}

void momRobot::processData()
{
    QTime start =  QTime::currentTime ();
    try{
        txtReader = (QSharedPointer<textReader>) new textReader(textFilePath);
        xlsReader = (QSharedPointer<excelReader>) new excelReader(excelFilePath);
        this->updateConfig();

        connect(xlsReader.data(), SIGNAL(progressBarInit(int, int)), this->ui->progressBar, SLOT(setRange(int, int)));
        connect(xlsReader.data(), SIGNAL(progressBarUpdate(int)), this->ui->progressBar, SLOT(setValue(int)));
        xlsReader->exec(txtReader->exec());
    }
    catch(std::invalid_argument& e){
        QMessageBox::critical (this, "出现错误", e.what());
        return;
    }
    QTime end = QTime::currentTime();
    QMessageBox::information(this, "操作完成", QString("操作完成!  用时 %1 ms \n已保存到 %2").arg(start.msecsTo(end)).arg(xlsReader->saveFilePath));
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
    QFuture<void> future = QtConcurrent::run(this, &momRobot::processData);
}

momRobot::~momRobot()
{
    delete ui;
}
