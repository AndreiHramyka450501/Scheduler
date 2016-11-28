#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Scheduler");

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdate()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
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
    addWindow ad;
    ad.setModal(true);
    ad.exec();
}

void MainWindow::on_pushButtonAdd_clicked()
{
    addWindow add;
    add.setModal(true);
    add.exec();
}

void MainWindow::on_pushButtonNotify_clicked()
{
    notifyWindow ntf;
    ntf.setModal(true);
    ntf.exec();
}

void MainWindow::on_menuNotify_triggered()
{
    notifyWindow ntf;
    ntf.setModal(true);
    ntf.exec();
}
