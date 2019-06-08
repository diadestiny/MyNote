#ifndef SECTION_H
#define SECTION_H

#include <QDialog>
#include<pe.h>
namespace Ui {
class Section;
}

class Section : public QDialog
{
    Q_OBJECT

public:
    explicit Section(QWidget *parent = nullptr);
    ~Section();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Section *ui;
    Pefile pefile;
};

#endif // SECTION_H
