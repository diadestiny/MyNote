#include "dos.h"
#include"ui_dos.h"
#include<dialog.h>
#include<pe.h>
#include<class.h>
#include<QTableWidget>
MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);


}

MyDialog::~MyDialog()
{
    delete ui;
}


void peDosHeaderAnalyze( Pefile &pefile)
{


    QByteArray ba = pefile.name.toLatin1();
    const char *cstr = ba.data();
    FILE *fp = fopen(cstr, "rb");
    fread(&pefile.Dosheader.dosheader, sizeof(pefile.Dosheader.dosheader), 1, fp);
    // IMAGE_DOS_HEADER *dp=&pefile.Dosheader.dosheader;
    //dp->e_cblp =16;
    // printf("%x\n",dp->e_cblp);
    // printf("%x\n",pefile.Dosheader.dosheader.e_cblp);
    fclose(fp);
    sprintf(pefile.Dosheader.e_magic,"%04x", (pefile.Dosheader.dosheader).e_magic);
    sprintf(pefile.Dosheader.e_cblp,"%04x", (pefile.Dosheader.dosheader).e_cblp);
    sprintf(pefile.Dosheader.e_cp,"%04x", (pefile.Dosheader.dosheader).e_cp);
    sprintf(pefile.Dosheader.e_crlc,"%04x", (pefile.Dosheader.dosheader).e_crlc);
    sprintf(pefile.Dosheader.e_cparhdr,"%04x", (pefile.Dosheader.dosheader).e_cparhdr);
    sprintf(pefile.Dosheader.e_minalloc,"%04x", (pefile.Dosheader.dosheader).e_minalloc);
    sprintf(pefile.Dosheader.e_maxalloc,"%04x", (pefile.Dosheader.dosheader).e_maxalloc);
    sprintf(pefile.Dosheader.e_ss,"%04x", (pefile.Dosheader.dosheader).e_ss);
    sprintf(pefile.Dosheader.e_sp,"%04x", (pefile.Dosheader.dosheader).e_sp);
    sprintf(pefile.Dosheader.e_csum,"%04x", (pefile.Dosheader.dosheader).e_csum);
    sprintf(pefile.Dosheader.e_ip,"%04x", (pefile.Dosheader.dosheader).e_ip);
    sprintf(pefile.Dosheader.e_cs,"%04x", (pefile.Dosheader.dosheader).e_cs);
    sprintf(pefile.Dosheader.e_lfarlc,"%04x", (pefile.Dosheader.dosheader).e_lfarlc);
    sprintf(pefile.Dosheader.e_ovno,"%04x", (pefile.Dosheader.dosheader).e_ovno);
    sprintf(pefile.Dosheader.e_res,"%04x", (pefile.Dosheader.dosheader).e_res[0]);
    sprintf(pefile.Dosheader.e_oemid,"%04x", (pefile.Dosheader.dosheader).e_oemid);
    sprintf(pefile.Dosheader.e_oeminfo,"%04x", (pefile.Dosheader.dosheader).e_oeminfo);
    sprintf(pefile.Dosheader.e_res2,"%04x", (pefile.Dosheader.dosheader).e_res2[0]);
    sprintf(pefile.Dosheader.e_lfanew,"%08lx", (pefile.Dosheader.dosheader).e_lfanew);

};

void MyDialog::on_pushButton_clicked()
{
     read(pefile);
     peDosHeaderAnalyze(pefile);
     ui->tableWidget->setColumnCount(6);
     ui->tableWidget->setRowCount(7);
     ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Member"<<"Value"<<"Member"<<"Value"<<"Member"<<"Value");
     ui->tableWidget->setItem(0,0,new QTableWidgetItem("e_magic")); //设置表格内容
     ui->tableWidget->setItem(1,0,new QTableWidgetItem("e_cblp"));
     ui->tableWidget->setItem(2,0,new QTableWidgetItem("e_cp"));
     ui->tableWidget->setItem(3,0,new QTableWidgetItem("e_crlc"));
     ui->tableWidget->setItem(4,0,new QTableWidgetItem("e_cparhdr"));
     ui->tableWidget->setItem(5,0,new QTableWidgetItem("e_minalloc"));
     ui->tableWidget->setItem(6,0,new QTableWidgetItem("e_maxalloc"));
     ui->tableWidget->setItem(0,2,new QTableWidgetItem("e_ss"));
     ui->tableWidget->setItem(1,2,new QTableWidgetItem("e_sp"));
     ui->tableWidget->setItem(2,2,new QTableWidgetItem("e_csum"));
     ui->tableWidget->setItem(3,2,new QTableWidgetItem("e_ip"));
     ui->tableWidget->setItem(4,2,new QTableWidgetItem("e_cs"));
     ui->tableWidget->setItem(5,2,new QTableWidgetItem("e_lfarlc"));
     ui->tableWidget->setItem(0,4,new QTableWidgetItem("e_ovno"));
     ui->tableWidget->setItem(1,4,new QTableWidgetItem("e_res[0]"));
     ui->tableWidget->setItem(2,4,new QTableWidgetItem("e_oemid"));
     ui->tableWidget->setItem(3,4,new QTableWidgetItem("e_oeminfo"));
     ui->tableWidget->setItem(4,4,new QTableWidgetItem("e_res2[0]"));
     ui->tableWidget->setItem(5,4,new QTableWidgetItem("e_lfanew"));
     ui->tableWidget->setItem(0,1,new QTableWidgetItem(pefile.Dosheader.e_magic));
     ui->tableWidget->setItem(1,1,new QTableWidgetItem(pefile.Dosheader.e_cblp));
     ui->tableWidget->setItem(2,1,new QTableWidgetItem(pefile.Dosheader.e_cp));
     ui->tableWidget->setItem(3,1,new QTableWidgetItem(pefile.Dosheader.e_crlc));
     ui->tableWidget->setItem(4,1,new QTableWidgetItem(pefile.Dosheader.e_cparhdr));
     ui->tableWidget->setItem(5,1,new QTableWidgetItem(pefile.Dosheader.e_minalloc));
     ui->tableWidget->setItem(6,1,new QTableWidgetItem(pefile.Dosheader.e_maxalloc));
     ui->tableWidget->setItem(0,3,new QTableWidgetItem(pefile.Dosheader.e_ss));
     ui->tableWidget->setItem(1,3,new QTableWidgetItem(pefile.Dosheader.e_sp));
     ui->tableWidget->setItem(2,3,new QTableWidgetItem(pefile.Dosheader.e_csum));
     ui->tableWidget->setItem(3,3,new QTableWidgetItem(pefile.Dosheader.e_ip));
     ui->tableWidget->setItem(4,3,new QTableWidgetItem(pefile.Dosheader.e_cs));
     ui->tableWidget->setItem(5,3,new QTableWidgetItem(pefile.Dosheader.e_lfarlc));
     ui->tableWidget->setItem(0,5,new QTableWidgetItem(pefile.Dosheader.e_ovno));
     ui->tableWidget->setItem(1,5,new QTableWidgetItem(pefile.Dosheader.e_res));
     ui->tableWidget->setItem(2,5,new QTableWidgetItem(pefile.Dosheader.e_oemid));
     ui->tableWidget->setItem(3,5,new QTableWidgetItem(pefile.Dosheader.e_oeminfo));
     ui->tableWidget->setItem(4,5,new QTableWidgetItem(pefile.Dosheader.e_res2));
     ui->tableWidget->setItem(5,5,new QTableWidgetItem(pefile.Dosheader.e_lfanew));

}
