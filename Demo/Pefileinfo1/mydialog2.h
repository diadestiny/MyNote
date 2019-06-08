#ifndef MYDIALOG2_H
#define MYDIALOG2_H

#include <QDialog>
#include<pe.h>

namespace Ui {
class mydialog2;
}

class mydialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit mydialog2(QWidget *parent = nullptr);
    ~mydialog2();

private:
    Ui::mydialog2 *ui;
    Pefile pefile;
};

#endif // MYDIALOG2_H
