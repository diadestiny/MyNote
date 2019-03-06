#ifndef OTHER_H
#define OTHER_H

#include <QDialog>
#include <pe.h>
namespace Ui {
class Other;
}

class Other : public QDialog
{
    Q_OBJECT

public:
    explicit Other(QWidget *parent = nullptr);
    ~Other();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Other *ui;
    Pefile pefile;
};

#endif // OTHER_H
