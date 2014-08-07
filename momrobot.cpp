#include "momrobot.h"
#include "ui_momrobot.h"
#include <QDebug>

momRobot::momRobot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::momRobot)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    //connect signals
    connect(this, SIGNAL(throwException(QString)), this, SLOT(receiveException(QString)));
    connect(this, SIGNAL(complete(int)), this, SLOT(showComplete(int)));
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
    //this is the core function to process the data
    QTime start =  QTime::currentTime ();
    try{
        txtReader = (QSharedPointer<textReader>) new textReader(textFilePath);
        xlsReader = (QSharedPointer<excelReader>) new excelReader(excelFilePath);

        connect(xlsReader.data(), SIGNAL(progressBarInit(int, int)), this->ui->progressBar, SLOT(setRange(int, int)));
        connect(xlsReader.data(), SIGNAL(progressBarUpdate(int)), this->ui->progressBar, SLOT(setValue(int)));

        this->updateConfig();
        xlsReader->exec(txtReader->exec());
    }
    /* have to use exception to transfer the error message
     * because some exceptions occur in its constructor,
     * so I can't connect it to slot directly
     */
    catch(std::invalid_argument& e){
        emit throwException(QString(e.what()));
        return;
    }
    QTime end = QTime::currentTime();
    emit complete(start.msecsTo(end));
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
    QtConcurrent::run(this, &momRobot::processData);
    ui->startButton->setEnabled(false);
    ui->startButton->setText("处理中...");
}

void momRobot::receiveException(QString exception)
{
    QMessageBox::critical(this, "出现错误", exception);
}

void momRobot::showComplete(int ms)
{
    QMessageBox::information(this, "操作完成", QString("操作完成!  用时 %1 ms \n已保存到 %2").arg(ms).arg(xlsReader->saveFilePath));
    ui->startButton->setEnabled(true);
    ui->startButton->setText("开始！");
}

momRobot::~momRobot()
{
    delete ui;
}
