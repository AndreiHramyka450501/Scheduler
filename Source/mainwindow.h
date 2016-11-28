#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QTimer>
#include <QDateTime>
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

private slots:
    void on_menuExit_triggered();

    void on_menuAdd_triggered();

    void on_pushButtonAdd_clicked();

    void on_pushButtonNotify_clicked();

    void on_menuNotify_triggered();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
};

#endif // MAINWINDOW_H
