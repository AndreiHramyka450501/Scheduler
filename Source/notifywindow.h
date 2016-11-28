#ifndef NOTIFYWINDOW_H
#define NOTIFYWINDOW_H

#include <QDialog>

namespace Ui {
class notifyWindow;
}

class notifyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit notifyWindow(QWidget *parent = 0);
    ~notifyWindow();

private slots:
    void on_pushButtonCancel_clicked();

private:
    Ui::notifyWindow *ui;
};

#endif // NOTIFYWINDOW_H
