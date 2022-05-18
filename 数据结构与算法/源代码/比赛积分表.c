//在有n个选手P1,P2,P3,... ,Pn参加的单循环赛中，每对选手之间非胜即负。现要求求出一个选手序列: P1’,P2’,P3’,... ,Pn’,其满足 Pi’胜Pi+1’(i=1,... ,n-1)。
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n,i,j,temp;
    int a[21][21];
    for(i=0;i<=20;i++)
    {
        for(j=0;j<=20;j++)
        {
            a[i][j]=0;
        }
    }
    typedef struct
    {
        int num;
        int score;
    }SCORE;
    SCORE s[21];
    SCORE temps;
    printf("How many athletes?(less than 20)");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        for(j=i+1;j<=n;j++)
        {
            printf("athlete %d and athlete %d who is the winner?",i,j);
            do
            {
                scanf("%d",&temp);
            }while(temp!=i&&temp!=j);
            if(temp==i)
                a[i][j]=1;
            else if(temp==j)
                a[j][i]=1;
        }
    }
    temp=0;
    for(i=1;i<=n;i++)
    {
        for(j=0;j<=n;j++)
            temp+=a[i][j];
        s[i].num=i;
        s[i].score=temp;
        temp=0;
    }
    for(i=1;i<n;i++)
    {
        for(j=i;j<=n;j++)
        {
            if(s[i].score<s[j].score)
            {
                temps=s[i];
                s[i]=s[j];
                s[j]=temps;
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        printf("NO.%d Score:%d Ranking:%d\n",s[i].num,s[i].score,i);
    }
    system("pause");
}
