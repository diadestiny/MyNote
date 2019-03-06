#ifndef DOSHEADER_H
#define DOSHEADER_H
#include <windows.h>
#include<QString>
#include<vector>
class DosHeader
{
public:
       IMAGE_DOS_HEADER dosheader;
       char e_magic[100];
       char e_cblp[100];
       char e_cp[100];
       char e_crlc[100];
       char e_cparhdr[100];
       char e_minalloc[100];
       char e_maxalloc[100];
       char e_ss[100];
       char e_sp[100];
       char e_csum[100];
       char e_ip[100];
       char e_cs[100];
       char e_lfarlc[100];
       char e_ovno[100];
       char e_res[100];
       char e_oemid[100];
       char e_oeminfo[100];
       char e_res2[100];
       char e_lfanew[100];

};

class FileHeader
{
public:
    IMAGE_FILE_HEADER fileheader;
    char* Machine = new char[100];
    char* NumberOfSections = new char[100];
    char* TimeDateStamp = new char[100];
    char* PointerToSymbolTable = new char[100];
    char* NumberOfSymbols = new char[100];
    char* SizeOfOptionalHeader = new char[100];
    char* Characteristics = new char[100];
};
class OptionalHeader
{
public:
   IMAGE_OPTIONAL_HEADER32 opthdr32;
   IMAGE_OPTIONAL_HEADER64 opthdr64;
   char Magic[100];
   char ImageBase [100];
   char Subsystem [100];
   char AddressOfEntryPoint [100];
   char SizeOfCode [100];
   char SizeOfImage  [100];
   char SizeOfHeaders [100];
   char SectionAlignment [100];
   char FileAlignment [100];
   char Dataaddress [16][100];
   char Datasize [16][100];

};
class Sechdr
{
public:
    IMAGE_SECTION_HEADER sechdr;
    char Name [30][100];
    char Viradd [30][100];
    char SizeofRawdata [30] [100];
    char PtrRaw [30][100];
    char Character [30][100];
};
class Imp
{
public:
    IMAGE_IMPORT_DESCRIPTOR iid;
    IMAGE_THUNK_DATA32 data32;
    IMAGE_THUNK_DATA64 data64;
    IMAGE_IMPORT_BY_NAME byname;
    char Namerva [50][80];
    char FirstThunk [50][80];
    char ForwarderChain [50][80];
    char TimeDateStamp [50][80];
    char OFT [50][80];
    char Name [80][60];
    char Hint [1500][10];
    char Name2[1500][50];
};
class DeBug
{
public:
    IMAGE_DEBUG_DIRECTORY deb;
    char Character[100];
    char TimeDate[100];
    char MaxVer[100];
    char MinVer[100];
    char Type[100];
    char Sizeofdata[100];
    char AddRawData[100];
    char PtrRawData[100];
};
class TSL
{
public:
    IMAGE_TLS_DIRECTORY32 tls32;
    IMAGE_TLS_DIRECTORY64 tls64;
    char Start[100];
    char End[100];
    char AddIndex[100];
    char address[100];
    char sizeofzero[100];
    char character[100];

};
class EXP
{
public:
    IMAGE_EXPORT_DIRECTORY export1;
    char Character[100];
    char TimeDate[100];
    char MaxVer[100];
    char MinVer[100];
    char Namerva [100];
    char Name[100];
    char base[100];
    char numfunc[100];
    char numname[100];
    char addfun[100];
    char addname[100];
    char addnameord[100];
    char funcname[100];
};
class Reloc
{
public:
    IMAGE_BASE_RELOCATION rel;
    char RVA[100];
    char Size[100];
    char Item[100];

};

#endif // DOSHEADER_H
