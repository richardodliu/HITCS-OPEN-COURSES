#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NumVertices 20
#define MAX_VERTEX_NUM 100
typedef char VertexData;

typedef struct MTGraph {
	VertexData vertex[NumVertices]; //顶点表
	int edge[NumVertices][NumVertices];
	//邻接矩阵—边表, 可视为顶点之间的关系
	int n, e; //图的顶点数与边数
}MTGraph;

typedef struct node {//边表结点
	int adjvex; //邻接点域（下标）
	int cost; //边上的权值
	struct node *next; //下一边链接指针
} EdgeNode;
typedef struct { //顶点表结点
	VertexData vertex; //顶点数据域
	EdgeNode *firstedge;//边链表头指针
} VertexNode;
typedef struct { //图的邻接表
	VertexNode vexlist[NumVertices];
	int n, e; //顶点个数与边数
} AdjGraph;

typedef enum{unvisited,visited} VisitIf;
typedef struct EBox {
	VisitIf mark; //边访问标记
	int ivex, jvex; //该边依附的两个顶点的位置
	struct EBox *ilink, *jlink; //分别指向依附这两个顶点的下一条边
	int *info; //该边信息指针
}EBox;
typedef struct VexBox {
	VertexData data;
	EBox *firstedge; //指向第一条依附于该顶点的边
} VexBox;
typedef struct AMLGraph {
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum, edgenum; //无向图的当前顶点数和边数
} AMLGraph;

typedef struct QueueNode//队列节点
{
	int  adjvex;
	struct QueueNode* next;
} QueueNode;
typedef struct Queue//队列
{
	QueueNode *Front;
	QueueNode *Rear;
}Queue;

typedef struct queue {
	int    data[NumVertices];
	int    front, rear;
}queue;

typedef struct StackNode//栈节点
{
	int adjvex;
	struct StackNode *next;
}StackNode;
typedef StackNode *Stack;

//函数功能：建立邻接矩阵
MTGraph *CreateMGragh();
//函数功能：建立邻接表
AdjGraph *CreateGraph();
//函数功能：将邻接矩阵g转换成邻接表G
AdjGraph *MatToList(MTGraph *g);
//函数功能：将邻接表G转换成邻接矩阵g
MTGraph *ListToMat(AdjGraph *G);
//函数功能：以vi为出发点时对邻接表表示的图G进行先深搜索
void DFS1(AdjGraph *G, int i);
//函数功能：先深搜索一邻接表表示的图G
void DFSTraverse1(AdjGraph *G);
//函数功能：以vi为出发点时对邻接矩阵表示的图G进行先深搜索
void DFS3(MTGraph *G, int i);
//函数功能：先深搜索一邻接矩阵表示的图G
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
	printf("欢迎进入图系统\n");
	View();
	scanf("%d", &choice);
	getchar();
	switch (choice)
	{
	case 1:
		G = CreateGraph();
		M = ListToMat(G);
		printf("邻接表递归深度优先搜索遍历为：      ");
		DFSTraverse1(G);
		printf("\n邻接矩阵递归深度优先搜索遍历为：    ");
		DFSTraverse3(M);
		printf("\n邻接表非递归深度优先搜索遍历为：    ");
		DFSTraverse_STACK(G, S);
		printf("\n邻接矩阵非递归深度优先搜索遍历为：  ");
		DFSTraverse_STACK1(M, S);
		printf("\n邻接表广度优先搜索遍历为：          ");
		BFSTraverse1(G);
		printf("\n邻接矩阵广度优先搜索遍历为：        ");
		BFSTraverse(M);
		break;
	case 2:
		M = CreateMGragh();
		G = MatToList(M);
		printf("邻接表递归深度优先搜索遍历为：      ");
		DFSTraverse1(G);
		printf("\n邻接矩阵递归深度优先搜索遍历为：    ");
		DFSTraverse3(M);
		printf("\n邻接表非递归深度优先搜索遍历为：    ");
		DFSTraverse_STACK(G, S);
		printf("\n邻接矩阵非递归深度优先搜索遍历为：  ");
		DFSTraverse_STACK1(M, S);
		printf("\n邻接表广度优先搜索遍历为：          ");
		BFSTraverse1(G);
		printf("\n邻接矩阵广度优先搜索遍历为：        ");
		BFSTraverse(M);
		break;
	default:
		printf("\n输入有误，请重新输入\n");
		break;
	}
	return 0;
}
void View()
{
	printf("---------------------------------- |\n");
	printf("|   ----------------------------   |\n");
	printf("|  |1 读取邻接表并转换和遍历    |  |\n");
	printf("|  |2 读取邻接矩阵并转换和遍历  |  |\n");
	printf("|   -----------------------------  |\n");
	printf("|--------------------------------- |\n");
	printf("请选择:");

}
//建立邻接矩阵
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
		printf("a.txt文件打开失败，程序退出！\n");
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
//建立邻接表
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
		printf("b.txt文件打开失败，程序退出！\n");
		exit(0);
	}
	fscanf(file, "%d %d\n", &G->n, &G->e);
	for (i = 0; i < G->n; i++)
	{ //2.建立顶点表
		fscanf(file, "%c\n", &point);
		G->vexlist[i].vertex = point;
		G->vexlist[i].firstedge = NULL;
	} //2.2边表置为空表
	for (i = 0; i < G->e; i++)
	{ //3.逐条边输入,建立边表
		fscanf(file, "%d %d %d\n", &head, &tail, &weight);
		p = malloc(sizeof(EdgeNode)); //3.2建立边结点
		p->adjvex = head;
		p->cost = weight; //3.3设置边结点
		p->next = G->vexlist[tail].firstedge; //3.4链入第 tail 号链表的前端
		G->vexlist[tail].firstedge = p;
		p = malloc(sizeof(EdgeNode));
		p->adjvex = tail;
		p->cost = weight;
		p->next = G->vexlist[head].firstedge; //链入第 head 号链表的前端
		G->vexlist[head].firstedge = p;
	}
	fclose(file);
	return G;
}
//邻接矩阵转换为邻接表
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
	for (i = 0; i<g->n; i++)                   //检查邻接矩阵中每个元素
		for (j = g->n - 1; j >= 0; j--)
			if (g->edge[i][j] != 0)       //存在一条边
			{
				p = malloc(sizeof(EdgeNode));   //创建一个节点*p
				p->adjvex = j;
				p->cost = g->edge[i][j];
				p->next = G->vexlist[i].firstedge;      //采用头插法插入*p
				G->vexlist[i].firstedge = p;
			}
	G->n = g->n;
	G->e = g->e;
	return G;
}
//邻接表转换为邻接矩阵
MTGraph *ListToMat(AdjGraph *G)
{
	int i, j;
	EdgeNode *p;
	MTGraph *g = malloc(sizeof(MTGraph));
	g->n = G->n;
	g->e = G->e;
	for (i = 0; i<g->n; i++)
		g->vertex[i] = G->vexlist[i].vertex;
	for (i = 0; i<g->n; i++)   //先初始化邻接矩阵
		for (j = 0; j<g->n; j++)
			g->edge[i][j] = 0;
	for (i = 0; i<G->n; i++)  //根据邻接表，为邻接矩阵赋值
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
//递归深度优先搜索邻接表
int visit1[NumVertices]; //访问标记数组是全局变量
int dfn[NumVertices]; //顶点的先深编号
int count = 1;
void DFSTraverse1(AdjGraph *G) //主算法
/* 先深搜索一邻接表表示的图G；而以邻接矩阵表示G时，算法完全相同 */
{
	int i;
	for (i = 0; i < G->n; i++)
		visit1[i] = 0; //标志数组初始化
	for (i = 0; i < G->n; i++)
		if (!visit1[i])
			DFS1(G, i); //从顶点 i 出发的一次搜索，BFSX(G, i )
}
void DFS1(AdjGraph *G, int i)
{
	EdgeNode *p;
	printf("%c ", G->vexlist[i].vertex);
	visit1[i] = 1; //标记vi已访问
	dfn[i] = count++; //对vi进行编号
	p = G->vexlist[i].firstedge; //取vi边表的头指针
	while (p)
	{ //依次搜索vi的邻接点vj, 这里j=p->adjvex
		if (!visit1[p->adjvex]) //若vj尚未访问
			DFS1(G, p->adjvex); //则以vj为出发点先深搜索
		p = p->next;
	}
}
//递归深度优先搜索邻接矩阵
int visit3[NumVertices];
int dfn1[NumVertices]; //顶点的先深编号
int count1 = 1;
void DFSTraverse3(MTGraph *G) {
	int i;
	for (i = 0; i < G->n; i++)
		visit3[i] = 0;
	//循环是为保证每个顶点都能被访问到
	for (i = 0; i < G->n; i++)
		if (!visit3[i])
			DFS3(G, i);
}
void DFS3(MTGraph *G, int i)
{
	int j;
	printf("%c ", G->vertex[i]);
	visit3[i] = 1; //标记vi已访问
	dfn1[i] = count1; //对vi进行编号
	count1++; //下一个顶点的编号
	for (j = 0; j<G->n; j++) //依次搜索vi的邻接点
		if ((G->edge[i][j] == 1) && !visit3[i]) //若vj尚未访问
			DFS3(G, j);
}
//非递归广度优先搜索邻接表
int visited1[NumVertices]; //访问标记数组是全局变量
int dfn1[NumVertices]; //顶点的先深编号
void BFSTraverse1(AdjGraph *G) //主算法
							   /* 先广搜索一邻接表表示的图G；而以邻接矩阵表示G时，算法完全相同 */
{
	for (int i = 0; i < G->n; i++)
		visited1[i] = 0; //标志数组初始化
	for (int i = 0; i < G->n; i++)
		if (!visited1[i])
			BFS1(G, i); //从顶点 i 出发的一次搜索，DFSX (G, i )
}
void BFS1(AdjGraph *G, int k)//这里没有进行先广编号
{
	int i;
	EdgeNode *p;
	Queue *Q = malloc(sizeof(Queue));
	MakeNullQ(Q);
	printf("%c ", G->vexlist[k].vertex);
	visited1[k] = 1;
	Enqueue(Q, k); //进队列
	while (Q->Front != Q->Rear)
	{ //队空搜索结束
		i = Front(Q);
		Dequeue(Q); //vi出队
		p = G->vexlist[i].firstedge; //取vi的边表头指针
		while (p)
		{ //若vi的邻接点 vj (j= p→adjvex)存在,依次搜索
			if (!visited1[p->adjvex])
			{ //若vj未访问过
				printf("%c ", G->vexlist[p->adjvex].vertex);
				visited1[p->adjvex] = 1; //给vj作访问过标记
				Enqueue(Q, p->adjvex); //访问过的vj入队
			}
			p = p->next; //找vi的下一个邻接点
		} // 重复检测 vi的所有邻接顶点
	} //外层循环，判队列空否
}//以vk为出发点时对用邻接表表示的图G进行先广搜索
void MakeNullQ(Queue *Q)
{
	Q->Front = malloc(sizeof(QueueNode));
	Q->Front->next = NULL;
	Q->Rear = Q->Front;//头尾指针相同表示空
}
void Enqueue(Queue *Q, int adjvex)
{
	Q->Rear->next = malloc(sizeof(QueueNode));//队尾指针后接一个新的节点
	Q->Rear = Q->Rear->next;//队尾指针后移
	Q->Rear->adjvex = adjvex;
	Q->Rear->next = NULL;
}
void Dequeue(Queue *Q)
{
	if (Q->Front == Q->Rear)
		printf("队列已空，无法出队");
	else
	{
		QueueNode *temp = malloc(sizeof(QueueNode));
		temp = Q->Front->next;
		Q->Front->next = temp->next;//移动队列队首指针，队首元素出栈
		free(temp);//清存
		if (Q->Front->next == NULL)//判断为空则置空
			Q->Rear = Q->Front;
	}
}
int Front(Queue *Q)
{
	return Q->Front->next->adjvex;//返回头队列元素
}
//非递归广度优先搜索邻接矩阵
int visited2[NumVertices]; //访问标记数组是全局变量
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
//非递归深度优先搜索邻接表
int visite2[NumVertices];
void DFSTraverse_STACK(AdjGraph *G, Stack S)
{
	int i;
	for (i = 0; i < G->n; i++)
		visite2[i] = 0;    //顶点数维度数组初始化
	for (int i = 0; i < G->n; i++)//对每个顶点处理
		if (!visite2[i])//没访问过
			DFSX_STACK(S, G, i);//压栈
}
void DFSX_STACK(Stack S, AdjGraph *G, int i)
{
	int NodeIndex;
	S = Push(S, i);//顶点压栈
	while (S->next != NULL)//栈不为空
	{
		NodeIndex = Top(S);//栈顶元素处理
		if (!visite2[NodeIndex])//若没访问
		{
			printf("%c ", G->vexlist[NodeIndex].vertex);
			visite2[NodeIndex] = 1;//标志访问过
		}
		EdgeNode *newEdgNode;
		newEdgNode = G->vexlist[NodeIndex].firstedge;//连接的点的开始
		while (newEdgNode)//处理与该点相邻接的所有点
		{
			if (!visite2[newEdgNode->adjvex])//没访问就压入栈中
			{
				Push(S, newEdgNode->adjvex);
				break;
			}
			else
				newEdgNode = newEdgNode->next;//否则判断下一个邻接节点
		}
		if (!newEdgNode)//如果与该点相邻的点都访问了
			Pop(S);//弹出该点
	}
}
StackNode *Push(StackNode *S, int adjvex)
{
	StackNode *Snew = malloc(sizeof(StackNode));
	if (S == NULL)//栈为空插入情况
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
		return S->next->adjvex;//返回栈顶元素的标号
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
		printf("栈已空，无法出栈");
	else
	{
		StackNode *Stemp = malloc(sizeof(StackNode));
		Stemp = S->next;
		S->next = Stemp->next;//元素出栈
		free(Stemp);//清存
	}
}
//非递归深度优先搜索邻接矩阵
int visite1[NumVertices];
void DFSTraverse_STACK1(MTGraph *G, Stack S)
{
	int i;
	for (i = 0; i < G->n; i++)
		visite1[i] = 0;    //顶点数维度数组初始化
	for (int i = 0; i < G->n; i++)//对每个顶点处理
		if (!visite1[i])//没访问过
			DFSX_STACK1(S, G, i);//压栈
}
void DFSX_STACK1(Stack S, MTGraph *G, int i)
{
	int NodeIndex;
	S = Push(S, i);//顶点压栈
	int j;
	while (S->next != NULL)//栈不为空
	{
		j = 0;
		NodeIndex = Top(S);//栈顶元素处理
		if (!visite1[NodeIndex])//若没访问
		{
			printf("%c ", G->vertex[NodeIndex]);
			visite1[NodeIndex] = 1;//标志访问过
		}
		j = findNext(G, NodeIndex, j);
		while (j != -1)//处理与该点相邻接的所有点
		{
			if (!visite1[j])//没访问就压入栈中
			{
				S = Push(S, j);
				break;
			}
			else
				j = findNext(G, NodeIndex, j);//否则判断下一个邻接节点
		}
		if (j == -1)//如果与该点相邻的点都访问了
			Pop(S);//弹出该点
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
