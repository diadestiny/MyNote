#ifndef RELOCATION_H
#define RELOCATION_H

#include <QDialog>
#include<pe.h>
namespace Ui {
class Relocation;
}

class Relocation : public QDialog
{
    Q_OBJECT

public:
    explicit Relocation(QWidget *parent = nullptr);
    ~Relocation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Relocation *ui;
    Pefile pefile;
};

#endif // RELOCATION_H
