#ifndef MOMROBOT_H
#define MOMROBOT_H

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

private:
    Ui::momRobot *ui;
};

#endif // MOMROBOT_H
