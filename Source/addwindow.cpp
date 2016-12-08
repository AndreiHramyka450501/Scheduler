#include "addwindow.h"
#include "ui_addwindow.h"

addWindow::addWindow(QDate &startDate,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавление события");                 //Изменение названия окна

    ui->dateEdit->setDate(startDate);                           //Установка начальной даты
    ui->dateEdit->setCalendarPopup(true);
    ui->timeEdit->setTime(QTime::currentTime());                //Установка начального времени

    ui->pushButtonOK->setDisabled(true);                        //"Выключение" кнопки "ОК"
}

addWindow::~addWindow()
{
    delete ui;
}

void addWindow::on_pushButtonCancel_clicked()                   //Действие кнопки "Отмена":
{
    close();                                                        //закрыть окно добавления события
}

void addWindow::on_textPlan_textChanged()                       //Действия при изменении текста события
{
    if (ui->textPlan->toPlainText() != "")                          //если не поле пустое
    {
        plan = ui->textPlan->toPlainText();                             //занести текст поля в строку plan
        ui->pushButtonOK->setDisabled(false);                           //"включить" кнопку "ОК"
    } else                                                          //если поле пустое
    {
        ui->pushButtonOK->setDisabled(true);                            //"выключить" кнопку "ОК"
    }
}

void addWindow::on_pushButtonOK_clicked()                       //Действие кнопки "ОК":
{
    date = ui->dateEdit->date().toString("dd.MM.yyyy");             //запомнить дату, время, категорию события
    time = ui->timeEdit->time().toString("hh:mm");
    category = ui->comboBox->currentText();

    MainWindow c;                                                   //создать экземпляр главного окна приложения
    QSqlQuery qry;                                                  //занести в базу данных новую запись (событие)
    qry.prepare("insert into plans (Дата,Время,Событие,Категория) values ('"+date+"','"+time+"','"+plan+"','"+category+"')");
    qry.exec();
    c.close();

    ui->textPlan->setText("");
    close();                                                        //закрыть окно добавления события
}
