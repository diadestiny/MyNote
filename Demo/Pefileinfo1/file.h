#ifndef FILE_H
#define FILE_H

#include <QDialog>
#include <pe.h>
namespace Ui {
class File;
}

class File : public QDialog
{
    Q_OBJECT

public:
    explicit File(QWidget *parent = nullptr);
    ~File();

private slots:
    void on_pushButton_clicked();

private:
    Ui::File *ui;
    Pefile pefile;
};

#endif // FILE_H
