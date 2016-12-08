#ifndef NOTIFYWINDOW_H
#define NOTIFYWINDOW_H

#include <QDialog>
#include <QDate>
#include <QTime>
#include "mainwindow.h"

namespace Ui {
class notifyWindow;
}

class notifyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit notifyWindow(QString &plan,QWidget *parent = 0);
    ~notifyWindow();

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonOK_clicked();

private:
    Ui::notifyWindow *ui;
    QString date,time,clPlan;
};

#endif // NOTIFYWINDOW_H
