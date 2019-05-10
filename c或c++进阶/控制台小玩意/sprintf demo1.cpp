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
        printf("请输入%d %c %d 的结果(如果为除法,仅保留2位有效数字):\n",a,d,b);
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
    printf("总分为%d(100分制),错题数为%d\n",sum,j);
}
