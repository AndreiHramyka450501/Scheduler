#include "addwindow.h"
#include "ui_addwindow.h"

addWindow::addWindow(QDate &startDate,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавление события");

    ui->dateEdit->setDate(startDate);
    ui->dateEdit->setCalendarPopup(true);
    ui->timeEdit->setTime(QTime::currentTime());

    ui->pushButtonOK->setDisabled(true);

}

addWindow::~addWindow()
{
    delete ui;
}

void addWindow::on_pushButtonCancel_clicked()
{
    close();
}

void addWindow::on_textPlan_textChanged()
{
    if (ui->textPlan->toPlainText() != "")
    {
        plan = ui->textPlan->toPlainText();
        ui->pushButtonOK->setDisabled(false);
    } else
    {
        ui->pushButtonOK->setDisabled(true);
    }
}

void addWindow::on_pushButtonOK_clicked()
{
    date = ui->dateEdit->date().toString("dd.MM.yyyy");
    time = ui->timeEdit->time().toString("hh:mm");
    category = ui->comboBox->currentText();

    MainWindow c;
    QSqlQuery qry;
    qry.prepare("insert into plans (Дата,Время,Событие,Категория) values ('"+date+"','"+time+"','"+plan+"','"+category+"')");
    qry.exec();
    c.close();

    ui->textPlan->setText("");
    close();
}
