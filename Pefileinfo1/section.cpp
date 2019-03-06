#include "section.h"
#include "ui_section.h"
Section::Section(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Section)
{
    ui->setupUi(this);
}

Section::~Section()
{
    delete ui;
}

void peSectionHeaderAnaylze(Pefile &pefile)
{
    QByteArray ba = pefile.name.toLatin1();
    const char *cstr = ba.data();
    FILE *fp = fopen(cstr, "rb");
    fread(&pefile.Dosheader.dosheader, sizeof(pefile.Dosheader.dosheader), 1, fp);
    fseek(fp, pefile.Dosheader.dosheader.e_lfanew, SEEK_SET);
    fread(&pefile.pesig, 4, 1, fp);
    fread(&pefile.FileHeader.fileheader, sizeof(pefile.FileHeader.fileheader), 1, fp);
    fseek(fp, pefile.Dosheader.dosheader.e_lfanew + 4 + sizeof(pefile.FileHeader.fileheader) + pefile.FileHeader.fileheader.SizeOfOptionalHeader, SEEK_SET);


     for (int i = 0; i < pefile.FileHeader.fileheader.NumberOfSections; i++)
        {
            fread(&pefile.Sechdr.sechdr, sizeof(pefile.Sechdr.sechdr), 1, fp);
            sprintf(pefile.Sechdr.Name[i],"%s", pefile.Sechdr.sechdr.Name);
            sprintf(pefile.Sechdr.Viradd[i],"%08lx", pefile.Sechdr.sechdr.VirtualAddress);
            sprintf(pefile.Sechdr.SizeofRawdata[i],"%08lx", pefile.Sechdr.sechdr.SizeOfRawData);
            sprintf(pefile.Sechdr.PtrRaw[i],"%08lx", pefile.Sechdr.sechdr.PointerToRawData);
            sprintf(pefile.Sechdr.Character[i],"%08lx", pefile.Sechdr.sechdr.Characteristics);
        }

        fclose(fp);
}

void Section::on_pushButton_clicked()
{
    read(pefile);
    peSectionHeaderAnaylze(pefile);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(pefile.FileHeader.fileheader.NumberOfSections);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Name"<<"VirtualAddress"<<"SizeOfRawData"
                              <<"PointerToRawData"<<"Characteristics");
        for(int i=0;i<pefile.FileHeader.fileheader.NumberOfSections;i++)
        {
             ui->tableWidget->setItem(i,0,new QTableWidgetItem(pefile.Sechdr.Name[i]));
             ui->tableWidget->setItem(i,1,new QTableWidgetItem(pefile.Sechdr.Viradd[i]));
             ui->tableWidget->setItem(i,2,new QTableWidgetItem(pefile.Sechdr.SizeofRawdata[i]));
             ui->tableWidget->setItem(i,3,new QTableWidgetItem(pefile.Sechdr.PtrRaw[i]));
             ui->tableWidget->setItem(i,4,new QTableWidgetItem(pefile.Sechdr.Character[i]));
        }

}
