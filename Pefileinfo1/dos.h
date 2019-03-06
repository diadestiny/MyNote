#ifndef MYDIALOG_H
#define MYDIALOG_H
#include<pe.h>
#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MyDialog *ui;
    Pefile pefile;
};

#endif // MYDIALOG_H
