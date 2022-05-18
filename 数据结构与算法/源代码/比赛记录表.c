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
    printf("1.��ѧԺ�������鿴��Ϣ\n");
    printf("2.�������ܷ�����鿴��Ϣ\n");
    printf("3.��Ů���ܷ�����鿴��Ϣ\n");
    printf("4.��ѧԺ�ܷ�����鿴��Ϣ\n");
    printf("5.��ѯĳѧԺ����ϸ��Ϣ\n");
    printf("6.��ѯĳ��Ŀ����ϸ��Ϣ\n");
    printf("7.����ѧԺ����\n");
    printf("8.�洢����\n");
    printf("9.�˳�����\n");
    do
    {
        printf("�����빦�����:");
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
        printf("ѧԺ����:%s  ѧԺ���:%d\n",info[i].n,i);
        printf("���ӵ÷�:%d  Ů�ӵ÷�:%d  �ܷ�:%d\n",info[i].gb,info[i].gg,info[i].tg);
        info++;
    }
    printf("�밴�س���������\n");
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
    printf("�Ƿ�Ҫ���ļ��ж�ȡ���ݣ����뽫�ļ�����Ϊin.txt����������Ŀ�ļ����У�\n");
    printf("����Y��y��ʾ���룬����������ʾ�����룺");
    scanf("%c",&choice);
    if(choice=='Y'||choice=='y')
        freopen("in.txt","r",stdin);
    do
    {
        printf("��ָ��ѧԺ��Ŀ��������5��20֮�䣩");
        scanf("%d",&school);
        getchar();
    }
    while(school>20||school<5);
    do
    {
        printf("��ָ��������Ŀ��������������20��");
        scanf("%d",&boy);
        getchar();
    }
    while(boy>20||boy<1);
    do
    {
        printf("��ָ��Ů����Ŀ��������������20��");
        scanf("%d",&girl);
        getchar();
    }
    while(girl>20||girl<1);
    printf("ѧԺ��Ŀ:%d\n������Ŀ:%d\nŮ����Ŀ:%d\n",school,boy,girl);
    printf("�밴�س���������");
    getchar();
    printf("��ָ����Щ������Ŀ����ǰ��������\n�����ţ��Կո��س��ָ�\n�Բ��Ϸ������ݽ�β��\n");
    while(1)
    {
        scanf("%d",&p);
        getchar();
        if(p>boy||p<=0)
            break;
        TOFb[p]=1;
    }
    printf("����������Ŀ����ǰ��������:\n");
    for(i=1; i<=boy; i++)
    {
        if(TOFb[i]==1)
            printf("%d  ",i);
    }
    printf("\n��ָ����ЩŮ����Ŀ����ǰ��������\n�����ţ��Կո��س��ָ�\n�Բ��Ϸ������ݽ�β��\n");
    while(1)
    {
        scanf("%d",&p);
        p=p-boy;
        getchar();
        if(p>girl||p<=0)
            break;
        TOFg[p]=1;
    }
    printf("����Ů����Ŀ����ǰ��������:\n");
    for(i=1; i<=girl; i++)
    {
        if(TOFg[i]==1)
            printf("%d  ",i+boy);
    }
    printf("\n�밴�س���������");
    getchar();
    printf("\n����������������Ŀ�ĳɼ�\n");
    for(i=1; i<=boy; i++)
    {
        if(TOFb[i]==1)
        {
            printf("������������Ŀ%d��ǰ����ѧԺ���,�Կո���ָ�\n",i);
            do
            {
                scanf("%d %d %d",&s1,&s2,&s3);
                getchar();
                cond=s1<1||s2<1||s3<1||s1>school||s2>school||s3>school||s1==s2||s2==s3||s1==s3;
                if(cond)
                    printf("����������ݲ��Ϸ������������룡");
            }
            while(cond);
            b[s1][i]+=5;
            b[s2][i]+=3;
            b[s3][i]+=2;
        }
        else
        {
            printf("������������Ŀ%d��ǰ����ѧԺ���,�Կո���ָ�\n",i);
            do
            {
                scanf("%d %d %d %d %d",&s1,&s2,&s3,&s4,&s5);
                getchar();
                cond=s1<1||s2<1||s3<1||s4<1||s5<1||s1>school||s2>school||s3>school||s4>school||s5>school;
                if(cond)
                    printf("����������ݲ��Ϸ������������룡");
            }
            while(cond);
            b[s1][i]+=7;
            b[s2][i]+=5;
            b[s3][i]+=3;
            b[s4][i]+=2;
            b[s5][i]+=1;
        }
    }
    printf("����������Ů����Ŀ�ĳɼ�\n");
    for(i=1; i<=girl; i++)
    {
        if(TOFg[i]==1)
        {
            printf("������Ů����Ŀ%d��ǰ����ѧԺ���,�Կո���ָ�\n",i+boy);
            do
            {
                scanf("%d %d %d",&s1,&s2,&s3);
                getchar();
                cond=s1<1||s2<1||s3<1||s1>school||s2>school||s3>school||s1==s2||s2==s3||s1==s3;
                if(cond)
                    printf("����������ݲ��Ϸ������������룡");
            }
            while(cond);
            g[s1][i]+=5;
            g[s2][i]+=3;
            g[s3][i]+=2;
        }
        else
        {
            printf("������Ů����Ŀ%d��ǰ����ѧԺ���,�Կո���ָ�\n",i+boy);
            do
            {
                scanf("%d %d %d %d %d",&s1,&s2,&s3,&s4,&s5);
                getchar();
                cond=s1<1||s2<1||s3<1||s4<1||s5<1||s1>school||s2>school||s3>school||s4>school||s5>school;
                if(cond)
                    printf("����������ݲ��Ϸ������������룡");
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
    printf("������ɣ�");

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
                printf("ѧԺ����:%s  ѧԺ���:%d  ",info[i].n,info[i].num);
                printf("���ӵ÷�:%d  Ů�ӵ÷�:%d  �ܷ�:%d\n",info[i].gb,info[i].gg,info[i].tg);
            }
            printf("�밴�س�������!");
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
                printf("ѧԺ����:%s  ѧԺ���:%d  ",info[i].n,info[i].num);
                printf("���ӵ÷�:%d  Ů�ӵ÷�:%d  �ܷ�:%d\n",info[i].gb,info[i].gg,info[i].tg);
            }
            printf("�밴�س���������\n");
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
                printf("ѧԺ����:%s  ѧԺ���:%d  ",info[i].n,info[i].num);
                printf("���ӵ÷�:%d  Ů�ӵ÷�:%d  �ܷ�:%d\n",info[i].gb,info[i].gg,info[i].tg);
            }
            printf("�밴�س���������\n");
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
                printf("ѧԺ����:%s  ѧԺ���:%d  ",info[i].n,info[i].num);
                printf("���ӵ÷�:%d  Ů�ӵ÷�:%d  �ܷ�:%d\n",info[i].gb,info[i].gg,info[i].tg);
            }
            printf("�밴�س���������\n");
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
                printf("������Ҫ���ҵ�ѧԺ��ţ�");
                scanf("%d",&i);
                getchar();
            }
            while(i<1||i>school);
            printf("ѧԺ����:%s  ѧԺ���:%d  ",info[i].n,info[i].num);
            printf("���ӵ÷�:%d  Ů�ӵ÷�:%d  �ܷ�:%d\n",info[i].gb,info[i].gg,info[i].tg);
            printf("������Ŀ�÷�����:");
            for(j=1; j<=boy; j++)
            {
                printf("%d  ",b[info[i].num][j]);
            }
            printf("\nŮ����Ŀ�÷�����:");
            for(j=1; j<=girl; j++)
            {
                printf("%d  ",g[info[i].num][j]);
            }
            printf("�밴�س���������");
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
                printf("������Ҫ���ҵ���Ŀ��ţ�");
                scanf("%d",&i);
                getchar();
            }
            while(i<1||i>boy+girl);
            printf("��ѧԺ�ĵ÷�����:\n");
            if(i<=boy)
            {
                printf("����ĿΪ������Ŀ\n");
                for(j=1; j<=school; j++)
                    printf("%d  ",b[j][i]);
            }
            else
            {
                printf("����ĿΪŮ����Ŀ\n");
                i=i-boy;
                for(j=1; j<=school; j++)
                    printf("%d  ",g[j][i]);
            }
            printf("�밴�س�������");
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
                printf("������Ҫ�������Ƶ�ѧԺ��ţ�");
                scanf("%d",&i);
                getchar();
            }
            while(i<1||i>school);
            printf("���������ƣ���Ҫ����10���֣�:");
            scanf("%s",info[i].n);
            getchar();
            printf("������ɣ����س�������");
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
                fprintf(fp,"ѧԺ����:%s  ѧԺ���:%d  ",info[i].n,info[i].num);
                fprintf(fp,"���ӵ÷�:%d  Ů�ӵ÷�:%d  �ܷ�:%d\n",info[i].gb,info[i].gg,info[i].tg);
            }
            printf("�ļ��Ѿ��洢Ϊ1.txt,�����˳�������ٲ鿴��");
            getchar();
            break;
        case 9:
            break;
        }
        if(cond==9)
            break;
    }
}
