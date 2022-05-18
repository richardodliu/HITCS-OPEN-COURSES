#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 37
#define M 73

typedef struct htnode{ // �����
    double weight ; // Ȩֵ
    char ch;
    int lchild; // ������
    int rchild; // �Һ�����
    int parent; // ˫����
}huffmant;/*��������*/

typedef struct codenoye{
    char ch; //�洢��������ַ�
    char bits[10]; //�ַ�����λ��
}huffmantcode;/*����������*/

void creatht(huffmant ht[]);
void initht(huffmant ht[]);
void charsethuffmanencoding(huffmant ht[],huffmantcode h[]);
void selectmin(huffmant ht[],int n,int *p1,int *p2);
void write(huffmantcode h[]);
void read(huffmant ht[],huffmantcode h[]);

int main()
{
    huffmant ht[M];
    huffmantcode h[N];/*�����������*/
    creatht(ht);
    charsethuffmanencoding(ht,h);
    for(int i=0;i<N;i++)
    {
        printf("%c ",h[i].ch);
        printf("%s\n",h[i].bits);
    }
    for(int i=0;i<M;i++)
    {
        printf("%c ",ht[i].ch);
        printf("%d ",ht[i].lchild);
        printf("%d ",ht[i].parent);
        printf("%d\n",ht[i].rchild);
    }
    write(h);
    read(ht,h);
    return 0;
}

void creatht(huffmant ht[])//����huffam��,t[m-1]Ϊ���
{
    int i,p1,p2;
    initht(ht); //��ʼ��������Ȩֵ
    for(i=N;i<M;i++)
    { //n-1�κϲ�
        selectmin(ht,i-1,&p1,&p2);
        ht[p1].parent=i;
        ht[p2].parent=i;
        ht[i].lchild=p1;
        ht[i].rchild=p2;
        ht[i].weight=ht[p1].weight+ht[p2].weight;
    }
}

void charsethuffmanencoding(huffmant ht[],huffmantcode h[])
{ //����Huffman��T ��Huffman����� H
    int c,p,i,j,k; // c ��p �ֱ�ָʾT �к��Ӻ�˫�׵�λ��
    char cd[100]; // ��ʱ��ű���
    int start; // ָʾ������cd �е�λ��
    cd[99]='\0'; // ���������
    for(i=0;i<N; i++)
    { // ������Ҷ��T[i]�ı���
    h[i].ch=ht[i].ch; // ����Ҷ��T[i]��Ӧ���ַ�
    start=99; // ������ʼλ�õĳ�ֵ
    c=i; // ��Ҷ��T[i]��ʼ����
    p=ht[c].parent;
    while(ht[c].parent>=0)
        {// ֱ�����ݵ�T[c]������λ��
            start--;
            if(ht[p].lchild==c)
            {
                cd[start]='0';
            }
            else cd[start]='1';
            // ��T[c]��T[p]�����ӣ������ɴ���0���������ɴ���1
            c=p; // ��������
            p=ht[c].parent;
        }
        for(j=0,k=start;k<=99;k++,j++)
        {
            h[i].bits[j]=cd[k];
        }
    }
}

void initht(huffmant ht[])
{
    FILE *fp;
    char a[10];
    char p[N];
    p[0]='a';
    p[1]='b';
    p[2]='c';
    p[3]='d';
    p[4]='e';
    p[5]='f';
    p[6]='g';
    p[7]='h';
    p[8]='i';
    p[9]='j';
    p[10]='k';
    p[11]='l';
    p[12]='m';
    p[13]='n';
    p[14]='o';
    p[15]='p';
    p[16]='q';
    p[17]='r';
    p[18]='s';
    p[19]='t';
    p[20]='u';
    p[21]='v';
    p[22]='w';
    p[23]='x';
    p[24]='y';
    p[25]='z';
    p[26]=',';
    p[27]='.';
    p[28]='!';
    p[29]='?';
    p[30]='"';
    p[31]=':';
    p[32]=';';
    p[33]='(';
    p[34]=')';
    p[35]='`';
    p[36]=' ';
    int q[N]={0};
    int sum=0;
    double r[N]={0};
    char ch;
    printf("�������ļ���(������10���ַ�):");
    scanf("%s",a);
    if ((fp=fopen(a, "rb"))==NULL)
        {
            printf("cannot open this file.\n");
        }
    while(feof(fp)==0)
    {
        fscanf(fp,"%c",&ch);
        if(ch>='a' && ch<='z')
        {
            q[ch-'a']++;
        }
        else if(ch>='A' && ch<='Z')
        {
            q[ch-'A']++;
        }
        else
        {
            switch(ch)
            {
            case ',':
                q[26]++;
                break;
            case '.':
                q[27]++;
                break;
            case '!':
                q[28]++;
                break;
            case '?':
                q[29]++;
                break;
            case '"':
                q[30]++;
                break;
            case ':':
                q[31]++;
                break;
            case ';':
                q[32]++;
                break;
            case '(':
                q[33]++;
                break;
            case ')':
                q[34]++;
                break;
            case '`':
                q[35]++;
                break;
            case ' ':
                q[36]++;
                break;
            }
        }
        sum++;
    }
    fclose(fp);
    int i;
    for(i=0;i<N;i++)
    {
        r[i]=(double)q[i]/sum;
    }
    for(i=0;i<N;i++)
    {
        ht[i].lchild=-1;
        ht[i].parent=-1;
        ht[i].rchild=-1;
        ht[i].weight=r[i];
        ht[i].ch=p[i];
    }
    for(i=N;i<M;i++)
    {
        ht[i].lchild=-1;
        ht[i].parent=-1;
        ht[i].rchild=-1;
        ht[i].weight=0;
        ht[i].ch=' ';
    }
}

void selectmin(huffmant ht[],int n,int *p1,int *p2)
{
    int i,j;
    for(i=0;i<=n;i++)
    {
        if(ht[i].parent==-1)
        {
            *p1=i;
            break;
        }
    }
    for(j=i+1;j<=n;j++)
    {
        if(ht[j].parent==-1)
        {
            *p2=j;
            break;
        }
    }
    for(i=0;i<=n;i++)
    {
        if((ht[*p1].weight>ht[i].weight) && (ht[i].parent==-1) && (*p2!=i))
        {
            *p1=i;
        }
    }
    for(j=0;j<=n;j++)
    {
        if((ht[*p2].weight>ht[j].weight) && (ht[j].parent==-1) && (*p1!=j))
        {
            *p2=j;
        }
    }
}

void write(huffmantcode h[])
{
    FILE *fp1,*fp2;
    char a[10],b[10];
    char c;
    int i;
    printf("�������ȡ�ļ���(������10���ַ�):");
    scanf("%s",a);
    if ((fp1=fopen(a, "rb"))==NULL)
        {
            printf("cannot open this file.\n");
        }
    printf("������д���ļ���(������10���ַ�):");
    scanf("%s",b);
    if ((fp2=fopen(b, "wb+"))==NULL)
        {
            printf("cannot open this file.\n");
        }
    while(feof(fp1)==0)
    {
        fscanf(fp1,"%c",&c);
        if(c>='A' && c<='Z') c=c+32;
        for(i=0;i<N;i++)
        {
            if(h[i].ch==c)
            {
                fprintf(fp2,"%s",h[i].bits);
                printf("%s\n",h[i].bits);
                break;
            }
        }

    }
    fclose(fp1);
    fclose(fp2);
}

void read(huffmant ht[],huffmantcode h[])
{
    FILE *fp1,*fp2;
    char a[10],b[10];
    int p;
    char x;
    printf("�������ȡ�ļ���(������10���ַ�):");
    scanf("%s",a);
    if ((fp1=fopen(a, "rb"))==NULL)
        {
            printf("cannot open this file.\n");
        }
    printf("������д���ļ���(������10���ַ�):");
    scanf("%s",b);
    if ((fp2=fopen(b, "wb+"))==NULL)
        {
            printf("cannot open this file.\n");
        }
    while(feof(fp1)==0)
    {
        p=M-1;
        while(1)
        {
           if(ht[p].lchild==-1 && ht[p].rchild==-1)
           {
               fprintf(fp2,"%c",ht[p].ch);
               break;
           }
           fscanf(fp1,"%c",&x);
           if(x=='0')
           {
               p=ht[p].lchild;
           }
           else p=ht[p].rchild;
        }
    }
    fclose(fp1);
    fclose(fp2);
}
