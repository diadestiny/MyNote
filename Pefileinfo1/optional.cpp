#include "optional.h"
#include "ui_optional.h"
#include "class.h"
Optional::Optional(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Optional)
{
    ui->setupUi(this);
    QFont font ;
    font.setPointSize(15);
    font.setFamily(QString::fromLocal8Bit("微软雅黑"));
    ui->label->setFont(font);

}

Optional::~Optional()
{
    delete ui;
}

void peOptionalHeaderAnalyze(Pefile &pefile)
{
    QByteArray ba = pefile.name.toLatin1();
    const char *cstr = ba.data();
    FILE *fp = fopen(cstr, "rb");
    fread(&pefile.Dosheader.dosheader, sizeof(pefile.Dosheader.dosheader), 1, fp);
    fseek(fp, pefile.Dosheader.dosheader.e_lfanew, SEEK_SET);
    fread(&pefile.pesig, 4, 1, fp);
    fread(&pefile.FileHeader.fileheader, sizeof(pefile.FileHeader.fileheader), 1, fp);
    if (pefile.FileHeader.fileheader.Machine == IMAGE_FILE_MACHINE_I386)
    {
    fread(&pefile.OptionalHeader.opthdr32, sizeof(pefile.OptionalHeader.opthdr32), 1,fp);
    sprintf(pefile.OptionalHeader.Magic,"%04x", pefile.OptionalHeader.opthdr32.Magic);
    sprintf(pefile.OptionalHeader.ImageBase,"%08lx", pefile.OptionalHeader.opthdr32.ImageBase);
    sprintf(pefile.OptionalHeader.Subsystem,"%08x", pefile.OptionalHeader.opthdr32.Subsystem);
    sprintf(pefile.OptionalHeader.AddressOfEntryPoint,"%08lx", pefile.OptionalHeader.opthdr32.AddressOfEntryPoint);
    sprintf(pefile.OptionalHeader.SizeOfCode,"%08lx", pefile.OptionalHeader.opthdr32.SizeOfCode);
    sprintf(pefile.OptionalHeader.SizeOfImage,"%08lx", pefile.OptionalHeader.opthdr32.SizeOfImage);
    sprintf(pefile.OptionalHeader.SizeOfHeaders,"%08lx", pefile.OptionalHeader.opthdr32.SizeOfHeaders);
    sprintf(pefile.OptionalHeader.SectionAlignment,"%08lx", pefile.OptionalHeader.opthdr32.SectionAlignment);
    sprintf(pefile.OptionalHeader.FileAlignment,"%08lx", pefile.OptionalHeader.opthdr32.FileAlignment);
    fclose(fp);
    }
    else if (pefile.FileHeader.fileheader.Machine == IMAGE_FILE_MACHINE_AMD64
             ||pefile.FileHeader.fileheader.Machine ==IMAGE_FILE_MACHINE_IA64)
    {
        fread(&pefile.OptionalHeader.opthdr64, sizeof(pefile.OptionalHeader.opthdr64), 1,fp);
        sprintf(pefile.OptionalHeader.Magic,"%04x", pefile.OptionalHeader.opthdr64.Magic);
        sprintf(pefile.OptionalHeader.ImageBase,"%016llx", pefile.OptionalHeader.opthdr64.ImageBase);
        sprintf(pefile.OptionalHeader.Subsystem,"%08x", pefile.OptionalHeader.opthdr64.Subsystem);
        sprintf(pefile.OptionalHeader.AddressOfEntryPoint,"%08lx", pefile.OptionalHeader.opthdr64.AddressOfEntryPoint);
        sprintf(pefile.OptionalHeader.SizeOfCode,"%08lx", pefile.OptionalHeader.opthdr64.SizeOfCode);
        sprintf(pefile.OptionalHeader.SizeOfImage,"%08lx", pefile.OptionalHeader.opthdr64.SizeOfImage);
        sprintf(pefile.OptionalHeader.SizeOfHeaders,"%08lx", pefile.OptionalHeader.opthdr64.SizeOfHeaders);
        sprintf(pefile.OptionalHeader.SectionAlignment,"%08lx", pefile.OptionalHeader.opthdr64.SectionAlignment);
        sprintf(pefile.OptionalHeader.FileAlignment,"%08lx", pefile.OptionalHeader.opthdr64.FileAlignment);
        fclose(fp);
    }

}

void Optional::on_pushButton_clicked()
{
     read(pefile);
     peOptionalHeaderAnalyze(pefile);
     ui->tableWidget->setColumnCount(6);
     ui->tableWidget->setRowCount(3);
     ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Member"<<"Value"<<"Member"<<"Value"<<"Member"<<"Value");
     ui->tableWidget->setItem(0,0,new QTableWidgetItem("Magic")); //设置表格内容
     ui->tableWidget->setItem(1,0,new QTableWidgetItem("ImageBase"));
     ui->tableWidget->setItem(2,0,new QTableWidgetItem("Subsystem"));
     ui->tableWidget->setItem(0,2,new QTableWidgetItem("AddressOfEntryPoint"));
     ui->tableWidget->setItem(1,2,new QTableWidgetItem("SizeOfCode"));
     ui->tableWidget->setItem(2,2,new QTableWidgetItem("SizeOfImage"));
     ui->tableWidget->setItem(0,4,new QTableWidgetItem("SizeOfHeaders"));
     ui->tableWidget->setItem(1,4,new QTableWidgetItem("SectionAlignment"));
     ui->tableWidget->setItem(2,4,new QTableWidgetItem("FileAlignment"));
     ui->tableWidget->setItem(0,1,new QTableWidgetItem(pefile.OptionalHeader.Magic)); //设置表格内容
     ui->tableWidget->setItem(1,1,new QTableWidgetItem(pefile.OptionalHeader.ImageBase));
     ui->tableWidget->setItem(2,1,new QTableWidgetItem(pefile.OptionalHeader.Subsystem));
     ui->tableWidget->setItem(0,3,new QTableWidgetItem(pefile.OptionalHeader.AddressOfEntryPoint));
     ui->tableWidget->setItem(1,3,new QTableWidgetItem(pefile.OptionalHeader.SizeOfCode));
     ui->tableWidget->setItem(2,3,new QTableWidgetItem(pefile.OptionalHeader.SizeOfImage));
     ui->tableWidget->setItem(0,5,new QTableWidgetItem(pefile.OptionalHeader.SizeOfHeaders));
     ui->tableWidget->setItem(1,5,new QTableWidgetItem(pefile.OptionalHeader.SectionAlignment));
     ui->tableWidget->setItem(2,5,new QTableWidgetItem(pefile.OptionalHeader.FileAlignment));



     for(int i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
     {
     if(pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER32))
     {
     sprintf(pefile.OptionalHeader.Dataaddress[i],"%08lx",pefile.OptionalHeader.opthdr32.DataDirectory[i].VirtualAddress);
     sprintf(pefile.OptionalHeader.Datasize[i],"%08lx",pefile.OptionalHeader.opthdr32.DataDirectory[i].Size);
     }
     else if(pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER64))
     {
         sprintf(pefile.OptionalHeader.Dataaddress[i],"%08lx",pefile.OptionalHeader.opthdr64.DataDirectory[i].VirtualAddress);
         sprintf(pefile.OptionalHeader.Datasize[i],"%08lx",pefile.OptionalHeader.opthdr64.DataDirectory[i].Size);
     }
     }


     QTreeWidgetItem ** ptree1 = new QTreeWidgetItem*[15];
     QTreeWidgetItem ** ptree2 = new QTreeWidgetItem*[15];
     for(int i=0;i<15;i++)
     {
        ptree1[i] = new  QTreeWidgetItem[100];
        ptree2[i] = new  QTreeWidgetItem[100];
     }

    QTreeWidgetItem * p  = new QTreeWidgetItem(ui->treeWidget,
                            QStringList(QString("DataDirectory")));
     ptree1[0] = new QTreeWidgetItem(p,
                            QStringList(QString("Export Directory")));
     ptree1[1] = new QTreeWidgetItem(p,
                            QStringList(QString("Import Directory")));
     ptree1[2] = new QTreeWidgetItem(p,
                            QStringList(QString("Resource Diretory")));
     ptree1[3] = new QTreeWidgetItem(p,
                            QStringList(QString("Exception Diretory")));
     ptree1[4] = new QTreeWidgetItem(p,
                            QStringList(QString("Security Diretory")));
     ptree1[5] = new QTreeWidgetItem(p,
                            QStringList(QString("Relocation Diretory")));
     ptree1[6]= new QTreeWidgetItem(p,
                            QStringList(QString("Debug Diretory")));
     ptree1[7] = new QTreeWidgetItem(p,
                            QStringList(QString("Architecture Diretory")));
     ptree1[8] = new QTreeWidgetItem(p,
                            QStringList(QString("Reserved Diretory")));   
     ptree1[9] = new QTreeWidgetItem(p,
                            QStringList(QString("TLSDirectory Diretory")));
     ptree1[10] = new QTreeWidgetItem(p,
                            QStringList(QString("Configuration Diretory")));
     ptree1[11]= new QTreeWidgetItem(p,
                            QStringList(QString("Bound Import Diretory")));
     ptree1[12] = new QTreeWidgetItem(p,
                            QStringList(QString("Import Address Table Diretory")));
     ptree1[13] = new QTreeWidgetItem(p,
                            QStringList(QString("Delay Import Diretory")));
     ptree1[14]= new QTreeWidgetItem(p,
                            QStringList(QString(".NET MetaData Diretory")));
     for(int i=0;i<15;i++)
     {

         ptree2[i] = new QTreeWidgetItem(ptree1[i],
                                QStringList(QString("RVA:")+QString(pefile.OptionalHeader.Dataaddress[i])));
         ptree2[i] = new QTreeWidgetItem(ptree1[i],
                                QStringList(QString("Size:")+QString(pefile.OptionalHeader.Datasize[i])));

     }


}
