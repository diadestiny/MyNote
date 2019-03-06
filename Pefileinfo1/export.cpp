#include "export.h"
#include "ui_export.h"
#include <QMessageBox>
Export::Export(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Export)
{
    ui->setupUi(this);
}

Export::~Export()
{
    delete ui;
}

void Export::on_pushButton_clicked()
{
    ui->listWidget->clear();
     DWORD T[100],M[100],t=0,m=0;
     DWORD t1;
     char t12[15];
     WORD t4;
     char t11[15],tname[50],t14[15];
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
         for(int i=0;i<pefile.FileHeader.fileheader.NumberOfSections; i++)
         {
             fread(&pefile.Sechdr.sechdr, sizeof(pefile.Sechdr.sechdr), 1, fp);
             T[i]=pefile.Sechdr.sechdr.VirtualAddress;
             M[i]=pefile.Sechdr.sechdr.PointerToRawData;

          }

         for(int i=0;i<pefile.FileHeader.fileheader.NumberOfSections; i++)
         {
             if(pefile.OptionalHeader.opthdr32.DataDirectory[0].VirtualAddress>=
                     T[i] && pefile.OptionalHeader.opthdr32.DataDirectory[0].VirtualAddress<T[i+1])
             {
                 t =  T[i];
                 m =  M[i];
                 break;
             }
         }
         fseek(fp,pefile.OptionalHeader.opthdr32.DataDirectory[0].VirtualAddress-t+m, SEEK_SET);
       }
       else if(pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER64))
       {
           fread(&pefile.OptionalHeader.opthdr64, sizeof(pefile.OptionalHeader.opthdr64), 1,fp);
           for(int i=0;i<pefile.FileHeader.fileheader.NumberOfSections; i++)
           {

               fread(&pefile.Sechdr.sechdr, sizeof(pefile.Sechdr.sechdr), 1, fp);
               T[i]=pefile.Sechdr.sechdr.VirtualAddress;
               M[i]=pefile.Sechdr.sechdr.PointerToRawData;

            }
           for(int i=0;i<pefile.FileHeader.fileheader.NumberOfSections; i++)
           {
               if(pefile.OptionalHeader.opthdr64.DataDirectory[0].VirtualAddress>=
                       T[i] && pefile.OptionalHeader.opthdr64.DataDirectory[0].VirtualAddress<T[i+1])
               {
                   t =  T[i];
                   m =  M[i];
                   break;
               }
           }
           fseek(fp,pefile.OptionalHeader.opthdr64.DataDirectory[0].VirtualAddress-t+m, SEEK_SET);
       }

       if(pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER32))
       {
           if(pefile.OptionalHeader.opthdr32.DataDirectory[0].Size==0&&
                   pefile.OptionalHeader.opthdr32.DataDirectory[0].VirtualAddress==0)
           {
               QMessageBox::warning(this, "warning", "Sorry, the file has this data.");
           }
           else
           {
               fread(&pefile.exp.export1, sizeof(pefile.exp.export1), 1, fp);
               sprintf(pefile.exp.Character,"%08lx", (pefile.exp.export1).Characteristics);
               sprintf(pefile.exp.TimeDate,"%08lx",   (pefile.exp.export1).TimeDateStamp);
               sprintf(pefile.exp.MaxVer,"%08x",  (pefile.exp.export1).MajorVersion);
               sprintf(pefile.exp.MinVer,"%08x", (pefile.exp.export1).MinorVersion);
               sprintf(pefile.exp.Namerva,"%08lx",   (pefile.exp.export1).Name);
               sprintf(pefile.exp.base,"%08lx",  (pefile.exp.export1).Base);
               sprintf(pefile.exp.numfunc,"%08lx",(pefile.exp.export1).NumberOfFunctions);
               sprintf(pefile.exp.numname,"%08lx",  (pefile.exp.export1).NumberOfNames);
               sprintf(pefile.exp.addfun,"%08lx",  (pefile.exp.export1).AddressOfFunctions);
               sprintf(pefile.exp.addname,"%08lx",  (pefile.exp.export1).AddressOfNames);
               sprintf(pefile.exp.addnameord,"%08lx",  (pefile.exp.export1).AddressOfNameOrdinals);
               for(int i=0;i<pefile.FileHeader.fileheader.NumberOfSections; i++)
               {
                   if((pefile.exp.export1).Name>=
                           T[i] && (pefile.exp.export1).Name<T[i+1])
                   {
                       t =  T[i];
                       m =  M[i];
                       break;
                   }
               }
               fseek(fp,(pefile.exp.export1).Name-t+m, SEEK_SET);
               char na[40];
               fread(na, sizeof(char[40]), 1, fp);
               sprintf(pefile.exp.Name,"%s",na);
               ui->label->setText(QString("nameRVA指向的文件名：")+pefile.exp.Name);

                 fseek(fp,(pefile.exp.export1).AddressOfNames-t+m, SEEK_SET);
                for(int i=0;i<(pefile.exp.export1).NumberOfNames;i++)
                {
                    fread(&t1,sizeof(DWORD),1,fp);
                    long t13=ftell(fp);
                    sprintf(t11,"%08lx",t1);
                    fseek(fp,t1-t+m,SEEK_SET);
                    fread(&tname,sizeof(char[50]),1,fp);
                    sprintf(pefile.exp.funcname,"%s",tname);
                    fseek(fp,(pefile.exp.export1).AddressOfNameOrdinals-t+m+sizeof(WORD)*i, SEEK_SET);
                    fread(&t4,sizeof(WORD),1,fp);
                    sprintf(t14,"%08lx",t4);
                    fseek(fp,(pefile.exp.export1).AddressOfFunctions-t+m+sizeof(DWORD)*i, SEEK_SET);
                    fread(&t1,sizeof(DWORD),1,fp);
                    sprintf(t12,"%08lx",t1);
                    ui->listWidget->insertItem(i,t11+QString("    ")+QString(pefile.exp.funcname)+QString("    ")+t14+
                                               QString("    ")+t12);
                    fseek(fp,t13,SEEK_SET);
                }


           }

       }

       else if(pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER64))
       {
           if(pefile.OptionalHeader.opthdr64.DataDirectory[0].Size==0&&
                   pefile.OptionalHeader.opthdr64.DataDirectory[0].VirtualAddress==0)
           {
               QMessageBox::warning(this, "warning", "Sorry, the file has this data.");
           }
           else {
               fread(&pefile.exp.export1, sizeof(pefile.exp.export1), 1, fp);
               sprintf(pefile.exp.Character,"%08lx", (pefile.exp.export1).Characteristics);
               sprintf(pefile.exp.TimeDate,"%08lx",   (pefile.exp.export1).TimeDateStamp);
               sprintf(pefile.exp.MaxVer,"%08x",  (pefile.exp.export1).MajorVersion);
               sprintf(pefile.exp.MinVer,"%08x", (pefile.exp.export1).MinorVersion);
               sprintf(pefile.exp.Namerva,"%08lx",   (pefile.exp.export1).Name);
               sprintf(pefile.exp.base,"%08lx",  (pefile.exp.export1).Base);
               sprintf(pefile.exp.numfunc,"%08lx",(pefile.exp.export1).NumberOfFunctions);
               sprintf(pefile.exp.numname,"%08lx",  (pefile.exp.export1).NumberOfNames);
               sprintf(pefile.exp.addfun,"%08lx",  (pefile.exp.export1).AddressOfFunctions);
               sprintf(pefile.exp.addname,"%08lx",  (pefile.exp.export1).AddressOfNames);
               sprintf(pefile.exp.addnameord,"%08lx",  (pefile.exp.export1).AddressOfNameOrdinals);
               for(int i=0;i<pefile.FileHeader.fileheader.NumberOfSections; i++)
               {
                   if((pefile.exp.export1).Name>=
                           T[i] && (pefile.exp.export1).Name<T[i+1])
                   {
                       t =  T[i];
                       m =  M[i];
                       break;
                   }
               }
               fseek(fp,(pefile.exp.export1).Name-t+m, SEEK_SET);
               char na[40];
               fread(na, sizeof(char[40]), 1, fp);
               sprintf(pefile.exp.Name,"%s",na);
                 ui->label->setText(QString("nameRVA指向的文件名：")+pefile.exp.Name);
                 fseek(fp,(pefile.exp.export1).AddressOfNames-t+m, SEEK_SET);
                for(int i=0;i<(pefile.exp.export1).NumberOfNames;i++)
                {
                    fread(&t1,sizeof(DWORD),1,fp);
                    long t13=ftell(fp);
                    sprintf(t11,"%08lx",t1);
                    fseek(fp,t1-t+m,SEEK_SET);
                    fread(&tname,sizeof(char[50]),1,fp);
                    sprintf(pefile.exp.funcname,"%s",tname);
                    fseek(fp,(pefile.exp.export1).AddressOfNameOrdinals-t+m+sizeof(WORD)*i, SEEK_SET);
                    fread(&t4,sizeof(WORD),1,fp);
                    sprintf(t14,"%08lx",t4);
                    fseek(fp,(pefile.exp.export1).AddressOfFunctions-t+m+sizeof(DWORD)*i, SEEK_SET);
                    fread(&t1,sizeof(DWORD),1,fp);
                    sprintf(t12,"%08lx",t1);
                    ui->listWidget->insertItem(i,t11+QString("    ")+QString(pefile.exp.funcname)+QString("    ")+t14+
                                               QString("    ")+t12);
                    fseek(fp,t13,SEEK_SET);
                }

           }

       }
          ui->tableWidget->setColumnCount(2);
          ui->tableWidget->setRowCount(11);
          ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Member"<<"Value");
          ui->tableWidget->setItem(0,0,new QTableWidgetItem("Characteristics"));
          ui->tableWidget->setItem(1,0,new QTableWidgetItem("TimeDateStamp"));
          ui->tableWidget->setItem(2,0,new QTableWidgetItem("MajorVersion"));
          ui->tableWidget->setItem(3,0,new QTableWidgetItem("MinorVersion"));
          ui->tableWidget->setItem(4,0,new QTableWidgetItem("Name"));
          ui->tableWidget->setItem(5,0,new QTableWidgetItem("Base"));
          ui->tableWidget->setItem(6,0,new QTableWidgetItem("NumberOfFunctions"));
          ui->tableWidget->setItem(7,0,new QTableWidgetItem("NumberOfNames"));
          ui->tableWidget->setItem(8,0,new QTableWidgetItem("AddressOfFunctions"));
          ui->tableWidget->setItem(9,0,new QTableWidgetItem("AddressOfNames"));
          ui->tableWidget->setItem(10,0,new QTableWidgetItem("AddressOfNameOrdinals"));

          ui->tableWidget->setItem(0,1,new QTableWidgetItem(pefile.exp.Character));
          ui->tableWidget->setItem(1,1,new QTableWidgetItem(pefile.exp.TimeDate));
          ui->tableWidget->setItem(2,1,new QTableWidgetItem(pefile.exp.MaxVer));
          ui->tableWidget->setItem(3,1,new QTableWidgetItem(pefile.exp.MinVer));
          ui->tableWidget->setItem(4,1,new QTableWidgetItem(pefile.exp.Namerva));
          ui->tableWidget->setItem(5,1,new QTableWidgetItem(pefile.exp.base));
          ui->tableWidget->setItem(6,1,new QTableWidgetItem(pefile.exp.numfunc));
          ui->tableWidget->setItem(7,1,new QTableWidgetItem(pefile.exp.numname));
          ui->tableWidget->setItem(8,1,new QTableWidgetItem(pefile.exp.addfun));
          ui->tableWidget->setItem(9,1,new QTableWidgetItem(pefile.exp.addname));
          ui->tableWidget->setItem(10,1,new QTableWidgetItem(pefile.exp.addnameord));


}
