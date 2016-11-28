#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include "mainwindow.h"

namespace Ui {
class addWindow;
}

class addWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addWindow(QDate &startDate,QWidget *parent = 0);
    ~addWindow();

private slots:
    void on_pushButtonCancel_clicked();

    void on_textPlan_textChanged();

    void on_pushButtonOK_clicked();

private:
    Ui::addWindow *ui;
    QString date, time, plan, category;

};

#endif // ADDWINDOW_H
