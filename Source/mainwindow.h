#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QTimer>
#include <QDateTime>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "addwindow.h"
#include "notifywindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void timeUpdate();
    void connOpen();
    void connClose();
    void tableUpdate(QString date);

private slots:
    void on_menuExit_triggered();
    void on_menuAdd_triggered();
    void on_pushButtonAdd_clicked();
    void on_pushButtonNotify_clicked();
    void on_menuNotify_triggered();
    void on_calendarWidget_clicked(const QDate &date);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButtonDelete_clicked();

    void on_actionDelete_triggered();

private:
    Ui::MainWindow *ui;
    QDate selectedDate;
    QString dateFormat1;
    QString clPlan;
    QTimer *timer;
    QSqlDatabase mydb;
    QSqlQuery *qry;
    QSqlQueryModel *mod;
    QSortFilterProxyModel *tab;
    bool calendarClicked;

};

#endif // MAINWINDOW_H
