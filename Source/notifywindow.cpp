#include "notifywindow.h"
#include "ui_notifywindow.h"

notifyWindow::notifyWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notifyWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Настройка уведомлений");
}

notifyWindow::~notifyWindow()
{
    delete ui;
}

void notifyWindow::on_pushButtonCancel_clicked()
{
    close();
}
