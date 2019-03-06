#ifndef IMPORT_H
#define IMPORT_H

#include <QDialog>
#include<pe.h>
namespace Ui {
class Import;
}

class Import : public QDialog
{
    Q_OBJECT

public:
    explicit Import(QWidget *parent = nullptr);
    ~Import();

private slots:
    void on_pushButton_clicked();



private:
    Ui::Import *ui;
    Pefile pefile;
};

#endif // IMPORT_H
