#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct thing/*����*/{
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
void sortbyprice(struct thing *head)/*����*/{
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
struct thing *create(struct thing*head)/*��������*/{
    struct thing *rear=NULL,*p=NULL;
    head=NULL;
    FILE *fp;
    char a[10];
    printf("�������ļ���(������10���ַ�):");
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
    printf("��������\n");
    fclose(fp);
    /*��������*/
    sortbyprice(head);
    head=head->next;
    return head;
}
void print(struct thing*head)/*��ӡ*/{
    struct thing *p=head;
    if (head==NULL) {
        printf("�ձ�!\n");
        return;
    }
    while (p!=NULL) {
        if(p->num==0)
        {
            p=p->next;
            continue;
        }
        printf("����:%s Ʒ��:%s ����:%.f ����:%d\n",p->name,p->brand,p->price,p->num);
        p=p->next;
    }
}
struct thing *insert(struct thing*head)/*����*/{
    struct thing *ps,*p,*q;
    ps=(struct thing*)malloc(sizeof(struct thing));
    if (ps==NULL) {
        puts("error");
        exit(0);
    }
    printf("��������Ʒ����:");
    scanf("%s",ps->name);
    printf("��������ƷƷ��:");
    scanf("%s",ps->brand);
    printf("��������Ʒ����:");
    scanf("%f",&ps->price);
    printf("��������Ʒ����:");
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
struct thing *delete(struct thing*head)/*ɾ��*/{
    char str[20];
    printf("����������ɾ��������:");
    scanf("%s",str);
    struct thing *p=head,*q=head;
    while (strcmp(p->name,str)!=0) {
        if (p==NULL) {
            printf("�޴˼�¼");
            return head;
        }
        q=p;
        p=p->next;
    }
    q->next=p->next;
    free(p);
    /*��������*/
    sortbyprice(head);
    return head;
}
struct thing *change(struct thing*head)/*�޸�*/{
    int k;
    char str[20];
    printf("�����������޸ĵ�����:");
    scanf("%s",str);
    struct thing *p=head;
    while (p!=NULL) {
        if(strcmp(p->name,str)==0)
        {
        printf("����:%s Ʒ��:%s ����:%.f ����:%d\n",p->name,p->brand,p->price,p->num);
        printf("����������Ҫ�޸ĵ����ݣ�1.���� 2.��Ŀ");
        scanf("%d",&k);
        switch(k)
        {
        case 1:
            printf("�����뵱ǰ����");
            scanf("%f",&p->price);
            printf("����:%s Ʒ��:%s ����:%.f ����:%d\n",p->name,p->brand,p->price,p->num);
            break;
        case 2:
            printf("�����뵱ǰ��Ŀ");
            scanf("%d",&p->num);
            printf("����:%s Ʒ��:%s ����:%.f ����:%d\n",p->name,p->brand,p->price,p->num);
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
        printf("�޴˼�¼");
        return head;
    }
    /*��������*/
    sortbyprice(head);
    return head;
}
void namesort(struct thing *head)/*��������*/{
    char str[20];
    printf("������������ҵ�����:");
    scanf("%s",str);
    struct thing *p=head;
    while (p!=NULL) {
        if (strcmp(p->name,str)==0) {
            printf("����:%s Ʒ��:%s ����:%f ����:%d\n",p->name,p->brand,p->price,p->num);
            return;
        }
        p=p->next;
    }
    printf("�޴˼�¼\n");
}
void brandsort(struct thing *head)/*����Ʒ��*/{
    int n=0;
    char str[20];
    printf("������������ҵ�Ʒ��:");
    scanf("%s",str);
    struct thing *p=head;
    while (p!=NULL) {
        if (strcmp(p->brand,str)==0) {
            printf("����:%s Ʒ��:%s ����:%f ����:%d\n",p->name,p->brand,p->price,p->num);
            n++;
        }
        p=p->next;
    }
    if(n==0 && p==NULL)
    {
        printf("�޴˼�¼\n");
        return;
    }
    else return;
}
void sort(struct thing *head)/*����*/{
    int l;
    printf("1.����ָ�����ּ�¼\n2.����ָ��Ʒ�Ƽ�¼\n");
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
void Write(struct thing *head)/*д��*/{
    FILE *fp;
    struct thing *p=head;
    char a[10];
    printf("�������ļ���(������10���ַ�):");
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
    printf("�ļ�����:%s\n",a);
}
int main(){
    struct thing *head=NULL;
    int k;
    add: printf("1.������¼����\n2.��ӡȫ����¼\n3.����һ���µļ�¼\n4.ɾ��һ����¼\n5.���Ҽ�¼\n6.�޸�����\n7.����Ϣд������ļ�\n0.�˳�����\n");
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
