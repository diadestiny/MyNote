#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int a,char* argv[])
{
    if(strcmp(argv[2],"+")==0)
        printf("%d",atoi(argv[1])+atoi(argv[3]));
    if(strcmp(argv[2],"-")==0)
        printf("%d",atoi(argv[1])-atoi(argv[3]));
    if(strcmp(argv[2],"*")==0)
        printf("%d",atoi(argv[1])*atoi(argv[3]));
    if(strcmp(argv[2],"/")==0){
        if(strcmp(argv[3],"0")==0){
                printf("��������Ϊ0,�Ƿ�");
            return 0;
        }
         printf("%.2lf",atof(argv[1])/atof(argv[3]));
    }
    return 0;
}
