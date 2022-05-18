#include <stdio.h>
#include <stdlib.h>
#define maxsize 1024

int LIST[maxsize];
int m;
int n;

typedef struct BSTcell
{
    int key;
    struct BSTcell *lchild;
    struct BSTcell *rchild;
}BSTNode;

typedef BSTNode *BST;

BST F1;
BST F2;

int BSTsearch(int k,BST F)
{
    n++;
    if(F==NULL)
        return -2;
    else if(k==F->key)
    {
        return k;
    }
    if(k<F->key)
        return(BSTsearch(k,F->lchild));
    else
        return(BSTsearch(k,F->rchild));
}

void BSTinsert(int k,BST *F)
{
    if(*F==NULL)
    {
        *F=(BST)malloc(sizeof(BSTNode));
        (*F)->key=k;
        (*F)->lchild=NULL;
        (*F)->rchild=NULL;
        return;
    }
    else if(k<(*F)->key){
        BSTinsert(k,&((*F)->lchild));
    }
    else if(k>(*F)->key){
        BSTinsert(k,&((*F)->rchild));
    }
    else if(k==(*F)->key){
        return;
    }
}

int BSTdeletemin(BST F)//返回最小值并删除
{
    int tmp;
    BST p;
    if(F->lchild==NULL)//找到最左节点
    {
        p=F;
        tmp=F->key;
        F=F->rchild;
        free(p);
        return tmp;
    }
    else
        return(BSTdeletemin(F->lchild));
}

void BSTdeleteB(int k,BST F)//
{
    if(F!=NULL)
    {
        if(k<F->key)
            BSTdeleteB(k,F->lchild);
        else if(k>F->key)
            BSTdeleteB(k,F->rchild);//找到B节点
        else /*找到了！k==key*/
            if(F->rchild==NULL)
                F=F->lchild;
            else if(F->lchild==NULL)
                F=F->rchild;
            else/*被删除节点有左右子树，选右子树中的最小节点继承*/
                F->key=BSTdeletemin(F->rchild);
    }

}

void Binarycreat(BST F)//通过中序遍历建立数组
{
    if(F==NULL)
        return;
    Binarycreat(F->lchild);
    LIST[m++]=F->key;
    Binarycreat(F->rchild);
}

int Binarysearch(int k,int last)
{
    int low,up,mid;
    low=0;
    up=last;
    while(low<=up)
    {n++;
        mid=(low+up)/2;
        if(LIST[mid]==k)
            return mid;
        else if (LIST[mid]>k)
            up=mid-1;
        else
            low=mid+1;
    }
    return -1;
}

int main()
{
    int i;
    BST F1=NULL;
    BST F2=NULL;
    int data[maxsize];
    for(i=1; i<=maxsize; i++) //给F1赋值，顺序排列的1024个奇数
    {
        BSTinsert(2*i-1,&F1);
        data[i-1]=2*i-1;
    }
    for(i=0; i<maxsize; i++) //给F2赋值，乱序排列的1024个奇数
    {
        int index=rand()%(maxsize-i);//始终保持随机生成的下标为数组的前半部分
        if(data[index]!=-1)
        {
            BSTinsert(data[index],&F2);
            data[index]=data[maxsize-i-1];
            data[maxsize-i-1]=-1;//始终保持数组的前半部分为没有取过的数字
        }
    }
    printf("F1 and F2 have been created!\n");
    int sum1f[10000]= {0},sum1s[10000]= {0},sum2f[10000]= {0},sum2s[10000]= {0};
    for(i=0; i<10000; i++)//作10000次查找实验，记录失败与成功的查找长度
    {
        int k=rand()%(2*maxsize);
        n=0;
        if(BSTsearch(k,F1)==-2)
        {
            sum1f[i]=n;
        }
        else
            sum1s[i]=n;
        n=0;
        if(BSTsearch(k,F2)==-2)
            sum2f[i]=n;
        else
            sum2s[i]=n;
    }
    int sum1=0,sum2=0,sum1n=0,sum2n=0;
    for(i=0; i<10000; i++)//计算失败平均查找长度
    {
        if(sum1f[i]!=0)
        {
            sum1=sum1+sum1f[i];
            sum1n++;
        }
        if(sum2f[i]!=0)
        {
            sum2=sum2+sum2f[i];
            sum2n++;
        }
    }
    printf("the avery fail step of F1:%d\n",sum1/sum1n);
    printf("the avery fail step of F2:%d\n",sum2/sum2n);
    sum1=0,sum2=0,sum1n=0,sum2n=0;
    for(i=0; i<10000; i++)//计算成功平均查找长度
    {
        if(sum1s[i]!=0)
        {
            sum1=sum1+sum1s[i];
            sum1n++;
        }
        if(sum2s[i]!=0)
        {
            sum2=sum2+sum2s[i];
            sum2n++;
        }
    }
    printf("the avery sucess step of F1:%d\n",sum1/sum1n);
    printf("the avery sucess step of F2:%d\n",sum2/sum2n);
    Binarycreat(F1);
    printf("LIST has been created!\n");
    int sumf[10000]= {0},sums[10000]= {0};
    for(int i=0; i<10000; i++)//作10000次查找实验，记录失败与成功的查找长度
    {
        int k=rand()%(maxsize*2);
        n=0;
        if( Binarysearch(k,1023)==-1)
            sumf[i]=n;
        else
            sums[i]=n;
    }
    int sum=0,sumn=0;
    for(int i=0; i<10000; i++)//计算失败平均查找长度
    {
        if(sumf[i]!=0)
        {
            sum=sum+sumf[i];
            sumn++;
        }
    }
    printf("the avery fail step of LIST:%d\n",sum/sumn);
    sum=0,sumn=0;
    for(int i=0; i<10000; i++)//计算成功平均查找长度
    {
        if(sums[i]!=0)
        {
            sum=sum+sums[i];
            sumn++;
        }
    }
    printf("the avery sucess step of LIST:%d\n",sum/sumn);
    return 0;
}
