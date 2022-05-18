#include <stdio.h>
#include <stdlib.h>

#define N 100
#define max 2147483647

typedef struct Graph{
	int point[N]; //�����
	int line[N][N];
	//�ڽӾ��󡪱߱�, ����Ϊ����֮��Ĺ�ϵ
	int n; //ͼ�Ķ�����
	int m;//ͼ�ı���
}graph;

typedef struct Path{
    int r[100];
}path;

graph c;
//�㷨1ʹ��
int d1[N];
int p1[N];
int s1[N];
//�㷨2ʹ��
int a2[N][N];
int p2[N][N];

int a3[N][N];

//�������ܣ������ڽӾ���
void creategragh()
{
	FILE *file = NULL;
	int x,y,i,j,t;
	if ((file = fopen("C:\\Users\\61472\\Desktop\\work\\show\\a.txt", "r+")) == NULL)
	{
		printf("a.txt�ļ���ʧ�ܣ������˳���\n");
		exit(0);
	}
	fscanf(file, "%d %d\n",&c.n,&c.m);
	for(i=1;i<=c.n;i++)
    {
        for(j=1;j<=c.n;j++)
        {
            if(j==i) c.line[i][j]=0;
            else c.line[i][j]=max;
        }
    }
	for (i=1;i<=c.m;i++)
	{
		fscanf(file, "%d %d %d\n",&x,&y,&t);
		c.line[x][y]=t;
	}
	fclose(file);
}

int min(int d1[],int s1[])
{
    int i;
    int t=max;
    int w=2;
    for(i=2;i<=c.n;i++)
    {
        if(!s1[i]&&d1[i]<=t)
        {
            t=d1[i];
            w=i;
        }
    }
    return w;
}

void Dijkstra()
{
    int i,v,w,sum=0;
    /*��ʼ��*/
    for(i=1;i<=c.n;i++)
    {
        d1[i]=c.line[1][i];//D[i]��ʾԴ��1������i����̾��룬��ʼʱd[i]=line[1][i]
        p1[i]=1;//p[i]��ʾԴ��1������i�����·���ϵ�ǰ����µ����һ���㣬��ʼʱp[i]=1
        s1[i]=0;//���Դ��������ɵ��յ�
    }
    s1[1]=1;
    for(i=1;i<=c.n-1;i++)
    {
        w=min(d1,s1);
        s1[w]=1;
        for(v=2;v<=c.n;v++)
        {
            if(s1[v]!=1)
            {
                if(c.line[w][v]==max) sum=max;
                else sum=d1[w]+c.line[w][v];
                if(sum<d1[v])
                {
                    d1[v]=sum;
                    p1[v]=w;
                }
            }
        }
    }
}

void Floyd()
{
    int i,j,k;
    for(i=1;i<=c.n;i++)
    {
        for(j=1;j<=c.n;j++)
        {
            a2[i][j]=c.line[i][j];
            p2[i][j]=0;
            if(c.line[i][j]!=max) a3[i][j]=1;
            else a3[i][j]=0;
        }
    }
    for(k=1;k<=c.n;k++)
    {
        for(i=1;i<=c.n;i++)
        {
            for(j=1;j<=c.n;j++)
            {
                if((a2[i][k]+a2[k][j]<a2[i][j]) && a2[i][k]!=max && a2[k][j]!=max)
                {
                    a2[i][j]=a2[i][k]+a2[k][j];
                    p2[i][j]=k;
                }
                if(a3[i][k]==1 && a3[k][j]==1) a3[i][j]=a3[i][k]*a3[k][j];
            }
        }
    }
}

void getPath(int i ,int j)
{
    if(i==j) return;
    if(p2[i][j]==0) printf("%d ",j);
    else{
        getPath(i,p2[i][j]);
        getPath(p2[i][j],j);
    }
}

int main()
{
    int i,j;
    creategragh();
    Dijkstra();
    Floyd();
    for(i=2;i<=c.n;i++)
    {
        if(d1[i]==max) printf("1->%d:-1 ",i);
        else printf("1->%d:%d ",i,d1[i]);
    }
    printf("\n");
    for(i=1;i<=c.n;i++)
    {
        for(j=1;j<=c.n;j++)
        {
            if(a2[i][j]==max) printf("%d->%d:-1 ",i,j);
            else printf("%d->%d:%d ",i,j,a2[i][j]);
        }
        printf("\n");
    }
    for(i=1;i<=c.n;i++)
    {
        for(j=1;j<=c.n;j++)
        {
            printf("%d->%d:%d ",i,j,a3[i][j]);
        }
        printf("\n");
    }
    printf("��������ź��յ��ţ�");
    scanf("%d %d",&i,&j);
    printf("���·��Ϊ��%d ",i);
    getPath(i,j);
    return 0;
}
