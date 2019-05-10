#include "file.h"
#include "ui_file.h"

File::File(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::File)
{
    ui->setupUi(this);
}

File::~File()
{
    delete ui;
}

void peFileHeaderAnalyze(Pefile &pefile)
{
    QByteArray ba = pefile.name.toLatin1();
    const char *cstr = ba.data();
    FILE *fp = fopen(cstr, "rb");
    fread(&pefile.Dosheader.dosheader, sizeof(pefile.Dosheader.dosheader), 1, fp);
    fseek(fp, pefile.Dosheader.dosheader.e_lfanew, SEEK_SET);
    fread(&pefile.pesig, 4, 1,fp);
    fread(&pefile.FileHeader.fileheader, sizeof(pefile.FileHeader.fileheader), 1, fp);
    fclose(fp);
    sprintf(pefile.Signature,"%0lX", pefile.pesig);
    sprintf(pefile.FileHeader.Machine,"%04X", (pefile.FileHeader.fileheader).Machine);
    sprintf(pefile.FileHeader.NumberOfSections,"%04X", (pefile.FileHeader.fileheader).NumberOfSections);
    sprintf(pefile.FileHeader.TimeDateStamp,"%04lX", (pefile.FileHeader.fileheader).TimeDateStamp);
    sprintf(pefile.FileHeader.PointerToSymbolTable,"%04lX", (pefile.FileHeader.fileheader).PointerToSymbolTable);
    sprintf(pefile.FileHeader.NumberOfSymbols,"%04lX", (pefile.FileHeader.fileheader).NumberOfSymbols);
    sprintf(pefile.FileHeader.SizeOfOptionalHeader,"%04X", (pefile.FileHeader.fileheader).SizeOfOptionalHeader);
    sprintf(pefile.FileHeader.Characteristics,"%04X", (pefile.FileHeader.fileheader).Characteristics);
}

void File::on_pushButton_clicked()
{
    read(pefile);
    peFileHeaderAnalyze(pefile);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Member"<<"Value"<<"Member"<<"Value"<<"Member"<<"Value");
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("Signature")); //设置表格内容
    ui->tableWidget->setItem(1,0,new QTableWidgetItem("Machine"));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem("NumberOfSections"));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("TimeDateStamp"));
    ui->tableWidget->setItem(1,2,new QTableWidgetItem("PointerToSymbolTable"));
    ui->tableWidget->setItem(2,2,new QTableWidgetItem("NumberOfSymbols"));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem("SizeOfOptionalHeader"));
    ui->tableWidget->setItem(1,4,new QTableWidgetItem("Characteristics"));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(pefile.Signature));
    ui->tableWidget->setItem(1,1,new QTableWidgetItem(pefile.FileHeader.Machine));
    ui->tableWidget->setItem(2,1,new QTableWidgetItem(pefile.FileHeader.NumberOfSections));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem(pefile.FileHeader.TimeDateStamp));
    ui->tableWidget->setItem(1,3,new QTableWidgetItem(pefile.FileHeader.PointerToSymbolTable));
    ui->tableWidget->setItem(2,3,new QTableWidgetItem(pefile.FileHeader.NumberOfSymbols));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem(pefile.FileHeader.SizeOfOptionalHeader));
    ui->tableWidget->setItem(1,5,new QTableWidgetItem(pefile.FileHeader.Characteristics));

}
