#include "dialog.h"
#include <QApplication>
#include "dos.h"
#include"QFileDialog"
#include<vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog dlg;
    dlg.show();
    return a.exec();
}
