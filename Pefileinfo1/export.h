#ifndef EXPORT_H
#define EXPORT_H

#include <QDialog>
#include <pe.h>
namespace Ui {
class Export;
}

class Export : public QDialog
{
    Q_OBJECT

public:
    explicit Export(QWidget *parent = nullptr);
    ~Export();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Export *ui;
    Pefile pefile;
};

#endif // EXPORT_H
