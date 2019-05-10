#include <stdio.h>
#include<cstring>
#define N 3
struct student
{
	 int id;
	 char name[10];
	 char course[10];
	 double avgscore;
	 double testscore;
	 double sumscore;
};

typedef struct student Student;

void init(Student (*stu)[3]){
    int i;
    strcpy((*stu)[0].name,"����");
    strcpy((*stu)[1].name,"����");
    strcpy((*stu)[2].name,"����");
    strcpy((*stu)[0].course,"����");
    strcpy((*stu)[1].course,"��ѧ");
    strcpy((*stu)[2].course,"Ӣ��");
    printf("����ϵͳ�ܹ���%d��ѧ��\n",N);
    for( i=0;i<N;i++){
        printf("��ֱ������%d��ѧ����ƽʱ�ɼ��Ϳ��Գɼ���\n",i+1);
        scanf("%lf%lf",&((*stu)[i].avgscore),&((*stu)[i].testscore));
        (*stu)[i].id=i+1000;
    }
};
void cal(Student (*stu)[3]){
    int i;
    for( i=0;i<N;i++){
        (*stu)[i].sumscore = ((*stu)[i].avgscore)*0.8+((*stu)[i].testscore)*0.2;
        printf("��%d��ѧ�����ܳɼ�Ϊ%.2lf\n",i+1,(*stu)[i].sumscore);
    }
}
void check(Student (*stu)[3]){
    int i,maxid,minid;
    double max=-100000,min=1000000;
    for( i=0;i<N;i++){
        if((*stu)[i].sumscore>max){
            max=(*stu)[i].sumscore;
            maxid=i;
        }
        if((*stu)[i].sumscore<min){
            min=(*stu)[i].sumscore;
            minid=i;
        }
    }
    printf("�ܷ���ߵ�ѧ��������ϢΪ��ѧ��Ϊ%d,ѧ��Ϊ%s,�γ���Ϊ%s,%.2lf,���Գɼ�Ϊ%.2lf,�����ɼ�Ϊ%.2lf\n",
           (*stu)[maxid].id,(*stu)[maxid].name,(*stu)[maxid].course,(*stu)[maxid].avgscore,(*stu)[maxid].testscore,(*stu)[maxid].sumscore);
    printf("�ܷ���͵�ѧ��������ϢΪ��ѧ��Ϊ%d,ѧ��Ϊ%s,�γ���Ϊ%s,%.2lf,���Գɼ�Ϊ%.2lf,�����ɼ�Ϊ%.2lf\n",
           (*stu)[minid].id,(*stu)[minid].name,(*stu)[minid].course,(*stu)[minid].avgscore,(*stu)[minid].testscore,(*stu)[minid].sumscore);


}
int main(void)
{
    Student stu[N];
    int i;
    init(&stu);
    cal(&stu);
    check(&stu);
	return 0;
}
