#include "notifywindow.h"
#include "ui_notifywindow.h"

notifyWindow::notifyWindow(QString &plan,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notifyWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Настройка уведомлений");                          //Изменение названия окна

    ui->dateEdit->setMinimumDate(QDate::currentDate());                     //Установка начальной даты
    ui->dateEdit->setCalendarPopup(true);
    clPlan.append(plan);                                                    //Запись выбранного события в поле clplan

}

notifyWindow::~notifyWindow()
{
    delete ui;
}

void notifyWindow::on_pushButtonCancel_clicked()                            //Действие кнопки "Отмена":
{
    close();                                                                    //закрыть окно настройки уведомлений
}

void notifyWindow::on_pushButtonOK_clicked()                                //Действие кнопки "ОК":
{
    date = ui->dateEdit->date().toString("dd.MM.yyyy");                         //запомнить дату, время
    time = ui->timeEdit->time().toString("hh:mm");

    MainWindow m;
    QSqlQuery qry;                                                              //занести в базу данных новую запись (уведомление о выбранном событии)
    qry.prepare("insert into notifications (Событие,Дата,Время) values ('"+clPlan+"','"+date+"','"+time+"')");
    qry.exec();
    m.close();

    close();                                                                    //закрыть окно настройки уведомлений
}
