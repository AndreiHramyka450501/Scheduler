#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>
#include <QDateTime>
#include <QDate>
#include <QTime>

namespace Ui {
class addWindow;
}

class addWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addWindow(QWidget *parent = 0);
    ~addWindow();

private slots:
    void on_pushButtonCancel_clicked();

private:
    Ui::addWindow *ui;
};

#endif // ADDWINDOW_H
