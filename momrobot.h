#ifndef MOMROBOT_H
#define MOMROBOT_H

#include "textreader.h"
#include "excelreader.h"
#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QtConcurrentRun>
#include <QTime>

namespace Ui {
    class momRobot;
}

class momRobot : public QMainWindow
{
    Q_OBJECT

public:
    explicit momRobot(QWidget *parent = 0);
    ~momRobot();

signals:
    void throwException(QString exception);
    void complete(int ms);

private slots:
    void on_textButton_clicked();

    void on_excelButton_clicked();

    void on_startButton_clicked();

    void receiveException(QString exception);

    void showComplete(int ms);

private:
    void updateConfig();
    void processData();

    Ui::momRobot *ui;
    QString textFilePath;
    QString excelFilePath;

    QSharedPointer<textReader> txtReader;
    QSharedPointer<excelReader> xlsReader;
};

#endif // MOMROBOT_H
