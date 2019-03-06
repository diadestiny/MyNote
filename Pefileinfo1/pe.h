#ifndef PE_H
#define PE_H

#include <windows.h>
#include<QString>
#include<class.h>
#include<qfiledialog.h>


class Pefile
{
public:
     QString name;
     DosHeader Dosheader;//这是我定义的类
     FileHeader FileHeader;
     OptionalHeader OptionalHeader;
     Sechdr Sechdr,Sechdr1;
     IMAGE_DATA_DIRECTORY data;
     Imp Import;
     DeBug debug;
     TSL tsl;
     EXP exp;
     Reloc relocation;
     unsigned long pesig;
     char Signature [100];

};
void peDosHeaderAnalyze(Pefile &pefile);
void peFileHeaderAnalyze(Pefile &pefile);
void peOptionalHeaderAnalyze(Pefile &pefile);
void peSectionHeaderAnaylze(Pefile &pefile);
//int* peImportAnaylze(Pefile &pefile,int a[]);
//int NUMIDD(Pefile &pefile)
long getRVA (Pefile &pefile,int num);
void read(Pefile&);
BOOL isPevaild(Pefile & pefile);
bool ExitFile(const QString &fileName);

#endif // PE_H
