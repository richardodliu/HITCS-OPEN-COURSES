#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct thing/*定义*/{
    char name[20];
    char brand[20];
    float price;
    int num;
    struct thing *next;
};
void SwapFloat(float *x,float *y){
    float temp;
    temp=*x;
    *x=*y;
    *y=temp;
}
void SwapInt(int *x,int *y){
    int temp;
    temp=*x;
    *x=*y;
    *y=temp;
}
void SwapChar(char x[],char y[]){
    char temp[20];
    strcpy(temp,x);
    strcpy(x,y);
    strcpy(y,temp);
}
void sortbyprice(struct thing *head)/*排序*/{
    struct thing *i,*j,*k;
    for(i=head;i!=NULL;i=i->next)
    {
        k=i;
        for(j=i->next;j!=NULL;j=j->next)
        {
            if((j->price)<(k->price)) k=j;
        }
        if(k!=i)
        {
            SwapInt(&k->num,&i->num);
            SwapFloat(&k->price,&i->price);
            SwapChar(k->brand,i->brand);
            SwapChar(k->name,i->name);
        }
    }
}
struct thing *create(struct thing*head)/*创建链表*/{
    struct thing *rear=NULL,*p=NULL;
    head=NULL;
    FILE *fp;
    char a[10];
    printf("请输入文件名(不超过10个字符):");
    scanf("%s",a);
    if ((fp=fopen(a, "rb"))==NULL) {
        printf("cannot open this file.\n");
        return head;
    }
    p=(struct thing*)malloc(sizeof(struct thing));
    if (p==NULL) {
        puts("error.");
        exit(0);
    }
    while(feof(fp)==0)
    {
        if (head==NULL) {
            head=p;
        }
        else rear->next=p;
        rear=p;
        p=(struct thing*)malloc(sizeof(struct thing));
        if (p==NULL) {
            puts("error.\n");
            exit(0);
        }
        fscanf(fp,"%s",rear->name);
        fscanf(fp,"%s",rear->brand);
        fscanf(fp,"%f",&rear->price);
        fscanf(fp,"%d",&rear->num);
    }
    if (rear!=NULL) {
        rear->next=NULL;
    }
    printf("创建结束\n");
    fclose(fp);
    /*进入排序*/
    sortbyprice(head);
    head=head->next;
    return head;
}
void print(struct thing*head)/*打印*/{
    struct thing *p=head;
    if (head==NULL) {
        printf("空表!\n");
        return;
    }
    while (p!=NULL) {
        if(p->num==0)
        {
            p=p->next;
            continue;
        }
        printf("姓名:%s 品牌:%s 单价:%.f 数量:%d\n",p->name,p->brand,p->price,p->num);
        p=p->next;
    }
}
struct thing *insert(struct thing*head)/*插入*/{
    struct thing *ps,*p,*q;
    ps=(struct thing*)malloc(sizeof(struct thing));
    if (ps==NULL) {
        puts("error");
        exit(0);
    }
    printf("请输入商品姓名:");
    scanf("%s",ps->name);
    printf("请输入商品品牌:");
    scanf("%s",ps->brand);
    printf("请输入商品单价:");
    scanf("%f",&ps->price);
    printf("请输入商品数量:");
    scanf("%d",&ps->num);
    if (head==NULL) {
        head=ps;
        ps->next=NULL;
        return head;
    }
    else if (head->price>=ps->price){
        ps->next=head;
        head=ps;
        return head;
    }
    p=q=head;
    while (p!=NULL&&p->price<ps->price) {
        q=p;
        p=p->next;
    }
    q->next=ps;
    ps->next=p;
    return head;
}
struct thing *delete(struct thing*head)/*删除*/{
    char str[20];
    printf("请输入您想删除的名称:");
    scanf("%s",str);
    struct thing *p=head,*q=head;
    while (strcmp(p->name,str)!=0) {
        if (p==NULL) {
            printf("无此记录");
            return head;
        }
        q=p;
        p=p->next;
    }
    q->next=p->next;
    free(p);
    /*进入排序*/
    sortbyprice(head);
    return head;
}
struct thing *change(struct thing*head)/*修改*/{
    int k;
    char str[20];
    printf("请输入您想修改的名称:");
    scanf("%s",str);
    struct thing *p=head;
    while (p!=NULL) {
        if(strcmp(p->name,str)==0)
        {
        printf("姓名:%s 品牌:%s 单价:%.f 数量:%d\n",p->name,p->brand,p->price,p->num);
        printf("请输入你想要修改的内容：1.单价 2.数目");
        scanf("%d",&k);
        switch(k)
        {
        case 1:
            printf("请输入当前单价");
            scanf("%f",&p->price);
            printf("姓名:%s 品牌:%s 单价:%.f 数量:%d\n",p->name,p->brand,p->price,p->num);
            break;
        case 2:
            printf("请输入当前数目");
            scanf("%d",&p->num);
            printf("姓名:%s 品牌:%s 单价:%.f 数量:%d\n",p->name,p->brand,p->price,p->num);
            break;
        default:
            break;
        }
        break;
        }
        else p=p->next;
    }
    if (p==NULL)
    {
        printf("无此记录");
        return head;
    }
    /*进入排序*/
    sortbyprice(head);
    return head;
}
void namesort(struct thing *head)/*查找名字*/{
    char str[20];
    printf("请输入您想查找的姓名:");
    scanf("%s",str);
    struct thing *p=head;
    while (p!=NULL) {
        if (strcmp(p->name,str)==0) {
            printf("姓名:%s 品牌:%s 单价:%f 数量:%d\n",p->name,p->brand,p->price,p->num);
            return;
        }
        p=p->next;
    }
    printf("无此记录\n");
}
void brandsort(struct thing *head)/*查找品牌*/{
    int n=0;
    char str[20];
    printf("请输入您想查找的品牌:");
    scanf("%s",str);
    struct thing *p=head;
    while (p!=NULL) {
        if (strcmp(p->brand,str)==0) {
            printf("姓名:%s 品牌:%s 单价:%f 数量:%d\n",p->name,p->brand,p->price,p->num);
            n++;
        }
        p=p->next;
    }
    if(n==0 && p==NULL)
    {
        printf("无此记录\n");
        return;
    }
    else return;
}
void sort(struct thing *head)/*查找*/{
    int l;
    printf("1.查找指定名字记录\n2.查找指定品牌记录\n");
    scanf("%d",&l);
    switch (l) {
        case 1:
            namesort(head);
            break;
        case 2:
            brandsort(head);
            break;
        default:
            break;
    }
    return;
}
void Write(struct thing *head)/*写入*/{
    FILE *fp;
    struct thing *p=head;
    char a[10];
    printf("请输入文件名(不超过10个字符):");
    scanf("%s",a);
    if ((fp=fopen(a, "wb+"))==NULL) {
        printf("cannot open this file.");
        exit(0);
    }
    while (p!=NULL) {
        fprintf(fp,"%s %s %.f %d\n",p->name,p->brand,p->price,p->num);
        p=p->next;
    }
    fclose(fp);
    printf("文件名是:%s\n",a);
}
int main(){
    struct thing *head=NULL;
    int k;
    add: printf("1.创建记录链表\n2.打印全部记录\n3.插入一条新的记录\n4.删除一条记录\n5.查找记录\n6.修改数据\n7.将信息写入磁盘文件\n0.退出程序\n");
    scanf("%d",&k);
    switch (k) {
        case 1:
            head=create(head);
            break;
        case 2:
            print(head);
            break;
        case 3:
            head=insert(head);
            break;
        case 4:
            head=delete(head);
            break;
        case 5:
            sort(head);
            break;
        case 6:
            head=change(head);
            break;
        case 7:
            Write(head);
            break;
        case 0:
            return 0;
        default:
            break;
    }
    goto add;
}
