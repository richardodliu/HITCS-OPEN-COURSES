#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
typedef struct Grades
{
    char n[20];
    int gb;
    int gg;
    int tg;
    int num;
} GRADES;
void gotoxy(int x, int y)
{
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}
void calculate(int b[21][21],int g[21][21],int gradeboy[],int gradegirl[],int gradeall[],int boy,int girl,int school)
{
    int i,j,res=0;
    for(i=1; i<=school; i++)
    {
        for(j=1; j<=boy; j++)
            res+=b[i][j];
        gradeboy[i]=res;
        res=0;
    }
    for(i=1; i<=school; i++)
    {
        for(j=1; j<=girl; j++)
            res+=g[i][j];
        gradegirl[i]=res;
        res=0;
    }
    for(i=1; i<=school; i++)
        gradeall[i]=gradeboy[i]+gradegirl[i];
}
int showmenu()
{
    int cond;
    system("cls");
    printf("1.按学院编号排序查看信息\n");
    printf("2.按男子总分排序查看信息\n");
    printf("3.按女子总分排序查看信息\n");
    printf("4.按学院总分排序查看信息\n");
    printf("5.查询某学院的详细信息\n");
    printf("6.查询某项目的详细信息\n");
    printf("7.定义学院名称\n");
    printf("8.存储数据\n");
    printf("9.退出程序\n");
    do
    {
        printf("请输入功能序号:");
        scanf("%d",&cond);
        getchar();
    }
    while(cond>9||cond<1);
    return cond;
}
void showall(GRADES info[],int school)
{
    int i;
    for(i=1; i<=school; i++)
    {
        printf("学院名称:%s  学院编号:%d\n",info[i].n,i);
        printf("男子得分:%d  女子得分:%d  总分:%d\n",info[i].gb,info[i].gg,info[i].tg);
        info++;
    }
    printf("请按回车键继续！\n");
    getchar();

}
int main()
{
    FILE *fp=fopen("1.txt","a+");
    int school,boy,girl;
    int cond,p,i,j;
    int s1,s2,s3,s4,s5;
    int gradeboy[21]= {0};
    int gradegirl[21]= {0};
    int gradeall[21]= {0};
    int b[21][21];
    int g[21][21];
    GRADES info[21];
    GRADES temp;
    for(i=0; i<21; i++)
    {
        for(j=0; j<21; j++)
        {
            b[i][j]=0;
            g[i][j]=0;
        }
    }
    int TOFb[21]= {0};
    int TOFg[21]= {0};
    char choice;
    printf("是否要从文件中读取数据？（请将文件命名为in.txt，并放在项目文件夹中）\n");
    printf("输入Y或y表示读入，输入其他表示不读入：");
    scanf("%c",&choice);
    if(choice=='Y'||choice=='y')
        freopen("in.txt","r",stdin);
    do
    {
        printf("请指定学院数目：（介于5到20之间）");
        scanf("%d",&school);
        getchar();
    }
    while(school>20||school<5);
    do
    {
        printf("请指定男子项目个数：（不大于20）");
        scanf("%d",&boy);
        getchar();
    }
    while(boy>20||boy<1);
    do
    {
        printf("请指定女子项目个数：（不大于20）");
        scanf("%d",&girl);
        getchar();
    }
    while(girl>20||girl<1);
    printf("学院数目:%d\n男子项目:%d\n女子项目:%d\n",school,boy,girl);
    printf("请按回车键继续！");
    getchar();
    printf("请指定哪些男子项目进行前三名积分\n输入编号，以空格或回车分隔\n以不合法的数据结尾：\n");
    while(1)
    {
        scanf("%d",&p);
        getchar();
        if(p>boy||p<=0)
            break;
        TOFb[p]=1;
    }
    printf("以下男子项目将按前三名积分:\n");
    for(i=1; i<=boy; i++)
    {
        if(TOFb[i]==1)
            printf("%d  ",i);
    }
    printf("\n请指定哪些女子项目进行前三名积分\n输入编号，以空格或回车分隔\n以不合法的数据结尾：\n");
    while(1)
    {
        scanf("%d",&p);
        p=p-boy;
        getchar();
        if(p>girl||p<=0)
            break;
        TOFg[p]=1;
    }
    printf("以下女子项目将按前三名积分:\n");
    for(i=1; i<=girl; i++)
    {
        if(TOFg[i]==1)
            printf("%d  ",i+boy);
    }
    printf("\n请按回车键继续！");
    getchar();
    printf("\n请依次输入男子项目的成绩\n");
    for(i=1; i<=boy; i++)
    {
        if(TOFb[i]==1)
        {
            printf("请输入男子项目%d的前三名学院编号,以空格键分隔\n",i);
            do
            {
                scanf("%d %d %d",&s1,&s2,&s3);
                getchar();
                cond=s1<1||s2<1||s3<1||s1>school||s2>school||s3>school||s1==s2||s2==s3||s1==s3;
                if(cond)
                    printf("您输入的数据不合法，请重新输入！");
            }
            while(cond);
            b[s1][i]+=5;
            b[s2][i]+=3;
            b[s3][i]+=2;
        }
        else
        {
            printf("请输入男子项目%d的前五名学院编号,以空格键分隔\n",i);
            do
            {
                scanf("%d %d %d %d %d",&s1,&s2,&s3,&s4,&s5);
                getchar();
                cond=s1<1||s2<1||s3<1||s4<1||s5<1||s1>school||s2>school||s3>school||s4>school||s5>school;
                if(cond)
                    printf("您输入的数据不合法，请重新输入！");
            }
            while(cond);
            b[s1][i]+=7;
            b[s2][i]+=5;
            b[s3][i]+=3;
            b[s4][i]+=2;
            b[s5][i]+=1;
        }
    }
    printf("请依次输入女子项目的成绩\n");
    for(i=1; i<=girl; i++)
    {
        if(TOFg[i]==1)
        {
            printf("请输入女子项目%d的前三名学院编号,以空格键分隔\n",i+boy);
            do
            {
                scanf("%d %d %d",&s1,&s2,&s3);
                getchar();
                cond=s1<1||s2<1||s3<1||s1>school||s2>school||s3>school||s1==s2||s2==s3||s1==s3;
                if(cond)
                    printf("您输入的数据不合法，请重新输入！");
            }
            while(cond);
            g[s1][i]+=5;
            g[s2][i]+=3;
            g[s3][i]+=2;
        }
        else
        {
            printf("请输入女子项目%d的前五名学院编号,以空格键分隔\n",i+boy);
            do
            {
                scanf("%d %d %d %d %d",&s1,&s2,&s3,&s4,&s5);
                getchar();
                cond=s1<1||s2<1||s3<1||s4<1||s5<1||s1>school||s2>school||s3>school||s4>school||s5>school;
                if(cond)
                    printf("您输入的数据不合法，请重新输入！");
            }
            while(cond);
            g[s1][i]+=7;
            g[s2][i]+=5;
            g[s3][i]+=3;
            g[s4][i]+=2;
            g[s5][i]+=1;
        }
    }
    freopen("CON","r",stdin);
    printf("输入完成！");

    calculate(b,g,gradeboy,gradegirl,gradeall,boy,girl,school);
    for(i=1; i<=school; i++)
    {
        info[i].gb=gradeboy[i];
        info[i].gg=gradegirl[i];
        info[i].tg=gradeall[i];
        info[i].num=i;
        strcpy(info[i].n,"undifined");
    }
    while(1)
    {
        cond=showmenu();
        switch(cond)
        {
        case 1:
            for(i=1; i<school; i++)
            {
                for(j=i; j<=school; j++)
                {
                    if(info[i].num>info[j].num)
                    {
                        temp=info[i];
                        info[i]=info[j];
                        info[j]=temp;
                    }
                }
            }
            for(i=1; i<=school; i++)
            {
                printf("学院名称:%s  学院编号:%d  ",info[i].n,info[i].num);
                printf("男子得分:%d  女子得分:%d  总分:%d\n",info[i].gb,info[i].gg,info[i].tg);
            }
            printf("请按回车键继续!");
            getchar();
            break;
        case 2:
            for(i=1; i<school; i++)
            {
                for(j=i; j<=school; j++)
                {
                    if(info[i].gb<info[j].gb)
                    {
                        temp=info[i];
                        info[i]=info[j];
                        info[j]=temp;
                    }
                }
            }
            for(i=1; i<=school; i++)
            {
                printf("学院名称:%s  学院编号:%d  ",info[i].n,info[i].num);
                printf("男子得分:%d  女子得分:%d  总分:%d\n",info[i].gb,info[i].gg,info[i].tg);
            }
            printf("请按回车键继续！\n");
            getchar();
            break;
        case 3:
            for(i=1; i<school; i++)
            {
                for(j=i; j<=school; j++)
                {
                    if(info[i].gg<info[j].gg)
                    {
                        temp=info[i];
                        info[i]=info[j];
                        info[j]=temp;
                    }
                }
            }
            for(i=1; i<=school; i++)
            {
                printf("学院名称:%s  学院编号:%d  ",info[i].n,info[i].num);
                printf("男子得分:%d  女子得分:%d  总分:%d\n",info[i].gb,info[i].gg,info[i].tg);
            }
            printf("请按回车键继续！\n");
            getchar();
            break;
        case 4:
            for(i=1; i<school; i++)
            {
                for(j=i; j<=school; j++)
                {
                    if(info[i].tg<info[j].tg)
                    {
                        temp=info[i];
                        info[i]=info[j];
                        info[j]=temp;
                    }
                }
            }
            for(i=1; i<=school; i++)
            {
                printf("学院名称:%s  学院编号:%d  ",info[i].n,info[i].num);
                printf("男子得分:%d  女子得分:%d  总分:%d\n",info[i].gb,info[i].gg,info[i].tg);
            }
            printf("请按回车键继续！\n");
            getchar();
            break;
        case 5:
            for(i=1; i<school; i++)
            {
                for(j=i; j<=school; j++)
                {
                    if(info[i].num>info[j].num)
                    {
                        temp=info[i];
                        info[i]=info[j];
                        info[j]=temp;
                    }
                }
            }
            do
            {
                printf("请输入要查找的学院编号！");
                scanf("%d",&i);
                getchar();
            }
            while(i<1||i>school);
            printf("学院名称:%s  学院编号:%d  ",info[i].n,info[i].num);
            printf("男子得分:%d  女子得分:%d  总分:%d\n",info[i].gb,info[i].gg,info[i].tg);
            printf("男子项目得分详情:");
            for(j=1; j<=boy; j++)
            {
                printf("%d  ",b[info[i].num][j]);
            }
            printf("\n女子项目得分详情:");
            for(j=1; j<=girl; j++)
            {
                printf("%d  ",g[info[i].num][j]);
            }
            printf("请按回车键继续！");
            getchar();
            break;
        case 6:
            for(i=1; i<school; i++)
            {
                for(j=i; j<=school; j++)
                {
                    if(info[i].num>info[j].num)
                    {
                        temp=info[i];
                        info[i]=info[j];
                        info[j]=temp;
                    }
                }
            }
            do
            {
                printf("请输入要查找的项目编号！");
                scanf("%d",&i);
                getchar();
            }
            while(i<1||i>boy+girl);
            printf("各学院的得分详情:\n");
            if(i<=boy)
            {
                printf("此项目为男生项目\n");
                for(j=1; j<=school; j++)
                    printf("%d  ",b[j][i]);
            }
            else
            {
                printf("此项目为女生项目\n");
                i=i-boy;
                for(j=1; j<=school; j++)
                    printf("%d  ",g[j][i]);
            }
            printf("请按回车键继续");
            getchar();
            break;
        case 7:
            for(i=1; i<school; i++)
            {
                for(j=i; j<=school; j++)
                {
                    if(info[i].num>info[j].num)
                    {
                        temp=info[i];
                        info[i]=info[j];
                        info[j]=temp;
                    }
                }
            }
            do
            {
                printf("请输入要更改名称的学院编号！");
                scanf("%d",&i);
                getchar();
            }
            while(i<1||i>school);
            printf("请输入名称（不要超过10个字）:");
            scanf("%s",info[i].n);
            getchar();
            printf("操作完成，按回车键继续");
            getchar();
            break;
        case 8:
            for(i=1; i<school; i++)
            {
                for(j=i; j<=school; j++)
                {
                    if(info[i].num>info[j].num)
                    {
                        temp=info[i];
                        info[i]=info[j];
                        info[j]=temp;
                    }
                }
            }

            for(i=1; i<=school; i++)
            {
                fprintf(fp,"学院名称:%s  学院编号:%d  ",info[i].n,info[i].num);
                fprintf(fp,"男子得分:%d  女子得分:%d  总分:%d\n",info[i].gb,info[i].gg,info[i].tg);
            }
            printf("文件已经存储为1.txt,请先退出程序后再查看！");
            getchar();
            break;
        case 9:
            break;
        }
        if(cond==9)
            break;
    }
}
