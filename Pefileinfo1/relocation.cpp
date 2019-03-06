#include "relocation.h"
#include "ui_relocation.h"
#include<QMessageBox>
Relocation::Relocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Relocation)
{
    ui->setupUi(this);
}

Relocation::~Relocation()
{
    delete ui;
}

void Relocation::on_pushButton_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    DWORD T[100],M[100],t=0,m=0;
    WORD t1;
    int temp=0;
    long long add1=0,add2=0;
    char t11[2000][10];
    unsigned long num[2000];
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
          if((pefile.OptionalHeader.opthdr32.DataDirectory[5].VirtualAddress>=
                  T[i] && pefile.OptionalHeader.opthdr32.DataDirectory[5].VirtualAddress<T[i+1])
                  || ( i== pefile.FileHeader.fileheader.NumberOfSections-1&&
                       pefile.OptionalHeader.opthdr32.DataDirectory[5].VirtualAddress>=
                                                T[i]))
          {
              t =  T[i];
              m =  M[i];
              break;
          }
      }

      fseek(fp,pefile.OptionalHeader.opthdr32.DataDirectory[5].VirtualAddress-t+m, SEEK_SET);
     // printf("%x\n",pefile.OptionalHeader.opthdr32.DataDirectory[5].VirtualAddress);
    //  printf("%x\n%x\n",t,m);


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
            if((pefile.OptionalHeader.opthdr64.DataDirectory[5].VirtualAddress>=
                    T[i] && pefile.OptionalHeader.opthdr64.DataDirectory[5].VirtualAddress<T[i+1])
                    || ( i== pefile.FileHeader.fileheader.NumberOfSections-1&&
                         pefile.OptionalHeader.opthdr64.DataDirectory[5].VirtualAddress>=
                                                  T[i]))
            {
                t =  T[i];
                m =  M[i];
                break;
            }
        }

        fseek(fp,pefile.OptionalHeader.opthdr64.DataDirectory[5].VirtualAddress-t+m, SEEK_SET);

    }
    if (pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER32))
    {

        if(pefile.OptionalHeader.opthdr32.DataDirectory[5].Size==0&&
                pefile.OptionalHeader.opthdr32.DataDirectory[5].VirtualAddress==0)
        {
            QMessageBox::warning(this, "warning", "Sorry, the file has this data.");
        }
        else
        {
            add2=ftell(fp);
            printf("\n%x\n",ftell(fp));
            for(int b=0;add1<pefile.OptionalHeader.opthdr32.DataDirectory[5].Size+add2;b++)
        {    //printf("\n%x\n",ftell(fp));
             fread(&pefile.relocation.rel,sizeof(pefile.relocation.rel),1,fp);
             sprintf(pefile.relocation.RVA,"%08lx", (pefile.relocation.rel).VirtualAddress);
             sprintf(pefile.relocation.Size,"%08lx",  (pefile.relocation.rel).SizeOfBlock);
             sprintf(pefile.relocation.Item,"%lu",((pefile.relocation.rel).SizeOfBlock-8)/2);
             num[b]=((pefile.relocation.rel).SizeOfBlock-8)/2;
             ui->listWidget->insertItem(b,pefile.relocation.RVA+QString("    ")+pefile.relocation.Size
                                        +QString("    ")+pefile.relocation.Item);
            for(int i=0;i<num[b];i++)
            {
               fread(&t1,sizeof(WORD),1,fp);
                 sprintf(t11[i],"%x",t1);
                ui->listWidget_2->insertItem(i,QString("第")+QString::number(b+1)+QString("项  ")+QString::number(i+1)+QString(".     ")+t11[i]);

            }
            temp=((pefile.relocation.rel).SizeOfBlock-8)/2;
            add1=ftell(fp);
        }
        }
    }
    else if(pefile.FileHeader.fileheader.SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER64))
    {


        if(pefile.OptionalHeader.opthdr64.DataDirectory[5].Size==0&&
                pefile.OptionalHeader.opthdr64.DataDirectory[5].VirtualAddress==0)
        {
            QMessageBox::warning(this, "warning", "Sorry, the file has this data.");
        }
        else
        {
            add2=ftell(fp);
            printf("\n%x\n",ftell(fp));
            for(int b=0;add1<pefile.OptionalHeader.opthdr64.DataDirectory[5].Size+add2;b++)
        {    //printf("\n%x\n",ftell(fp));
             fread(&pefile.relocation.rel,sizeof(pefile.relocation.rel),1,fp);
             sprintf(pefile.relocation.RVA,"%08lx", (pefile.relocation.rel).VirtualAddress);
             sprintf(pefile.relocation.Size,"%08lx",  (pefile.relocation.rel).SizeOfBlock);
             sprintf(pefile.relocation.Item,"%lu",((pefile.relocation.rel).SizeOfBlock-8)/2);
             num[b]=((pefile.relocation.rel).SizeOfBlock-8)/2;
             ui->listWidget->insertItem(b,pefile.relocation.RVA+QString("    ")+pefile.relocation.Size
                                        +QString("    ")+pefile.relocation.Item);
            for(int i=0;i<num[b];i++)
            {
               fread(&t1,sizeof(WORD),1,fp);
                 sprintf(t11[i],"%x",t1);
                ui->listWidget_2->insertItem(i,QString("第")+QString::number(b+1)+QString("项  ")+QString::number(i+1)+QString(".     ")+t11[i]);

            }
            temp=((pefile.relocation.rel).SizeOfBlock-8)/2;
             add1=ftell(fp);
        }
        }
}
}
