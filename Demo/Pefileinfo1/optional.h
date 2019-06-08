#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <QDialog>
#include <pe.h>
namespace Ui {
class Optional;
}

class Optional : public QDialog
{
    Q_OBJECT

public:
    explicit Optional(QWidget *parent = nullptr);
    ~Optional();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Optional *ui;
    Pefile pefile;
};

#endif // OPTIONAL_H
