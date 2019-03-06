#include "import.h"
#include "ui_import.h"
#include"QMessageBox"
#include "string.h"
Import::Import(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Import)
{
    ui->setupUi(this);
}

Import::~Import()
{
    delete ui;
}

void Import::on_pushButton_clicked()
{

       read(pefile);
       ui->listWidget->clear();
       ui->listWidget_2->clear();
       DWORD T[100],M[100],t=0,m=0;
       DWORD Name[100],OFT[100],temp[2000];
       WORD tword;
       char tchar[50];
       int f=0;
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
               if(pefile.OptionalHeader.opthdr32.DataDirectory[1].VirtualAddress>=
                       T[i] && pefile.OptionalHeader.opthdr32.DataDirectory[1].VirtualAddress<T[i+1])
               {
                   t =  T[i];
                   m =  M[i];
                   break;
               }
           }
           fseek(fp,pefile.OptionalHeader.opthdr32.DataDirectory[1].VirtualAddress-t+m, SEEK_SET);
           //printf("%lx",pefile.OptionalHeader.opthdr32.DataDirectory[1].VirtualAddress-t+m);
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
                 if(pefile.OptionalHeader.opthdr64.DataDirectory[1].VirtualAddress>=
                         T[i] && pefile.OptionalHeader.opthdr64.DataDirectory[1].VirtualAddress<T[i+1])
                 {
                     t =  T[i];
                     m =  M[i];
                     break;
                 }
             }
             fseek(fp,pefile.OptionalHeader.opthdr64.DataDirectory[1].VirtualAddress-t+m, SEEK_SET);
         }
            fread(&pefile.Import.iid, sizeof(pefile.Import.iid), 1, fp);
            int j=0;
            while (!(pefile.Import.iid.Name ==0 &&pefile.Import.iid.OriginalFirstThunk ==0
                  &&pefile.Import.iid.FirstThunk==0&&pefile.Import.iid.Characteristics==0
                  &&pefile.Import.iid.ForwarderChain==0&&pefile.Import.iid.TimeDateStamp==0) )
           {

                sprintf(pefile.Import.Namerva[j],"%08lx", pefile.Import.iid.Name);
                Name[j]=pefile.Import.iid.Name;
                sprintf(pefile.Import.TimeDateStamp[j],"%08lx", pefile.Import.iid.TimeDateStamp);
                sprintf(pefile.Import.ForwarderChain[j],"%08lx", pefile.Import.iid.ForwarderChain);
                sprintf(pefile.Import.FirstThunk[j],"%08lx", pefile.Import.iid.FirstThunk);
                sprintf(pefile.Import.OFT[j],"%08lx", pefile.Import.iid.OriginalFirstThunk);
                OFT[j]=pefile.Import.iid.OriginalFirstThunk;
                j++;
                fread(&pefile.Import.iid, sizeof(pefile.Import.iid), 1, fp);
           }
            char s[j][30];
            for(int k=0;k<j; k++)
            {
             fseek(fp,Name[k]-t+m, SEEK_SET);
             fread(s[k], sizeof(char[30]), 1, fp);
             sprintf(pefile.Import.Name[k],"%s",s[k]);
            }


       ui->tableWidget->setColumnCount(6);
       ui->tableWidget->setRowCount(j);
       ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Module name"<<"nameRVA"<<"OFTs"

                                                  <<"TimeDateStamp"<<"ForwaederChain"<<"FirstThunk");
       for(int i=0;i<j;i++)
       {

            ui->tableWidget->setItem(i,0,new QTableWidgetItem(pefile.Import.Name[i]));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(pefile.Import.Namerva[i]));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(pefile.Import.OFT[i]));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(pefile.Import.TimeDateStamp[i]));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(pefile.Import.ForwarderChain[i]));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(pefile.Import.FirstThunk[i]));

       }
       //******************************************
       int a[j];
       int sum=0;

       if (pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER32))
         {
              for(int b=0;b<j;b++)
             {
                  f=0;
                  fseek(fp,OFT[b]-t+m, SEEK_SET);
                  fread(&pefile.Import.data32, sizeof(pefile.Import.data32), 1, fp);
                   while (!(pefile.Import.data32.u1.AddressOfData ==0))
                   {
                       temp[f]=pefile.Import.data32.u1.AddressOfData;
                       f++;
                       fread(&pefile.Import.data32, sizeof(pefile.Import.data32), 1, fp);
                   }
                     a[b]=f;

                 for(int k=0;k<a[b];k++)
                {
                     fseek(fp,temp[k]-t+m, SEEK_SET);
                     fread(&tword, sizeof(tword), 1, fp);
                     fread(&tchar,sizeof (char[50]),1,fp);
                     sprintf(pefile.Import.Hint[k],"%04x\n",tword);
                     sprintf(pefile.Import.Name2[k],"%s\n",tchar);
                     ui->listWidget->insertItem(k+sum,(QString(QString("name:")+pefile.Import.Name2[k])+(QString(QString("hint:")+pefile.Import.Hint[k]))));
                }
                 sum+=a[b];

               }

         }
           else if(pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER64))
       {
           for(int b=0;b<j;b++)
         {
               f=0;
               fseek(fp,OFT[b]-t+m, SEEK_SET);
               fread(&pefile.Import.data64, sizeof(pefile.Import.data64), 1, fp);
               while (!(pefile.Import.data64.u1.AddressOfData ==0))
               {
                   temp[f]=pefile.Import.data64.u1.AddressOfData;
                   f++;
                   fread(&pefile.Import.data64, sizeof(pefile.Import.data64), 1, fp);
               }
               a[b]=f;
              for(int k=0;k<a[b];k++)
            {
                 fseek(fp,temp[k]-t+m, SEEK_SET);
                 fread(&tword, sizeof(tword), 1, fp);
                 fread(&tchar,sizeof (char[50]),1,fp);
                 sprintf(pefile.Import.Hint[k],"%04x\n",tword);
                 sprintf(pefile.Import.Name2[k],"%s\n",tchar);
                  ui->listWidget->insertItem(k+sum,(QString(QString("name:")+pefile.Import.Name2[k])+(QString(QString("hint:")+pefile.Import.Hint[k]))));
            }
               sum+=a[b];
           }
       }
              fclose(fp);

             for(int i=0;i<j;i++)
             {
                 ui->listWidget_2->insertItem(i,(QString(pefile.Import.Name[i]))+QString("共有")+QString::number(a[i])
                                              +QString("函数"));
             }
}

