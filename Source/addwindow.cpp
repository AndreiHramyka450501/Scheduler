#include "addwindow.h"
#include "ui_addwindow.h"

addWindow::addWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавление события");

    const QDate date = QDate::currentDate();
    const QTime time = QTime::currentTime();

    ui->dateEdit->setMinimumDate(date);
    ui->timeEdit->setTime(time);

}

addWindow::~addWindow()
{
    delete ui;
}

void addWindow::on_pushButtonCancel_clicked()
{
    close();
}
