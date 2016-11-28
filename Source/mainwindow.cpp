#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Scheduler");
    this->setFixedSize(800,620);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdate()));
    timer->start(1000);

    dateFormat1 = "dd.MM.yyyy";
    selectedDate = QDate::currentDate();

    ui->pushButtonDelete->setDisabled(true);

    mod = new QSqlQueryModel;
    tab = new QSortFilterProxyModel;
    calendarClicked = false;

    connOpen();
    tableUpdate(selectedDate.toString(dateFormat1));
}

MainWindow::~MainWindow()
{
    connClose();
    delete ui;
}

void MainWindow::timeUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString time_text = time.toString("ddd - dd MMMM yyyy hh:mm:ss");
    ui->statusBar->showMessage(time_text);
}

void MainWindow::on_menuExit_triggered()
{
    close();
}

void MainWindow::on_menuAdd_triggered()
{
    addWindow add(selectedDate);
    add.setModal(true);
    add.exec();

    show();
    connClose();
    connOpen();
    tableUpdate(selectedDate.toString(dateFormat1));
}

void MainWindow::on_pushButtonAdd_clicked()
{
    on_menuAdd_triggered();
}

void MainWindow::on_menuNotify_triggered()
{
    notifyWindow ntf;
    ntf.setModal(true);
    ntf.exec();
}

void MainWindow::on_pushButtonNotify_clicked()
{
    on_menuNotify_triggered();
}

void MainWindow::connOpen()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QDir::currentPath() + "/schedule.sqlite");
    mydb.open();
}

void MainWindow::connClose()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

void MainWindow::tableUpdate(QString date)
{
    qry = new QSqlQuery(mydb);
    qry->prepare("select * from plans where Дата='"+date+"' order by Время");
    qry->exec();
    mod->setQuery(*qry);
    tab->setSourceModel(mod);

    ui->tableView->setModel(tab);

    ui->tableView->setColumnWidth(0,67);
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(2,550);
    ui->tableView->setColumnWidth(3,70);

}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    selectedDate = date;
    calendarClicked = true;
    tableUpdate(selectedDate.toString(dateFormat1));
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    clPlan = ui->tableView->model()->data(index).toString();
    ui->label->setText(clPlan);
    ui->pushButtonDelete->setDisabled(false);
}

void MainWindow::on_pushButtonDelete_clicked()
{
    QSqlQuery qry;
    qry.prepare("delete from plans where Событие='"+clPlan+"'");
    qry.exec();
    tableUpdate(selectedDate.toString(dateFormat1));
    ui->pushButtonDelete->setDisabled(true);
}
