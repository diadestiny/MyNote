#include "dialog.h"
#include"ui_dialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QLineEdit>
#include <QDialog>
#include<QLabel>
#include<QFile>
#include<iostream>
#include"pe.h"
#include<stdio.h>
#include<class.h>
#include<section.h>
#include<string.h>
#include<QMessageBox>
#include"math.h"
#include<QDateTime>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QFont font ;
    font.setPointSize(15);
    font.setFamily(QString::fromLocal8Bit("微软雅黑"));
    ui->label->setFont(font);
    setWindowTitle(tr("Welcome to a pefile explorer"));
    setWindowIcon(QIcon(":/new/prefix1/icon"));
    Qt::WindowFlags flags=Qt::Dialog;

        flags |=Qt::WindowMinMaxButtonsHint;

        flags |=Qt::WindowCloseButtonHint;

        setWindowFlags(flags);



}

Dialog::~Dialog()
{
    delete ui;
}


 bool Dialog::ExitFile(const QString &fileName)
{

    QFile file(fileName); // 新建QFile对象
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
       QMessageBox::warning(this, tr("多文档编辑器"),
                             tr("无法读取文件 %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
       return false; // 只读方式打开文件，出错则提示，并返回false
   }
   QByteArray ba=file.read(file.bytesAvailable());
   // 读取文件的全部文本内容，并添加到编辑器中
   ui->textEdit->setFontPointSize(15);

   ui->textEdit->setPlainText(ba.toHex());


     return true;

}


void read( Pefile &pefile)
{
    pefile.name = QFileDialog::getOpenFileName();
}

BOOL isPevaild(Pefile & pefile)
{
    QByteArray ba = pefile.name.toLatin1();
    const char *cstr = ba.data();
    FILE *fp = fopen(cstr, "rb");
    fread(&pefile.Dosheader.dosheader, sizeof(pefile.Dosheader.dosheader), 1, fp);
    fseek(fp, pefile.Dosheader.dosheader.e_lfanew, SEEK_SET);
    fread(&pefile.pesig, 4, 1,fp);
    fclose(fp);

    if (pefile.Dosheader.dosheader.e_magic == IMAGE_DOS_SIGNATURE && pefile.pesig == IMAGE_NT_SIGNATURE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
long getRVA (Pefile &pefile,int num)
{
    DWORD T[100],M[100],t=0,m=0;
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
            if(pefile.OptionalHeader.opthdr32.DataDirectory[num].VirtualAddress>=
                    T[i] && pefile.OptionalHeader.opthdr32.DataDirectory[num].VirtualAddress<T[i+1])
            {
                t =  T[i];
                m =  M[i];
                break;
            }
        }
        return pefile.OptionalHeader.opthdr32.DataDirectory[num].VirtualAddress-t+m;
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
              if(pefile.OptionalHeader.opthdr64.DataDirectory[num].VirtualAddress>=
                      T[i] && pefile.OptionalHeader.opthdr64.DataDirectory[num].VirtualAddress<T[i+1])
              {
                  t =  T[i];
                  m =  M[i];
                  break;
              }
          }
           return pefile.OptionalHeader.opthdr64.DataDirectory[num].VirtualAddress-t+m;
      }
}
long getRVA2 (Pefile &pefile,long num)
{
    DWORD T[100],M[100],t=0,m=0;
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
            if((num>=T[i] && num<T[i+1])||(i==pefile.FileHeader.fileheader.NumberOfSections-1
                                           && num>=T[i] ) )
            {
                t =  T[i];
                m =  M[i];
                break;
            }
        }
        return num-t+m;
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
              if((num>=T[i] && num<T[i+1])||(i==pefile.FileHeader.fileheader.NumberOfSections-1
                                             && num>=T[i] ) )
              {
                  t =  T[i];
                  m =  M[i];
                  break;
              }
          }
           return  num-t+m;
      }
}

void Dialog::on_pushButton_2_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("打开文件"),
                                                   ".",
                                                    tr("All Files(*.*)"));
    pefile.name =fileName;
    if (!fileName.isEmpty())
    {
        ui->pathEdit->setText(fileName);
        QString infoList,infoList2;
        QFile file(fileName);
        QTextStream in(&file);
        if (!(file.open(QIODevice::ReadOnly | QIODevice::Text)&&isPevaild(pefile)))
        {
           QMessageBox::warning(this, "warning", "It isn't a valid pe file.");
        }
        else
       {
        QFileInfo info(fileName);
        if (info.exists())
        {
            QFont font1 ;
            font1.setPointSize(15);
            font1.setFamily(QString::fromLocal8Bit("微软雅黑"));
            ui->infoLabel->setFont(font1);
            ui->label_9->setFont(font1);

            infoList += tr("文件大小: %1 KB (%2MB)\n").arg(info.size()/1024).arg(info.size()/1048576.0);
            infoList += tr("文件路径: %1 \n").arg(info.filePath());
            infoList += tr("文件名字: %1 \n").arg(info.fileName());
            infoList2 += tr("创建时间: %1 \n").arg(info.birthTime().toString());
            infoList2 += tr("修改时间: %1 \n").arg(info.lastModified().toString());
            infoList2 += tr("读取时间: %1 \n").arg(info.lastRead().toString());

            ui->infoLabel->setText(infoList);
            ui->label_9->setText(infoList2);
            ui->infoLabel->setWordWrap(true);
            ui->infoLabel->setAlignment(Qt::AlignTop);
            ui->label_9->setWordWrap(true);
            ui->label_9->setAlignment(Qt::AlignTop);
        }
       }
    }
}


void Dialog::on_pushButton_clicked()
{
   if (!pefile.name.isEmpty()){
   mydialog = new MyDialog;
   mydialog -> show();
   }
}


void Dialog::on_pushButton_3_clicked()
{
    if (!pefile.name.isEmpty()){
    file = new File;
    file -> show();
    }
}

void Dialog::on_pushButton_4_clicked()
{
    if (!pefile.name.isEmpty()){
    optional = new Optional;
    optional ->show();
    }
}


void Dialog::on_pushButton_5_clicked()
{
    if (!pefile.name.isEmpty()){
    section = new Section;
    section ->show();
    }
}

void Dialog::on_pushButton_6_clicked()
{
    if (!pefile.name.isEmpty()){
    import = new Import;
    import ->show();
    }
}



void Dialog::on_pushButton_7_clicked()
{
    if (!pefile.name.isEmpty()){
    other =new Other;
    other ->show();
    }
}

void Dialog::on_pushButton_8_clicked()
{
    if (!pefile.name.isEmpty()){
    expo =new Export;
    expo ->show();
    }
}

void Dialog::on_pushButton_9_clicked()
{
    if (!pefile.name.isEmpty()){
    reloc =new Relocation;
    reloc ->show();
    }
}

void Dialog::on_pushButton_10_clicked()
{

     if (!pefile.name.isEmpty())
     {
         QFileInfo info(pefile.name);
         if(info.size()/1024<=80){
         ExitFile(pefile.name);
         }else
         {
             QMessageBox::warning(this, "warning", "仅支持80KB以下的PE文件查看。");
         }
     }
}

void Dialog::on_pushButton_11_clicked()
{
     if (!pefile.name.isEmpty())
     {
         QString t=ui->lineEdit->text();
         QByteArray ba = t.toLatin1();
         char t2[100],result[100];
         long t3=0,t4=0;
         const char *t1 = ba.data();
         sprintf(t2,"%s",t1);
         size_t len =strlen(t2);
         printf("%s",t2);
         for(auto i=0;i<len;i++)
         {
          if('0'<=t2[i]&&t2[i]<='9')
          {
              t3+=(t2[i]-'0')*pow(16,(len-i-1));
          }
          else if('a'<=t2[i]&&t2[i]<='z')
          {
              t3+=(t2[i]-'a'+10)*pow(16,(len-i-1));
          }
          else if ('A'<=t2[i]&&t2[i]<='Z')
          {
                t3+=(t2[i]-'A'+10)*pow(16,(len-i-1));
          }

         }
         t4=getRVA2(pefile,t3);

        sprintf(result,"%lx",t4);
     ui->lineEdit_2->setText(result);
    }
}

void Dialog::on_pushButton_12_clicked()
{
    if (!pefile.name.isEmpty())
    {
        long t=ui->lineEdit_3->text().toLong();

        long t1=getRVA(pefile,t);
        printf("%d",t1);
        char result[100];
        sprintf(result,"%lx",t1);
        ui->lineEdit_4->setText(result);
    }
}
