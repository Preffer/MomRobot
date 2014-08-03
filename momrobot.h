#ifndef MOMROBOT_H
#define MOMROBOT_H

#include <QApplication>
#include <QMainWindow>

namespace Ui {
    class momRobot;
}

class momRobot : public QMainWindow
{
    Q_OBJECT

public:
    explicit momRobot(QWidget *parent = 0);
    ~momRobot();

private slots:
    void on_textButton_clicked();

    void on_excelButton_clicked();

    void on_startButton_clicked();

private:
    Ui::momRobot *ui;
    QString textFilePath;
    QString excelFilePath;
};

#endif // MOMROBOT_H
