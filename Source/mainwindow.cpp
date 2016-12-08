#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Scheduler");                                                  //Изменение названия окна
    this->setFixedSize(800,620);                                                        //Установка фиксированного размера окна

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdate()));
    timer->start(1000);

    dateFormat1 = "dd.MM.yyyy";
    selectedDate = QDate::currentDate();                                                //Установка начальной даты

    ui->pushButtonDelete->setDisabled(true);                                            //"Выключение" кнопок "Удалить" и "Уведомления"
    ui->actionDelete->setDisabled(true);
    ui->pushButtonNotify->setDisabled(true);

    mod = new QSqlQueryModel;

    connOpen();                                                                         //Вызов метода открытия файла базы данных
    tableUpdate(selectedDate.toString(dateFormat1));                                    //Вызов метода обновления таблицы базы данных на экран
}

MainWindow::~MainWindow()
{
    connClose();                                                                        //Вызов метода закрытия файла базы данных
    delete ui;
}

void MainWindow::timeUpdate()                                                           //Метод обновления текущего времени в строке состояния окна
{
    QDateTime time = QDateTime::currentDateTime();
    QString time_text = time.toString("ddd - dd MMMM yyyy hh:mm:ss");
    ui->statusBar->showMessage(time_text);
}

void MainWindow::on_menuExit_triggered()                                                //Действие кнопки меню "Выход":
{
    close();                                                                                //выход из программы
}

void MainWindow::on_menuAdd_triggered()                                                 //Действие кнопки меню "Добавить":
{
    addWindow add(selectedDate);                                                            //вызов окна добавления события
    add.setModal(true);
    add.exec();

    show();
    connClose();
    connOpen();
    tableUpdate(selectedDate.toString(dateFormat1));                                        //обновление списка событий в главном окне
}

void MainWindow::on_pushButtonAdd_clicked()                                             //Действие кнопки "Добавить"
{
    on_menuAdd_triggered();
}

void MainWindow::on_menuNotify_triggered()                                              //Действие кнопки меню "Уведомления":
{
    notifyWindow ntf(clPlan);                                                               //вызов окна настройки уведомлений
    ntf.setModal(true);
    ntf.exec();

    show();
    connClose();
    connOpen();
    tableUpdate(selectedDate.toString(dateFormat1));                                        //обновление списка событий в главном окне
}

void MainWindow::on_pushButtonNotify_clicked()                                          //Действие кнопки "Уведомления"
{
    on_menuNotify_triggered();
}

void MainWindow::connOpen()                                                             //Метод открытия файла базы данных
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QDir::currentPath() + "/schedule.sqlite");
    mydb.open();
}

void MainWindow::connClose()                                                            //Метод закрытия файла базы данных
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

void MainWindow::tableUpdate(QString date)                                              //Метод обновления списка событий из базы данных
{
    qry = new QSqlQuery(mydb);
    qry->prepare("select * from plans where Дата='"+date+"' order by Время");
    qry->exec();
    mod->setQuery(*qry);

    ui->tableView->setModel(mod);

    ui->tableView->setColumnWidth(0,67);                                                //Установка размера таблицы в окне
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(2,550);
    ui->tableView->setColumnWidth(3,70);
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)                           //Метод получения даты, выбранной пользователем в календаре
{
    selectedDate = date;
    tableUpdate(selectedDate.toString(dateFormat1));
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)                         //Метод получения события, выбранного пользователем в таблице
{
    clPlan = ui->tableView->model()->data(index).toString();
    ui->pushButtonDelete->setDisabled(false);                                           //"Включение" кнопок "Удалить" и "Уведомления"
    ui->actionDelete->setDisabled(false);
    ui->pushButtonNotify->setDisabled(false);
}

void MainWindow::on_actionDelete_triggered()                                            //Действие кнопки меню "Удалить":
{
    QSqlQuery qry;
    qry.prepare("delete from plans where Событие='"+clPlan+"'");                            //удаление записи из базы данных
    qry.exec();
    tableUpdate(selectedDate.toString(dateFormat1));
    ui->pushButtonDelete->setDisabled(true);                                                //"выключение" кнопок "Удалить" и "Уведомления"
    ui->actionDelete->setDisabled(true);
    ui->pushButtonNotify->setDisabled(true);
}

void MainWindow::on_pushButtonDelete_clicked()                                          //Действие кнопки "Удалить"
{
    on_actionDelete_triggered();
}

void MainWindow::on_actionToday_triggered()                                             //Действие кнопки меню "Сегодня":
{
    selectedDate = QDate::currentDate();                                                    //выбрать активной датой сегодня
    ui->calendarWidget->setSelectedDate(selectedDate);
    tableUpdate(selectedDate.toString(dateFormat1));
}

void MainWindow::on_actionTomorrow_triggered()                                          //Действие кнопки меню "Завтра":
{
    selectedDate = QDate::currentDate();
    selectedDate = selectedDate.addDays(1);                                                 //выбрать активной датой завтра
    ui->calendarWidget->setSelectedDate(selectedDate);
    tableUpdate(selectedDate.toString(dateFormat1));
}
