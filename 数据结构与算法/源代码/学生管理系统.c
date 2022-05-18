//
//  main.c
//  学生信息管理系统
//
//  Created by Wang on 2017/12/25.
//  Copyright © 2017年 Wang. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
struct student{
    int number;
    char name[20];
    int gender;
    int age;
    float grade;
    struct student *next;
};
struct student *headinsert(struct student *head)/*头插*/
{
    struct student *p=NULL;
    int no;
    printf("请输入学号:");
    scanf("%d",&no);
    while (no!=0) {
        p=(struct student *)malloc(sizeof(struct student));
        if (p==NULL) {
            puts("error.");
            exit(0);
        }
        p->number=no;
        printf("请输入学生姓名:");
        scanf("%s",p->name);
        printf("请输入学生性别1:男2:女");
        scanf("%d",&p->gender);
        printf("请输入学生年龄:");
        scanf("%d",&p->age);
        printf("请输入成绩:");
        scanf("%f",&p->grade);
        p->next=head;
        head=p;
        printf("请输入下一个学生的学号(0结束创建):");
        scanf("%d",&no);
    }
    return head;
}
struct student*rearinsert(struct student *head)/*尾插*/{
    struct student *p=NULL,*rear=NULL;
    int no;
    printf("请输入学号:");
    scanf("%d",&no);
    while (no!=0) {
        p=(struct student*)malloc(sizeof(struct student));
        if (p==NULL) {
            puts("error.");
            exit(0);
        }
        p->number=no;
        printf("请输入学生姓名:");
        scanf("%s",p->name);
        printf("请输入学生性别1:男2:女");
        scanf("%d",&p->gender);
        printf("请输入学生年龄:");
        scanf("%d",&p->age);
        printf("请输入成绩:");
        scanf("%f",&p->grade);
        if (head==NULL) head=p;
        else rear->next=p;
        rear=p;
        printf("请输入下一个学生的学号(0结束创建):");
        scanf("%d",&no);
    }
    if (rear!=NULL) {
        rear->next=NULL;
    }
    printf("创建结束");
    return head;
}
struct student *order(struct student*head)/*顺序插*/{
    int no;
    struct student *p,*q,*ps=NULL;
    printf("请输入学号:");
    scanf("%d",&no);
    while (no!=0) {
        ps=(struct student*)malloc(sizeof(struct student));
        if (ps==NULL) {
            puts("error");
            exit(0);
        }
        ps->number=no;
        printf("请输入学生姓名:");
        scanf("%s",ps->name);
        printf("请输入学生性别1:男2:女");
        scanf("%d",&ps->gender);
        printf("请输入学生年龄:");
        scanf("%d",&ps->age);
        printf("请输入成绩:");
        scanf("%f",&ps->grade);
        if (head==NULL) {
            head=ps;
            head->next=NULL;
            printf("请输入下一学生的学号:");
            scanf("%d",&no);
            continue;
        }
        if (head->number>ps->number) {
            ps->next=head;
            head=ps;
            printf("请输入下一学生的学号(0结束创建):");
            scanf("%d",&no);
            continue;
        }
        p=q=head;
        while(p!=NULL&&p->number<ps->number) {
            q=p;
            p=p->next;
        }
        q->next=ps;
        ps->next=p;
        printf("请输入下一个学生的学号(0结束创建):");
        scanf("%d",&no);
    }
    return head;
}
struct student *file(struct student *head)/*文件读入插*/{
    struct student *rear=NULL,*p=NULL;
    head=NULL;
    FILE *fp;
    char a[10];
    printf("请输入文件名(不超过10个字符):");
    scanf("%s",a);
    if ((fp=fopen(a, "rb"))==NULL) {
        printf("cannot open this file.");
        return head;
    }
    p=(struct student*)malloc(sizeof(struct student));
    if (p==NULL) {
        puts("error.");
        exit(0);
    }
    fread(p, sizeof(struct student), 1, fp);
    while(feof(fp)==0)
    {
        if (head==NULL) {
            head=p;
        }
        else rear->next=p;
        rear=p;
        printf("当前插入的学生记录为:学号:%d 姓名:%s 性别:%d 年龄:%d 成绩:%f\n",rear->number,rear->name,rear->gender,rear->age,rear->grade);
        p=(struct student*)malloc(sizeof(struct student));
        if (p==NULL) {
            puts("error.");
            exit(0);
        }
        fread(p, sizeof(struct student), 1, fp);
    }
    if (rear!=NULL) {
        rear->next=NULL;
    }
    printf("创建结束\n");
    fclose(fp);
    return head;
}
struct student *create(struct student*head)/*创建链表*/{
    int b;
    printf("1.头插法2.尾插法\n3.创建按学号有序链表4.打开学生信息文件创建链表");
    scanf("%d",&b);
    switch (b) {
        case 1:
            head=headinsert(head);
            break;
        case 2:
            head=rearinsert(head);
            break;
        case 3:
            head=order(head);
            break;
        case 4:
            head=file(head);
            break;
        default:
            break;
    }
    return head;
}
void print(struct student*head)/*打印*/{
    struct student *p=head;
    if (head==NULL) {
        printf("空表!\n");
        return;
    }
    while (p!=NULL) {
        printf("学号:%d 姓名:%s 性别:%d 年龄:%d 成绩:%f\n",p->number,p->name,p->gender,p->age,p->grade);
        p=p->next;
    }
}
struct student *insert(struct student*head){
    struct student *ps,*p,*q;
    ps=(struct student*)malloc(sizeof(struct student));
    if (ps==NULL) {
        puts("error");
        exit(0);
    }
    printf("请输入学号:");
    scanf("%d",&ps->number);
    printf("请输入学生姓名:");
    scanf("%s",ps->name);
    printf("请输入学生性别1:男2:女");
    scanf("%d",&ps->gender);
    printf("请输入学生年龄:");
    scanf("%d",&ps->age);
    printf("请输入成绩:");
    scanf("%f",&ps->grade);
    if (head==NULL) {
        head=ps;
        ps->next=NULL;
        return head;
    }
    else if (head->number>=ps->number){
        ps->next=head;
        head=ps;
        return head;
    }
    p=q=head;
    while (p!=NULL&&p->number<ps->number) {
        q=p;
        p=p->next;
    }
    q->next=ps;
    ps->next=p;
    return head;
}
struct student*sitedelete(struct student *head){
    int n;
    struct student *p=head,*q=head;
    printf("您想删除第几个记录:");
    scanf("%d",&n);
    int i=1;
    while (i<n) {
        q=p;
        p=p->next;
        i++;
    }
    q->next=p->next;
    free(p);
    return head;
}
struct student*numdelete(struct student*head){
    int n;
    printf("请输入您想删除的学号:");
    scanf("%d",&n);
    struct student *p=head,*q=head;
    while (p->number!=n) {
        if (p==NULL) {
            printf("无此记录");
            return head;
        }
        q=p;
        p=p->next;
    }
    q->next=p->next;
    free(p);
    return head;
}
struct student*delete(struct student*head){
    int k;
    printf("1.删除指定位置记录2.删除指定学号记录\n");
    scanf("%d",&k);
    switch (k) {
        case 1:
            head=sitedelete(head);
            break;
        case 2:
            head=numdelete(head);
            break;
        default:
            break;
    }
    return head;
}
void sort(struct student *head)/*查找*/{
    int n;
    printf("请输入您想查找的学号:");
    scanf("%d",&n);
    struct student *p=head;
    while (p!=NULL) {
        if (p->number==n) {
            printf("学号:%d 姓名:%s 性别:%d 年龄:%d 成绩:%f\n",p->number,p->name,p->gender,p->age,p->grade);
            return;
        }
        p=p->next;
    }
    printf("无此记录\n");
    return;
}
void member(struct student *head){
    int i=0;
    struct student *p=head;
    while (p!=NULL) {
        i++;
        p=p->next;
    }
    printf("一共有%d人\n",i);
}
void grade(struct student*head){
    float max,ave,i=0,total=0;
    struct student *p=head;
    max=p->grade;
    while (p!=NULL) {
        total+=p->grade;
        if (p->grade>max) {
            max=p->grade;
        }
        i++;
        p=p->next;
    }
        ave=total/i;
        printf("最高分:%f平均分:%f\n",max,ave);
    }
void fail(struct student*head){
    int i=0;
    struct student *p=head;
    while (p!=NULL) {
        if ((p->grade)<60) {
            i++;
        }
        p=p->next;
    }
    printf("不及格%d人\n",i);
}
void statistics(struct student *head)/*统计*/{
    int k;
    printf("1.统计总人数\n2.统计平均成绩和最高分\n3.统计不及格人数\n");
    scanf("%d",&k);
    switch (k) {
        case 1:
            member(head);
            break;
        case 2:
            grade(head);
            break;
        case 3:
            fail(head);
            break;
        default:
            break;
    }
}
struct student*distroy(struct student*head)/*销毁*/{
    struct student *p=head,*q=head;
    while (p!=NULL) {
        p=p->next;
        free(q);
        q=p;
    }
    return NULL;
}
void rewrite(struct student *head)/*重写*/{
    FILE *fp;
    struct student *p=head;
    char a[10];
    printf("请输入文件名(不超过10个字符):");
    scanf("%s",a);
    if ((fp=fopen(a, "wb+"))==NULL) {
        printf("cannot open this file.");
        exit(0);
    }
    while (p!=NULL) {
        fwrite(p, sizeof(struct student), 1, fp);
        p=p->next;
    }
    fclose(fp);
    printf("文件名是:%s\n",a);
}
void con(struct student *head)/*追加*/{
    FILE *fp;
    struct student *p=head;
    char a[10];
    printf("请输入文件名(不超过10个字符):");
    scanf("%s",a);
    if ((fp=fopen(a,"ab"))==NULL) {
        printf("cannot open this file.");
        exit(0);
    }
    fseek(fp, 0, 2);
    while (p!=NULL) {
        fwrite(p, sizeof(struct student), 1, fp);
        p=p->next;
    }
    fclose(fp);
    printf("文件名 是:%s",a);
}
void del()/*清空*/{
    FILE *fp;
    char a[10];
    printf("请输入文件名(不超过10个字符):");
    scanf("%s",a);
    if ((fp=fopen(a,"w"))==NULL) {
        printf("cannot open this file.");
        exit(0);
    }
    fclose(fp);
}
void Write(struct student *head)/*写入磁盘*/{
    int k;
    printf("1.重写学生文件\n2.追加学生文件\n3.清空学生文件\n");
    scanf("%d",&k);
    switch (k) {
        case 1:
            rewrite(head);
            break;
        case 2:
            con(head);
            break;
        case 3:
            del();
            break;
        default:
            break;
    }
}
void main(){
    struct student *head=NULL;
    int k;
add: printf("1.创建学生记录链表   2.打印全部学生记录\n3.插入一条新的学生记录4.删除一条学生记录\n5.按学号查找学生记录  6.统计\n7.销毁学生链表       8.将学生信息写入磁盘文件\n0.退出程序\n");
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
            statistics(head);
            break;
        case 7:
            head=distroy(head);
            break;
        case 8:
            Write(head);
            break;
        case 0:
            return;
        default:
            break;
    }
    goto add;
}
