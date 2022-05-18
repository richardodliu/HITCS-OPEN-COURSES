#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 10
#define STU_NUM 30
#define COURSE_NUM 6
struct student
{
    long num;
    char name[MAX_LEN];
    float score[COURSE_NUM];
    float sum;
    float aver;
    struct student *next;
};
int Menu(void);
struct student *ReadScore(struct student *head,int n,int m);
void AverSumofEveryStudent(struct student *head,int n,int m);
void AverSumofEveryCourse(struct student *head,int n,int m);
void SortbyScore(struct student *head,int n,int m,int (*compare)(float a,float b));
int Ascending(float a,float b);
int Descending(float a,float b);
void SwapFloat(float *x,float *y);
void SwapLong(long *x,long *y);
void SwapChar(char x[],char y[]);
void AsSortbyNum(struct student *head,int n,int m);
void SortbyName(struct student *head,int n,int m);
void SearchbyNum(struct student *head,int n,int m);
void SearchbyName(struct student *head,int n,int m);
void StatisticAnalysis(struct student *head,int n,int m);
void PrintScore(struct student *head,int n,int m);
void WritetoFile(struct student *head,int n,int m);
void ReadfromFile(struct student *head,int *n,int *m);
int main()
{
    char ch;
    int n=0,m=0;
    struct student *head=NULL;
    printf("Input student number(n<%d):",STU_NUM);
    scanf("%d",&n);
    printf("Input course number(m<=%d):",COURSE_NUM);
    scanf("%d",&m);
    while(1)
    {
        ch=Menu();
        switch(ch)
        {
        case 1:head=ReadScore(head,n,m);
               break;
        case 2:AverSumofEveryCourse(head,n,m);
               break;
        case 3:AverSumofEveryStudent(head,n,m);
               break;
        case 4:SortbyScore(head,n,m,Descending);
               printf("\nSort in descending order by score:\n");
               PrintScore(head,n,m);
               break;
        case 5:SortbyScore(head,n,m,Ascending);
               printf("\nSort in ascending order by score:\n");
               PrintScore(head,n,m);
               break;
        case 6:AsSortbyNum(head,n,m);
               printf("\nSort in ascending order by number:\n");
               PrintScore(head,n,m);
               break;
        case 7:SortbyName(head,n,m);
               printf("\nSort in ascending order by name:\n");
               PrintScore(head,n,m);
               break;
        case 8:SearchbyNum(head,n,m);
               break;
        case 9:SearchbyName(head,n,m);
               break;
        case 10:StatisticAnalysis(head,n,m);
                break;
        case 11:PrintScore(head,n,m);
                break;
        case 12:WritetoFile(head,n,m);
                break;
        case 13:ReadfromFile(head,&n,&m);
                break;
        case 0:printf("End of program!");
               exit(0);
        default:printf("Input error!");
        }
    }
    return 0;
}
int Menu(void)
{
    int itemSelected;
    printf("Management for Students' scores\n");
    printf("1.Input record\n");
    printf("2.Calculate total and average score of every course\n");
    printf("3.Calculate total and average score of every student\n");
    printf("4.Sort in descending order by score\n");
    printf("5.Sort in ascending order by score\n");
    printf("6.Sort in ascending order by number\n");
    printf("7.Sort in dictionary order by name\n");
    printf("8.Search by number\n");
    printf("9.Search by name\n");
    printf("10.Statistic analysis\n");
    printf("11.List record\n");
    printf("12.Write to a file\n");
    printf("13.Read from a file\n");
    printf("0.Exit\n");
    printf("Please Input your choice:");
    scanf("%d",&itemSelected);
    return itemSelected;
}
struct student *ReadScore(struct student *head,int n,int m)
{
    struct student *p=NULL,*rear=NULL;
    int i=0,j;
    printf("Input students' ID,name and score:\n");
    while (i<n)
    {
        p=(struct student *)malloc(sizeof(struct student));
        if (p==NULL)
        {
            printf("No enough memory!\n");
            exit(0);
        }
        scanf("%ld%s",&p->num,p->name);
        for(j=0;j<m;j++)
        {
            scanf("%f",&p->score[j]);
        }
        if (head==NULL) head=p;
        else rear->next=p;
        rear=p;
        i++;
    }
    if (rear!=NULL)
    {
        rear->next=NULL;
    }
    return head;
    return head;
}
void AverSumofEveryStudent(struct student *head,int n,int m)
{
    int i=0,j;
    struct student *p=head;
    while (p!=NULL)
    {
        i++;
        p->sum=0;
        for(j=0;j<m;j++)
        {
            p->sum=p->sum+p->score[j];
        }
        p->aver=m>0?p->sum/m:-1;
        printf("student %d:sum=%.0f,aver=%.0f\n",i,p->sum,p->aver);
        p=p->next;
    }
}
void AverSumofEveryCourse(struct student *head,int n,int m)
{
    int j;
    float sum[COURSE_NUM],aver[COURSE_NUM];
    for(j=0;j<m;j++)
    {
        struct student *p=head;
        sum[j]=0;
        while (p!=NULL)
        {
            sum[j]=sum[j]+p->score[j];
            p=p->next;
        }
        aver[j]=n>0?sum[j]/n:-1;
        printf("course %d:sum=%.0f,aver=%.0f\n",j+1,sum[j],aver[j]);
    }
}
void SortbyScore(struct student *head,int n,int m,int (*compare)(float a,float b))
{
    struct student *i,*j,*k;
    int t;
    for(i=head;i!=NULL;i=i->next)
    {
        k=i;
        for(j=i->next;j!=NULL;j=j->next)
        {
            if((*compare)(j->sum,k->sum)) k=j;
        }
        if(k!=i)
        {
            for(t=0;t<m;t++)
            {
                SwapFloat(&k->score[t],&i->score[t]);
            }
            SwapFloat(&k->sum,&i->sum);
            SwapFloat(&k->aver,&i->aver);
            SwapLong(&k->num,&i->num);
            SwapChar(k->name,i->name);
        }
    }
}
int Ascending(float a,float b)
{
    return a<b;
}
int Descending(float a,float b)
{
    return a>b;
}
void SwapFloat(float *x,float *y)
{
    float temp;
    temp=*x;
    *x=*y;
    *y=temp;
}
void SwapLong(long *x,long *y)
{
    long temp;
   temp=*x;
    *x=*y;
    *y=temp;
}
void SwapChar(char x[],char y[])
{
    char temp[MAX_LEN];
    strcpy(temp,x);
    strcpy(x,y);
    strcpy(y,temp);
}
void AsSortbyNum(struct student *head,int n,int m)
{
    struct student *i,*j,*k;
    int t;
    for(i=head;i!=NULL;i=i->next)
    {
        k=i;
        for(j=i->next;j!=NULL;j=j->next)
        {
            if(j->num<k->num) k=j;
        }
        if(k!=i)
        {
            for(t=0;t<m;t++)
            {
                SwapFloat(&k->score[t],&i->score[t]);
            }
            SwapFloat(&k->sum,&i->sum);
            SwapFloat(&k->aver,&i->aver);
            SwapLong(&k->num,&i->num);
            SwapChar(k->name,i->name);
        }
    }
}
void SortbyName(struct student *head,int n,int m)
{
    struct student *i,*j;
    int t;
    for(i=head;i!=NULL;i=i->next)
    {
        for(j=i->next;j!=NULL;j=j->next)
        {
            if(strcmp(j->name,i->name)<0)
            {
                for(t=0;t<m;t++)
                {
                    SwapFloat(&i->score[t],&j->score[t]);
                }
                SwapFloat(&i->sum,&j->sum);
                SwapFloat(&i->aver,&j->aver);
                SwapLong(&i->num,&j->num);
                SwapChar(i->name,j->name);
            }
        }
    }
}
void SearchbyNum(struct student *head,int n,int m)
{
    long number;
    struct student *i;
    int j;
    printf("Input the number you want to search:");
    scanf("%ld",&number);
    for(i=head;i!=NULL;i=i->next)
    {
        if(i->num==number)
        {
            printf("%ld\t%s\t",number,i->name);
            for(j=0;j<m;j++)
            {
                printf("%.0f\t",i->score[j]);
            }
            printf("%.0f\t%.0f\n",i->sum,i->aver);
            return;
        }
    }
    printf("\nNot Found!\n");
}
void SearchbyName(struct student *head,int n,int m)
{
    char x[MAX_LEN];
    struct student *i;
    int j;
    printf("Input the name you want to search:");
    scanf("%s",x);
    for(i=head;i!=NULL;i=i->next)
    {
        if(strcmp(i->name,x)==0)
        {
            printf("%ld\t%s\t",i->num,i->name);
            for(j=0;j<m;j++)
            {
                printf("%.0f\t",i->score[j]);
            }
            printf("%.0f\t%.0f\n",i->sum,i->aver);
            return;
        }

    }
    printf("\nNot found!\n");
}
void StatisticAnalysis(struct student *head,int n,int m)
{
    int j,k,total,t[6];
    struct student *i;
    for(j=0;j<m;j++)
    {
        printf("For course %d:\n",j+1);
        memset(t,0,sizeof(t));
        for(i=head;i!=NULL;i=i->next)
        {
            if(i->score[j]>=0&&i->score[j]<60) t[0]++;
            else if(i->score[j]<70)            t[1]++;
            else if(i->score[j]<80)            t[2]++;
            else if(i->score[j]<90)            t[3]++;
            else if(i->score[j]<100)           t[4]++;
            else if(i->score[j]==100)          t[5]++;
        }
        for(total=0,k=0;k<=5;k++)
        {
            total=total+t[k];
        }
        for(k=0;k<=5;k++)
        {
            if(k==0)printf("<60\t%d\t%.2f%%\n",t[k],(float)t[k]/n*100);
            else if(k==5) printf("%d\t%d\t%.2f%%\n",(k+5)*10,t[k],(float)t[k]/n*100);
            else printf("%d-%d\t%d\t%.2f%%\n",(k+5)*10,(k+5)*10+9,t[k],(float)t[k]/n*100);
        }
    }
}
void PrintScore(struct student *head,int n,int m)
{
    struct student *i;
    int j;
    for(i=head;i!=NULL;i=i->next)
    {
        printf("%ld\t%s\t",i->num,i->name);
        for(j=0;j<m;j++)
        {
            printf("%.0f\t",i->score[j]);
        }
        printf("%.0f\t%.0f\n",i->sum,i->aver);
    }
}
void WritetoFile(struct student *head,int n,int m)
{
    FILE *fp;
    struct student *i;
    int j;
    if ((fp = fopen("student.txt","w")) == NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    fprintf(fp,"%d\t%d\n",n,m);
    for(i=head;i!=NULL;i=i->next)
    {
        fprintf(fp,"%10ld%10s",i->num,i->name);
        for(j=0;j<m;j++)
        {
            fprintf(fp,"%10.0f",i->score[j]);
        }
        fprintf(fp,"%10.0f%10.0f\n",i->sum,i->aver);
    }
    fclose(fp);
}
void ReadfromFile(struct student *head,int *n,int *m)
{
    FILE *fp;
    struct student *i;
    int j;
    if ((fp = fopen("student.txt","w")) == NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    fscanf(fp,"%d\t%d\n",n,m);
    for(i=head;i!=NULL;i=i->next)
    {
        fscanf(fp,"%10ld",&i->num);
        fscanf(fp,"%10s",i->name);
        for(j=0;j<*m;j++)
        {
            fscanf(fp,"%10f",&i->score[j]);
        }
        fscanf(fp,"%10f%10f\n",&i->sum,&i->aver);
    }
    fclose(fp);
}
