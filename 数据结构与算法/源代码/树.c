#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct node {
	struct node *lchild;
	struct node *rchild;
	int data;
};
typedef struct node *btree;

struct stack{
    int top;
    btree p[100];
};
struct stack q;

btree creat();
void preorder(btree t);
void inorder(btree t);
void postorder(btree t);
void Preorder(btree root);
void Inorder(btree root);
void Postorder(btree root);
void level_order(btree root);
void makenull(struct stack q);
int isempty(struct stack q);
btree top(struct stack q);
void pop(struct stack q);
void push(struct stack q,btree x);
int fun(btree t);
int check(btree root);

int main()
{
	btree t = NULL;
	t = creat(t);/*创建*/
	preorder(t);
	printf("\n");
	inorder(t);
	printf("\n");
	postorder(t);
	printf("\n");
	Preorder(t);
	printf("\n");
	Inorder(t);
	printf("\n");
	Postorder(t);
	printf("\n");
	level_order(t);
	printf("\n");
	if(fun(t)==-1)
    {
        printf("no");
    }
    else printf("yes");
    printf("\n");
    if(check(t))
    {
        printf("yes");
    }
    else printf("no");
	return 0;

}

btree creat(btree t)
{
	btree s[100]={NULL};
	char str[10];
	int i = 1;
	int x;
	while (1)/*定义二叉树*/
	{
		scanf("%s", str);
		if (strcmp(str, "$") == 0)
		{
			break;
		}
		else if (strcmp(str, "#") == 0)
		{
			s[i] = NULL;
			i++;
		}
		else
		{
			s[i]= (btree)malloc(sizeof(struct node));
			if (s[i]== NULL)
			{
				puts("error.\n");
				exit(0);
			}
			x = atoi(str);
			s[i]->data = x;
			s[i]->lchild = NULL;
			s[i]->rchild = NULL;
			if (i==1)
			{
				t=s[i];
			}
			else
            {
                if (i % 2 == 0)
				{
					s[i/2]->lchild = s[i];
				}
				else
				{
					s[i/2]->rchild = s[i];
				}
            }
			i++;
		}
	}
	return t;
}

void preorder(btree t)
{
	if (t != NULL)
	{
		printf("%d ",t->data);
		preorder(t->lchild);
		preorder(t->rchild);
	}
}

void inorder(btree t)
{
	if (t != NULL)
	{

		inorder(t->lchild);
		printf("%d ",t->data);
		inorder(t->rchild);
	}
}

void postorder(btree t)
{
	if (t != NULL)
	{

		postorder(t->lchild);
		postorder(t->rchild);
		printf("%d ",t->data);
	}
}

void Preorder(btree root)
{
    int top= -1; //采用顺序栈，并假定不会发生上溢
    while (root!=NULL || top!= -1)
    {
        while (root!=NULL)
        {
            printf("%d ",root->data);
            q.p[++top]=root;
            root=root->lchild;
        }
        if (top!= -1)
            {
                root=q.p[top--];
                root=root->rchild;
            }
    }
}

void Inorder(btree root)
{
    int top= -1; //采用顺序栈，并假定不会发生上溢
    while (root!=NULL || top!= -1)
    {
        while (root!=NULL)
        {
            q.p[++top]=root;
            root=root->lchild;
        }
        if (top!= -1)
            {
                root=q.p[top--];
                printf("%d ",root->data);
                root=root->rchild;
            }
    }
}

void Postorder(btree root)
{
    btree pre,p;
    int top = -1;
    btree str[100];
    p = root;
    while (p != NULL || top != -1) {
        while (p != NULL) {
            str[++top] = p;
            pre = p->rchild;
            p = p->lchild;
            if (p == NULL)
                p = pre;
        }
        p = str[top--];
        printf("%d ", p->data);
        if (top != -1 && str[top]->lchild == p)
            p = str[top]->rchild;
        else
            p = NULL;
    }
}

void level_order(btree root)
{
    int top = 0, tail = 0;
    btree Q[100];
    if (root == NULL)
        return;
    Q[++tail] = root;
    btree q;
    q = (btree) malloc(sizeof(struct node));
    while (top != tail) {
        q = Q[++top];
        printf("%d ", q->data);
        if (q->lchild != NULL)
            Q[++tail] = q->lchild;
        if (q->rchild != NULL)
            Q[++tail] = q->rchild;
    }
}

void makenull(struct stack q)
{
    q.top=-1;
}

int isempty(struct stack q)
{
    if(q.top<=-1)
    {
        return 1;
    }
    else return 0;
}

btree top(struct stack q)
{
    if(isempty(q))
    {
        return NULL;
    }
    else return q.p[q.top];
}

void pop(struct stack q)
{
    if(isempty(q))
    {
        printf("stack is empty");
    }
    else q.top--;
}

void push(struct stack q,btree x)
{
    if(q.top==99)
    {
        printf("stack is full");
    }
    else
        q.top++;
        q.p[q.top]=x;
}

int fun(btree t)
{
    if((t->lchild==NULL) && (t->rchild==NULL))
    {
        return 1;
        printf("1");
    }
    else if((t->lchild==NULL && t->rchild!=NULL) || (t->rchild==NULL && t->lchild!=NULL))
    {
        return -1;
        printf("-1");
    }
    else
    {
        if( (fun(t->lchild)==-1) || (fun(t->rchild)==-1))
        {
            return -1;
            printf("-1");
        }
        else
        {
            if(fun(t->lchild)!=fun(t->rchild))
            {
                return -1;
                printf("-1");
            }
            else
            {
                return fun(t->lchild)+fun(t->rchild);;
                printf("%d",fun(t->lchild)+fun(t->rchild));
            }
        }
    }
}

int check(btree root)
{
    int top=0,tail=0,n=0,i=0,sum=0;
    int s[100];
    btree Q[100];
    if (root == NULL)
        return 0;
    Q[++tail] = root;
    btree q;
    q = (btree) malloc(sizeof(struct node));
    while (top != tail)
    {
        q = Q[++top];
        if(q->lchild == NULL)
        {
            s[n]=0;
        }
        else s[n]=1;
        n++;
        if(q->rchild == NULL)
        {
            s[n]=0;
        }
        else s[n]=1;
        n++;
        if (q->lchild != NULL)
            Q[++tail] = q->lchild;
        if (q->rchild != NULL)
            Q[++tail] = q->rchild;
    }
    n--;
    for(i=0;i<n;i++)
    {
        if(s[i]!=s[i+1])
        {
            sum++;
        }
    }
    if(sum>=2) return 0;
    else return 1;
}



