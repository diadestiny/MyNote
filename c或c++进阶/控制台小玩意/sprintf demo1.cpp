#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
int n=10;
int a,b,c,sum=0,j=0;
char ans1[10],ans2[10];
char d;
void mycal();
int main()
{
    mycal();
	return 0;
}
void mycal(){
 srand(time(NULL));
 while(n--){
       a=rand()%10+1;
       b=rand()%10+1;
       if(a<b){
        n++;
        continue;
       }
       c=rand()%4+1;
   switch(c){
   case 1:
       d='+';
       sprintf(ans2,"%d",a+b);
       break;
   case 2:
       d='-';

       sprintf(ans2,"%d",a-b);
       break;
   case 3:
       d='*';
       sprintf(ans2,"%d",a*b);
       break;
   case 4:
        d='/';
        sprintf(ans2,"%.2lf",(double)a/b);
        break;
       }
        printf("������%d %c %d �Ľ��(���Ϊ����,������2λ��Ч����):\n",a,d,b);
        scanf("%s",ans1);
        getchar();
        if(strcmp(ans1,ans2)==0){
            printf("Right!\n");
            sum+=10;

        }
        else{
            printf("Not correct!\n");
            j++;
        }

    }
    printf("�ܷ�Ϊ%d(100����),������Ϊ%d\n",sum,j);
}
