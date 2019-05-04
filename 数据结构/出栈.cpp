#include<bits/stdc++.h>
int index(char s[],char t[]){
    int i=0,j=0;
    while(i<strlen(s) && j<strlen(t)){
        if(s[i]==s[j]){
            i++;
            j++;
        }
        else{
            i=i-(j-1)+1;
            j=0;
        }
    }
    if(j>strlen(t)){
        return i-strlen(t);
    }
    else return 0;

}
int main(){

     char S[]="Mynameisbruceforce";//Ö÷´®
     char T[]="bruce";//×Ó´®
     int pos=index(S,T); //Î»ÖÃ
     printf("%d",pos);


    return 0;
}
