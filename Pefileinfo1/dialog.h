#ifndef DIALOG_H
#define DIALOG_H


#include <QDialog>
#include "dos.h"
#include "file.h"
#include "optional.h"
#include "pe.h"
#include "section.h"
#include "import.h"
#include "other.h"
#include "export.h"
#include"relocation.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    bool ExitFile(const QString &fileName); // 加载并打印文件
    Pefile pefile;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::Dialog *ui;
    QString curFile;
    MyDialog *mydialog;
    File *file;
    Optional *optional;
    Section *section;
    Import *import;
    Other *other;
    Export *expo;
    Relocation *reloc;
} ;



#endif // DIALOG_H

