#include "mydialog2.h"
#include "ui_mydialog2.h"

mydialog2::mydialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mydialog2)
{
    ui->setupUi(this);
}

mydialog2::~mydialog2()
{
    delete ui;
}
