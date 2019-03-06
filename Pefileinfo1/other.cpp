#include "other.h"
#include "ui_other.h"
#include <QMessageBox>

Other::Other(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Other)
{
    ui->setupUi(this);
}

Other::~Other()
{
    delete ui;
}

void Other::on_pushButton_clicked()
{
    read(pefile);
    QByteArray ba = pefile.name.toLatin1();
    const char *cstr = ba.data();
    FILE *fp = fopen(cstr, "rb");
    fread(&pefile.Dosheader.dosheader, sizeof(pefile.Dosheader.dosheader), 1, fp);
    fseek(fp, pefile.Dosheader.dosheader.e_lfanew, SEEK_SET);
    fread(&pefile.pesig, 4, 1, fp);
    fread(&pefile.FileHeader.fileheader, sizeof(pefile.FileHeader.fileheader), 1, fp);
    if (pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER32))
    {
        fread(&pefile.OptionalHeader.opthdr32, sizeof(pefile.OptionalHeader.opthdr32), 1,fp);
        if(pefile.OptionalHeader.opthdr32.DataDirectory[6].Size==0&&
                pefile.OptionalHeader.opthdr32.DataDirectory[6].VirtualAddress==0)
        {
            QMessageBox::warning(this, "warning", "Sorry, the file has this data.");
        }
        else
        {
            fseek(fp,getRVA(pefile,6),SEEK_SET);
            fread(&pefile.debug.deb,sizeof(pefile.debug.deb),1,fp);
            sprintf(pefile.debug.Character,"%04lx", (pefile.debug.deb).Characteristics);
            sprintf(pefile.debug.TimeDate,"%04lx",  (pefile.debug.deb).TimeDateStamp);
            sprintf(pefile.debug.MaxVer,"%04x",  (pefile.debug.deb).MajorVersion);
            sprintf(pefile.debug.MinVer,"%04x",  (pefile.debug.deb).MinorVersion);
            sprintf(pefile.debug.Type,"%04lx",  (pefile.debug.deb).Type);
            sprintf(pefile.debug.Sizeofdata,"%04lx", (pefile.debug.deb).SizeOfData);
            sprintf(pefile.debug.AddRawData,"%04lx", (pefile.debug.deb).AddressOfRawData);
            sprintf(pefile.debug.PtrRawData,"%04lx", (pefile.debug.deb).PointerToRawData);
            ui->tableWidget->setColumnCount(2);
            ui->tableWidget->setRowCount(8);
            ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Member"<<"Value");
            ui->tableWidget->setItem(0,0,new QTableWidgetItem("Characteristics"));
            ui->tableWidget->setItem(1,0,new QTableWidgetItem("TimeDateStamp"));
            ui->tableWidget->setItem(2,0,new QTableWidgetItem("MajorVersion"));
            ui->tableWidget->setItem(3,0,new QTableWidgetItem("MinorVersion"));
            ui->tableWidget->setItem(4,0,new QTableWidgetItem("Type"));
            ui->tableWidget->setItem(5,0,new QTableWidgetItem("SizeOfData"));
            ui->tableWidget->setItem(6,0,new QTableWidgetItem("AddressOfRawData"));
            ui->tableWidget->setItem(7,0,new QTableWidgetItem("PointerToRawData"));
            ui->tableWidget->setItem(0,1,new QTableWidgetItem(pefile.debug.Character));
            ui->tableWidget->setItem(1,1,new QTableWidgetItem(pefile.debug.TimeDate));
            ui->tableWidget->setItem(2,1,new QTableWidgetItem(pefile.debug.MaxVer));
            ui->tableWidget->setItem(3,1,new QTableWidgetItem(pefile.debug.MinVer));
            ui->tableWidget->setItem(4,1,new QTableWidgetItem(pefile.debug.Type));
            ui->tableWidget->setItem(5,1,new QTableWidgetItem(pefile.debug.Sizeofdata));
            ui->tableWidget->setItem(6,1,new QTableWidgetItem(pefile.debug.AddRawData));
            ui->tableWidget->setItem(7,1,new QTableWidgetItem(pefile.debug.PtrRawData));

        }

    }
    else if(pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER64))
    {
        fread(&pefile.OptionalHeader.opthdr64, sizeof(pefile.OptionalHeader.opthdr64), 1,fp);
        if(pefile.OptionalHeader.opthdr64.DataDirectory[6].Size==0&&
                pefile.OptionalHeader.opthdr64.DataDirectory[6].VirtualAddress==0)
        {
            QMessageBox::warning(this, "warning", "Sorry, the file has this data.");
        }
        else
        {
            fseek(fp,getRVA(pefile,6),SEEK_SET);
            fread(&pefile.debug.deb,sizeof(pefile.debug.deb),1,fp);
            sprintf(pefile.debug.Character,"%08lx", (pefile.debug.deb).Characteristics);
            sprintf(pefile.debug.TimeDate,"%08lx",  (pefile.debug.deb).TimeDateStamp);
            sprintf(pefile.debug.MaxVer,"%04x",  (pefile.debug.deb).MajorVersion);
            sprintf(pefile.debug.MinVer,"%04x",  (pefile.debug.deb).MinorVersion);
            sprintf(pefile.debug.Type,"%08lx",  (pefile.debug.deb).Type);
            sprintf(pefile.debug.Sizeofdata,"%08lx", (pefile.debug.deb).SizeOfData);
            sprintf(pefile.debug.AddRawData,"%08lx", (pefile.debug.deb).AddressOfRawData);
            sprintf(pefile.debug.PtrRawData,"%08lx", (pefile.debug.deb).PointerToRawData);
            ui->tableWidget->setColumnCount(2);
            ui->tableWidget->setRowCount(8);
            ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Member"<<"Value");
            ui->tableWidget->setItem(0,0,new QTableWidgetItem("Characteristics"));
            ui->tableWidget->setItem(1,0,new QTableWidgetItem("TimeDateStamp"));
            ui->tableWidget->setItem(2,0,new QTableWidgetItem("MajorVersion"));
            ui->tableWidget->setItem(3,0,new QTableWidgetItem("MinorVersion"));
            ui->tableWidget->setItem(4,0,new QTableWidgetItem("Type"));
            ui->tableWidget->setItem(5,0,new QTableWidgetItem("SizeOfData"));
            ui->tableWidget->setItem(6,0,new QTableWidgetItem("AddressOfRawData"));
            ui->tableWidget->setItem(7,0,new QTableWidgetItem("PointerToRawData"));
            ui->tableWidget->setItem(0,1,new QTableWidgetItem(pefile.debug.Character));
            ui->tableWidget->setItem(1,1,new QTableWidgetItem(pefile.debug.TimeDate));
            ui->tableWidget->setItem(2,1,new QTableWidgetItem(pefile.debug.MaxVer));
            ui->tableWidget->setItem(3,1,new QTableWidgetItem(pefile.debug.MinVer));
            ui->tableWidget->setItem(4,1,new QTableWidgetItem(pefile.debug.Type));
            ui->tableWidget->setItem(5,1,new QTableWidgetItem(pefile.debug.Sizeofdata));
            ui->tableWidget->setItem(6,1,new QTableWidgetItem(pefile.debug.AddRawData));
            ui->tableWidget->setItem(7,1,new QTableWidgetItem(pefile.debug.PtrRawData));
        }

    }





}

void Other::on_pushButton_2_clicked()
{
    read(pefile);
    QByteArray ba = pefile.name.toLatin1();
    const char *cstr = ba.data();
    FILE *fp = fopen(cstr, "rb");
    fread(&pefile.Dosheader.dosheader, sizeof(pefile.Dosheader.dosheader), 1, fp);
    fseek(fp, pefile.Dosheader.dosheader.e_lfanew, SEEK_SET);
    fread(&pefile.pesig, 4, 1, fp);
    fread(&pefile.FileHeader.fileheader, sizeof(pefile.FileHeader.fileheader), 1, fp);
    if (pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER32))
    {
        fread(&pefile.OptionalHeader.opthdr32, sizeof(pefile.OptionalHeader.opthdr32), 1,fp);
        if(pefile.OptionalHeader.opthdr32.DataDirectory[9].Size==0&&
                pefile.OptionalHeader.opthdr32.DataDirectory[9].VirtualAddress==0)
        {
            QMessageBox::warning(this, "warning", "Sorry, the file has this data.");
        }
        else
        {
            fseek(fp,getRVA(pefile,9),SEEK_SET);
            fread(&pefile.tsl.tls32,sizeof(pefile.tsl.tls32),1,fp);
            sprintf(pefile.tsl.Start,"%08lx", (pefile.tsl.tls32).StartAddressOfRawData);
            sprintf(pefile.tsl.End,"%08lx",   (pefile.tsl.tls32).EndAddressOfRawData);
            sprintf(pefile.tsl.AddIndex,"%08lx",  (pefile.tsl.tls32).AddressOfIndex);
            sprintf(pefile.tsl.address,"%08lx",  (pefile.tsl.tls32).AddressOfCallBacks);
            sprintf(pefile.tsl.sizeofzero,"%08lx",   (pefile.tsl.tls32).SizeOfZeroFill);
            sprintf(pefile.tsl.character,"%08lx",  (pefile.tsl.tls32).Characteristics);
            ui->tableWidget_2->setColumnCount(2);
            ui->tableWidget_2->setRowCount(6);
            ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"Member"<<"Value");
            ui->tableWidget_2->setItem(0,0,new QTableWidgetItem("StartAddressOfRawData"));
            ui->tableWidget_2->setItem(1,0,new QTableWidgetItem("EndAddressOfRawData"));
            ui->tableWidget_2->setItem(2,0,new QTableWidgetItem("AddressOfIndex"));
            ui->tableWidget_2->setItem(3,0,new QTableWidgetItem("AddressOfCallBacks"));
            ui->tableWidget_2->setItem(4,0,new QTableWidgetItem("SizeOfZeroFill"));
            ui->tableWidget_2->setItem(5,0,new QTableWidgetItem("Characteristics"));
            ui->tableWidget_2->setItem(0,1,new QTableWidgetItem(pefile.tsl.Start));
            ui->tableWidget_2->setItem(1,1,new QTableWidgetItem(pefile.tsl.End));
            ui->tableWidget_2->setItem(2,1,new QTableWidgetItem(pefile.tsl.AddIndex));
            ui->tableWidget_2->setItem(3,1,new QTableWidgetItem(pefile.tsl.address));
            ui->tableWidget_2->setItem(4,1,new QTableWidgetItem(pefile.tsl.sizeofzero));
            ui->tableWidget_2->setItem(5,1,new QTableWidgetItem(pefile.tsl.character));


        }

    }
    else if(pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER64))
      {
        fread(&pefile.OptionalHeader.opthdr64, sizeof(pefile.OptionalHeader.opthdr64), 1,fp);
        if(pefile.OptionalHeader.opthdr64.DataDirectory[9].Size==0&&
                pefile.OptionalHeader.opthdr64.DataDirectory[9].VirtualAddress==0)
        {
            QMessageBox::warning(this, "warning", "Sorry, the file has this data.");
        }
        else
        {
            fseek(fp,getRVA(pefile,9),SEEK_SET);
            fread(&pefile.tsl.tls64,sizeof(pefile.tsl.tls64),1,fp);
            sprintf(pefile.tsl.Start,"%012llx", (pefile.tsl.tls64).StartAddressOfRawData);
            sprintf(pefile.tsl.End,"%012llx",   (pefile.tsl.tls64).EndAddressOfRawData);
            sprintf(pefile.tsl.AddIndex,"%012llx",  (pefile.tsl.tls64).AddressOfIndex);
            sprintf(pefile.tsl.address,"%012llx",  (pefile.tsl.tls64).AddressOfCallBacks);
            sprintf(pefile.tsl.sizeofzero,"%08lx",   (pefile.tsl.tls64).SizeOfZeroFill);
            sprintf(pefile.tsl.character,"%08lx",  (pefile.tsl.tls64).Characteristics);
            ui->tableWidget_2->setColumnCount(2);
            ui->tableWidget_2->setRowCount(6);
            ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"Member"<<"Value");
            ui->tableWidget_2->setItem(0,0,new QTableWidgetItem("StartAddressOfRawData"));
            ui->tableWidget_2->setItem(1,0,new QTableWidgetItem("EndAddressOfRawData"));
            ui->tableWidget_2->setItem(2,0,new QTableWidgetItem("AddressOfIndex"));
            ui->tableWidget_2->setItem(3,0,new QTableWidgetItem("AddressOfCallBacks"));
            ui->tableWidget_2->setItem(4,0,new QTableWidgetItem("SizeOfZeroFill"));
            ui->tableWidget_2->setItem(5,0,new QTableWidgetItem("Characteristics"));
            ui->tableWidget_2->setItem(0,1,new QTableWidgetItem(pefile.tsl.Start));
            ui->tableWidget_2->setItem(1,1,new QTableWidgetItem(pefile.tsl.End));
            ui->tableWidget_2->setItem(2,1,new QTableWidgetItem(pefile.tsl.AddIndex));
            ui->tableWidget_2->setItem(3,1,new QTableWidgetItem(pefile.tsl.address));
            ui->tableWidget_2->setItem(4,1,new QTableWidgetItem(pefile.tsl.sizeofzero));
            ui->tableWidget_2->setItem(5,1,new QTableWidgetItem(pefile.tsl.character));


        }

    }
}
