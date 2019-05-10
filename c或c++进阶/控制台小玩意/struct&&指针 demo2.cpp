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
    strcpy((*stu)[0].name,"张三");
    strcpy((*stu)[1].name,"李四");
    strcpy((*stu)[2].name,"王五");
    strcpy((*stu)[0].course,"语文");
    strcpy((*stu)[1].course,"数学");
    strcpy((*stu)[2].course,"英语");
    printf("管理系统总共有%d个学生\n",N);
    for( i=0;i<N;i++){
        printf("请分别输入第%d个学生的平时成绩和考试成绩：\n",i+1);
        scanf("%lf%lf",&((*stu)[i].avgscore),&((*stu)[i].testscore));
        (*stu)[i].id=i+1000;
    }
};
void cal(Student (*stu)[3]){
    int i;
    for( i=0;i<N;i++){
        (*stu)[i].sumscore = ((*stu)[i].avgscore)*0.8+((*stu)[i].testscore)*0.2;
        printf("第%d个学生的总成绩为%.2lf\n",i+1,(*stu)[i].sumscore);
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
    printf("总分最高的学生个人信息为：学号为%d,学号为%s,课程名为%s,%.2lf,考试成绩为%.2lf,总评成绩为%.2lf\n",
           (*stu)[maxid].id,(*stu)[maxid].name,(*stu)[maxid].course,(*stu)[maxid].avgscore,(*stu)[maxid].testscore,(*stu)[maxid].sumscore);
    printf("总分最低的学生个人信息为：学号为%d,学号为%s,课程名为%s,%.2lf,考试成绩为%.2lf,总评成绩为%.2lf\n",
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
