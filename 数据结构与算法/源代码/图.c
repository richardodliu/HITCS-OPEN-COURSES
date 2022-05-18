#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NumVertices 20
#define MAX_VERTEX_NUM 100
typedef char VertexData;

typedef struct MTGraph {
	VertexData vertex[NumVertices]; //�����
	int edge[NumVertices][NumVertices];
	//�ڽӾ��󡪱߱�, ����Ϊ����֮��Ĺ�ϵ
	int n, e; //ͼ�Ķ����������
}MTGraph;

typedef struct node {//�߱���
	int adjvex; //�ڽӵ����±꣩
	int cost; //���ϵ�Ȩֵ
	struct node *next; //��һ������ָ��
} EdgeNode;
typedef struct { //�������
	VertexData vertex; //����������
	EdgeNode *firstedge;//������ͷָ��
} VertexNode;
typedef struct { //ͼ���ڽӱ�
	VertexNode vexlist[NumVertices];
	int n, e; //������������
} AdjGraph;

typedef enum{unvisited,visited} VisitIf;
typedef struct EBox {
	VisitIf mark; //�߷��ʱ��
	int ivex, jvex; //�ñ����������������λ��
	struct EBox *ilink, *jlink; //�ֱ�ָ�������������������һ����
	int *info; //�ñ���Ϣָ��
}EBox;
typedef struct VexBox {
	VertexData data;
	EBox *firstedge; //ָ���һ�������ڸö���ı�
} VexBox;
typedef struct AMLGraph {
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum, edgenum; //����ͼ�ĵ�ǰ�������ͱ���
} AMLGraph;

typedef struct QueueNode//���нڵ�
{
	int  adjvex;
	struct QueueNode* next;
} QueueNode;
typedef struct Queue//����
{
	QueueNode *Front;
	QueueNode *Rear;
}Queue;

typedef struct queue {
	int    data[NumVertices];
	int    front, rear;
}queue;

typedef struct StackNode//ջ�ڵ�
{
	int adjvex;
	struct StackNode *next;
}StackNode;
typedef StackNode *Stack;

//�������ܣ������ڽӾ���
MTGraph *CreateMGragh();
//�������ܣ������ڽӱ�
AdjGraph *CreateGraph();
//�������ܣ����ڽӾ���gת�����ڽӱ�G
AdjGraph *MatToList(MTGraph *g);
//�������ܣ����ڽӱ�Gת�����ڽӾ���g
MTGraph *ListToMat(AdjGraph *G);
//�������ܣ���viΪ������ʱ���ڽӱ��ʾ��ͼG������������
void DFS1(AdjGraph *G, int i);
//�������ܣ���������һ�ڽӱ��ʾ��ͼG
void DFSTraverse1(AdjGraph *G);
//�������ܣ���viΪ������ʱ���ڽӾ����ʾ��ͼG������������
void DFS3(MTGraph *G, int i);
//�������ܣ���������һ�ڽӾ����ʾ��ͼG
void DFSTraverse3(MTGraph *G);
void BFSTraverse1(AdjGraph *G);
void BFS1(AdjGraph *G, int k);
void MakeNullQ(Queue *Q);
void Enqueue(Queue *Q, int adjvex);
void Dequeue(Queue *Q);
int Front(Queue *Q);
void BFSTraverse(MTGraph *G);
void InitQueue(queue *Q);
void EnQueue(queue *Q, int e);
int QueueEmpty(queue *Q);
void DeQueue(queue *Q, int *e);
void DFSTraverse_STACK(AdjGraph *G, Stack S);
void DFSX_STACK(Stack S, AdjGraph *G, int i);
StackNode *Push(StackNode *S, int adjvex);
int Top(Stack S);
void Pop(Stack S);
void DFSTraverse_STACK1(MTGraph *G, Stack S);
void DFSX_STACK1(Stack S, MTGraph *G, int i);
int findNext(MTGraph *G, int vex, int j);
void MakeNullS(Stack S);
void View();
int Judge = 0;
int main()
{
	int choice;
	Stack S = NULL;
	Queue *Q = malloc(sizeof(QueueNode));
	queue *q = malloc(sizeof(queue));
	MakeNullQ(Q);
	MakeNullS(S);
	InitQueue(q);
	AdjGraph *G = NULL;
	MTGraph *M = NULL;
	printf("��ӭ����ͼϵͳ\n");
	View();
	scanf("%d", &choice);
	getchar();
	switch (choice)
	{
	case 1:
		G = CreateGraph();
		M = ListToMat(G);
		printf("�ڽӱ�ݹ����������������Ϊ��      ");
		DFSTraverse1(G);
		printf("\n�ڽӾ���ݹ����������������Ϊ��    ");
		DFSTraverse3(M);
		printf("\n�ڽӱ�ǵݹ����������������Ϊ��    ");
		DFSTraverse_STACK(G, S);
		printf("\n�ڽӾ���ǵݹ����������������Ϊ��  ");
		DFSTraverse_STACK1(M, S);
		printf("\n�ڽӱ���������������Ϊ��          ");
		BFSTraverse1(G);
		printf("\n�ڽӾ�����������������Ϊ��        ");
		BFSTraverse(M);
		break;
	case 2:
		M = CreateMGragh();
		G = MatToList(M);
		printf("�ڽӱ�ݹ����������������Ϊ��      ");
		DFSTraverse1(G);
		printf("\n�ڽӾ���ݹ����������������Ϊ��    ");
		DFSTraverse3(M);
		printf("\n�ڽӱ�ǵݹ����������������Ϊ��    ");
		DFSTraverse_STACK(G, S);
		printf("\n�ڽӾ���ǵݹ����������������Ϊ��  ");
		DFSTraverse_STACK1(M, S);
		printf("\n�ڽӱ���������������Ϊ��          ");
		BFSTraverse1(G);
		printf("\n�ڽӾ�����������������Ϊ��        ");
		BFSTraverse(M);
		break;
	default:
		printf("\n������������������\n");
		break;
	}
	return 0;
}
void View()
{
	printf("---------------------------------- |\n");
	printf("|   ----------------------------   |\n");
	printf("|  |1 ��ȡ�ڽӱ�ת���ͱ���    |  |\n");
	printf("|  |2 ��ȡ�ڽӾ���ת���ͱ���  |  |\n");
	printf("|   -----------------------------  |\n");
	printf("|--------------------------------- |\n");
	printf("��ѡ��:");

}
//�����ڽӾ���
MTGraph *CreateMGragh()
{
	FILE *file = NULL;
	int numa = 0, numb = 0, i, j;
	char point;
	MTGraph *G = malloc(sizeof(MTGraph));
	for (i = 0; i<G->n; i++)
		for (j = 0; j<G->n; j++)
			G->edge[i][j] = 0;
	if ((file = fopen("C:\\Users\\61472\\Desktop\\work\\lab3.1\\a.txt", "r+")) == NULL)
	{
		printf("a.txt�ļ���ʧ�ܣ������˳���\n");
		exit(0);
	}
	fscanf(file, "%d %d\n", &G->n, &G->e);
	for (i = 0; i<G->n; i++)
	{
		fscanf(file, "%c\n", &point);
		G->vertex[i] = point;
	}
	for (i = 0; i<G->e; i++)
	{
		fscanf(file, "%d %d\n", &numa, &numb);
		G->edge[numa][numb] = 1;
		G->edge[numb][numa] = 1;
	}
	fclose(file);
	return G;
}
//�����ڽӱ�
AdjGraph *CreateGraph()
{
	int i;
	int head = 0, tail = 0, weight = 0;
	AdjGraph *G = malloc(sizeof(AdjGraph));
	FILE *file = NULL;
	char point;
	EdgeNode *p = NULL;
	if ((file = fopen("C:\\Users\\61472\\Desktop\\work\\lab3.1\\b.txt", "r+")) == NULL)
	{
		printf("b.txt�ļ���ʧ�ܣ������˳���\n");
		exit(0);
	}
	fscanf(file, "%d %d\n", &G->n, &G->e);
	for (i = 0; i < G->n; i++)
	{ //2.���������
		fscanf(file, "%c\n", &point);
		G->vexlist[i].vertex = point;
		G->vexlist[i].firstedge = NULL;
	} //2.2�߱���Ϊ�ձ�
	for (i = 0; i < G->e; i++)
	{ //3.����������,�����߱�
		fscanf(file, "%d %d %d\n", &head, &tail, &weight);
		p = malloc(sizeof(EdgeNode)); //3.2�����߽��
		p->adjvex = head;
		p->cost = weight; //3.3���ñ߽��
		p->next = G->vexlist[tail].firstedge; //3.4����� tail �������ǰ��
		G->vexlist[tail].firstedge = p;
		p = malloc(sizeof(EdgeNode));
		p->adjvex = tail;
		p->cost = weight;
		p->next = G->vexlist[head].firstedge; //����� head �������ǰ��
		G->vexlist[head].firstedge = p;
	}
	fclose(file);
	return G;
}
//�ڽӾ���ת��Ϊ�ڽӱ�
AdjGraph *MatToList(MTGraph *g)
{
	int i, j;
	EdgeNode *p;
	AdjGraph *G = malloc(sizeof(AdjGraph));
	for (i = 0; i<g->n; i++)
	{
		G->vexlist[i].vertex = g->vertex[i];
		G->vexlist[i].firstedge = NULL;
	}
	for (i = 0; i<g->n; i++)                   //����ڽӾ�����ÿ��Ԫ��
		for (j = g->n - 1; j >= 0; j--)
			if (g->edge[i][j] != 0)       //����һ����
			{
				p = malloc(sizeof(EdgeNode));   //����һ���ڵ�*p
				p->adjvex = j;
				p->cost = g->edge[i][j];
				p->next = G->vexlist[i].firstedge;      //����ͷ�巨����*p
				G->vexlist[i].firstedge = p;
			}
	G->n = g->n;
	G->e = g->e;
	return G;
}
//�ڽӱ�ת��Ϊ�ڽӾ���
MTGraph *ListToMat(AdjGraph *G)
{
	int i, j;
	EdgeNode *p;
	MTGraph *g = malloc(sizeof(MTGraph));
	g->n = G->n;
	g->e = G->e;
	for (i = 0; i<g->n; i++)
		g->vertex[i] = G->vexlist[i].vertex;
	for (i = 0; i<g->n; i++)   //�ȳ�ʼ���ڽӾ���
		for (j = 0; j<g->n; j++)
			g->edge[i][j] = 0;
	for (i = 0; i<G->n; i++)  //�����ڽӱ�Ϊ�ڽӾ���ֵ
	{
		p = G->vexlist[i].firstedge;
		while (p != NULL)
		{
			g->edge[i][p->adjvex] = p->cost;
			g->edge[p->adjvex][i] = p->cost;
			p = p->next;
		}
	}
	return g;
}
//�ݹ�������������ڽӱ�
int visit1[NumVertices]; //���ʱ��������ȫ�ֱ���
int dfn[NumVertices]; //�����������
int count = 1;
void DFSTraverse1(AdjGraph *G) //���㷨
/* ��������һ�ڽӱ��ʾ��ͼG�������ڽӾ����ʾGʱ���㷨��ȫ��ͬ */
{
	int i;
	for (i = 0; i < G->n; i++)
		visit1[i] = 0; //��־�����ʼ��
	for (i = 0; i < G->n; i++)
		if (!visit1[i])
			DFS1(G, i); //�Ӷ��� i ������һ��������BFSX(G, i )
}
void DFS1(AdjGraph *G, int i)
{
	EdgeNode *p;
	printf("%c ", G->vexlist[i].vertex);
	visit1[i] = 1; //���vi�ѷ���
	dfn[i] = count++; //��vi���б��
	p = G->vexlist[i].firstedge; //ȡvi�߱��ͷָ��
	while (p)
	{ //��������vi���ڽӵ�vj, ����j=p->adjvex
		if (!visit1[p->adjvex]) //��vj��δ����
			DFS1(G, p->adjvex); //����vjΪ��������������
		p = p->next;
	}
}
//�ݹ�������������ڽӾ���
int visit3[NumVertices];
int dfn1[NumVertices]; //�����������
int count1 = 1;
void DFSTraverse3(MTGraph *G) {
	int i;
	for (i = 0; i < G->n; i++)
		visit3[i] = 0;
	//ѭ����Ϊ��֤ÿ�����㶼�ܱ����ʵ�
	for (i = 0; i < G->n; i++)
		if (!visit3[i])
			DFS3(G, i);
}
void DFS3(MTGraph *G, int i)
{
	int j;
	printf("%c ", G->vertex[i]);
	visit3[i] = 1; //���vi�ѷ���
	dfn1[i] = count1; //��vi���б��
	count1++; //��һ������ı��
	for (j = 0; j<G->n; j++) //��������vi���ڽӵ�
		if ((G->edge[i][j] == 1) && !visit3[i]) //��vj��δ����
			DFS3(G, j);
}
//�ǵݹ������������ڽӱ�
int visited1[NumVertices]; //���ʱ��������ȫ�ֱ���
int dfn1[NumVertices]; //�����������
void BFSTraverse1(AdjGraph *G) //���㷨
							   /* �ȹ�����һ�ڽӱ��ʾ��ͼG�������ڽӾ����ʾGʱ���㷨��ȫ��ͬ */
{
	for (int i = 0; i < G->n; i++)
		visited1[i] = 0; //��־�����ʼ��
	for (int i = 0; i < G->n; i++)
		if (!visited1[i])
			BFS1(G, i); //�Ӷ��� i ������һ��������DFSX (G, i )
}
void BFS1(AdjGraph *G, int k)//����û�н����ȹ���
{
	int i;
	EdgeNode *p;
	Queue *Q = malloc(sizeof(Queue));
	MakeNullQ(Q);
	printf("%c ", G->vexlist[k].vertex);
	visited1[k] = 1;
	Enqueue(Q, k); //������
	while (Q->Front != Q->Rear)
	{ //�ӿ���������
		i = Front(Q);
		Dequeue(Q); //vi����
		p = G->vexlist[i].firstedge; //ȡvi�ı߱�ͷָ��
		while (p)
		{ //��vi���ڽӵ� vj (j= p��adjvex)����,��������
			if (!visited1[p->adjvex])
			{ //��vjδ���ʹ�
				printf("%c ", G->vexlist[p->adjvex].vertex);
				visited1[p->adjvex] = 1; //��vj�����ʹ����
				Enqueue(Q, p->adjvex); //���ʹ���vj���
			}
			p = p->next; //��vi����һ���ڽӵ�
		} // �ظ���� vi�������ڽӶ���
	} //���ѭ�����ж��пշ�
}//��vkΪ������ʱ�����ڽӱ��ʾ��ͼG�����ȹ�����
void MakeNullQ(Queue *Q)
{
	Q->Front = malloc(sizeof(QueueNode));
	Q->Front->next = NULL;
	Q->Rear = Q->Front;//ͷβָ����ͬ��ʾ��
}
void Enqueue(Queue *Q, int adjvex)
{
	Q->Rear->next = malloc(sizeof(QueueNode));//��βָ����һ���µĽڵ�
	Q->Rear = Q->Rear->next;//��βָ�����
	Q->Rear->adjvex = adjvex;
	Q->Rear->next = NULL;
}
void Dequeue(Queue *Q)
{
	if (Q->Front == Q->Rear)
		printf("�����ѿգ��޷�����");
	else
	{
		QueueNode *temp = malloc(sizeof(QueueNode));
		temp = Q->Front->next;
		Q->Front->next = temp->next;//�ƶ����ж���ָ�룬����Ԫ�س�ջ
		free(temp);//���
		if (Q->Front->next == NULL)//�ж�Ϊ�����ÿ�
			Q->Rear = Q->Front;
	}
}
int Front(Queue *Q)
{
	return Q->Front->next->adjvex;//����ͷ����Ԫ��
}
//�ǵݹ������������ڽӾ���
int visited2[NumVertices]; //���ʱ��������ȫ�ֱ���
void BFSTraverse(MTGraph *G)
{
	int i, j;
	queue Q;

	for (i = 0; i<G->n; i++)
		visited2[i] = 0;

	InitQueue(&Q);

	for (i = 0; i<G->n; ++i)
	{
		if (!visited2[i])
		{
			visited2[i] = 1;
			printf("%c ", G->vertex[i]);
			EnQueue(&Q, i);

			while (!QueueEmpty(&Q))
			{
				DeQueue(&Q, &i);
				for (j = 0; j<G->n; j++)
				{
					if (!visited2[j] && G->edge[i][j] != 0)
					{
						visited2[j] = 1;
						printf("%c ", G->vertex[j]);
						EnQueue(&Q, j);
					}
				}
			}
		}
	}
}
void InitQueue(queue *Q)
{
	Q->front = Q->rear = 0;
}
void EnQueue(queue *Q, int e)
{
	if ((Q->rear + 1) % NumVertices == Q->front)
		return;

	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % NumVertices;
}
int QueueEmpty(queue *Q)
{
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}
void DeQueue(queue *Q, int *e)
{
	if (Q->front == Q->rear)
		return;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % NumVertices;
}
//�ǵݹ�������������ڽӱ�
int visite2[NumVertices];
void DFSTraverse_STACK(AdjGraph *G, Stack S)
{
	int i;
	for (i = 0; i < G->n; i++)
		visite2[i] = 0;    //������ά�������ʼ��
	for (int i = 0; i < G->n; i++)//��ÿ�����㴦��
		if (!visite2[i])//û���ʹ�
			DFSX_STACK(S, G, i);//ѹջ
}
void DFSX_STACK(Stack S, AdjGraph *G, int i)
{
	int NodeIndex;
	S = Push(S, i);//����ѹջ
	while (S->next != NULL)//ջ��Ϊ��
	{
		NodeIndex = Top(S);//ջ��Ԫ�ش���
		if (!visite2[NodeIndex])//��û����
		{
			printf("%c ", G->vexlist[NodeIndex].vertex);
			visite2[NodeIndex] = 1;//��־���ʹ�
		}
		EdgeNode *newEdgNode;
		newEdgNode = G->vexlist[NodeIndex].firstedge;//���ӵĵ�Ŀ�ʼ
		while (newEdgNode)//������õ����ڽӵ����е�
		{
			if (!visite2[newEdgNode->adjvex])//û���ʾ�ѹ��ջ��
			{
				Push(S, newEdgNode->adjvex);
				break;
			}
			else
				newEdgNode = newEdgNode->next;//�����ж���һ���ڽӽڵ�
		}
		if (!newEdgNode)//�����õ����ڵĵ㶼������
			Pop(S);//�����õ�
	}
}
StackNode *Push(StackNode *S, int adjvex)
{
	StackNode *Snew = malloc(sizeof(StackNode));
	if (S == NULL)//ջΪ�ղ������
	{
		S = malloc(sizeof(StackNode));
		S->next = Snew;
		Snew->adjvex = adjvex;
		Snew->next = NULL;
		return S;
	}
	Snew->adjvex = adjvex;
	Snew->next = S->next;
	S->next = Snew;
	return S;
}
int Top(Stack S)
{
	if (S->next != NULL)
		return S->next->adjvex;//����ջ��Ԫ�صı��
	return -1;
}
void MakeNullS(Stack S)
{
	S = malloc(sizeof(StackNode));
	S->next = NULL;
}
void Pop(Stack S)
{
	if (S->next == NULL)
		printf("ջ�ѿգ��޷���ջ");
	else
	{
		StackNode *Stemp = malloc(sizeof(StackNode));
		Stemp = S->next;
		S->next = Stemp->next;//Ԫ�س�ջ
		free(Stemp);//���
	}
}
//�ǵݹ�������������ڽӾ���
int visite1[NumVertices];
void DFSTraverse_STACK1(MTGraph *G, Stack S)
{
	int i;
	for (i = 0; i < G->n; i++)
		visite1[i] = 0;    //������ά�������ʼ��
	for (int i = 0; i < G->n; i++)//��ÿ�����㴦��
		if (!visite1[i])//û���ʹ�
			DFSX_STACK1(S, G, i);//ѹջ
}
void DFSX_STACK1(Stack S, MTGraph *G, int i)
{
	int NodeIndex;
	S = Push(S, i);//����ѹջ
	int j;
	while (S->next != NULL)//ջ��Ϊ��
	{
		j = 0;
		NodeIndex = Top(S);//ջ��Ԫ�ش���
		if (!visite1[NodeIndex])//��û����
		{
			printf("%c ", G->vertex[NodeIndex]);
			visite1[NodeIndex] = 1;//��־���ʹ�
		}
		j = findNext(G, NodeIndex, j);
		while (j != -1)//������õ����ڽӵ����е�
		{
			if (!visite1[j])//û���ʾ�ѹ��ջ��
			{
				S = Push(S, j);
				break;
			}
			else
				j = findNext(G, NodeIndex, j);//�����ж���һ���ڽӽڵ�
		}
		if (j == -1)//�����õ����ڵĵ㶼������
			Pop(S);//�����õ�
	}
}
int findNext(MTGraph *G, int vex, int j)
{
	int i;
	for (i = j + 1; i<vex; i++)
	{
		if (G->edge[vex][i] == 1)
			return i;
	}
	return -1;
}
