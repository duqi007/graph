

#define MAX_VERTEX_NUM		20
#define OK					1
#define ERROR				0
#define STACK_INIT_SIZE 	20
#define STACKINCREMENT 		10

typedef enum { DG, DN, UDG, UDN }  GraphKind ;
typedef char 				VertexType;
typedef int 				Status;
typedef int 				ElemType;
typedef int 				SElemType;
typedef int 				Status;

//------------链式队列的存储结构------------------------// 
typedef struct QNode{
    ElemType data;
    struct QNode * next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front;         //队头指针
    QueuePtr rear;          //队尾指针
}LinkQueue;


typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}sqStack;

//------------图的邻接表的存储-----------------// 
//弧的结构体 
typedef struct ArcNode{
	int adjvex;							//该弧所指向的顶点信息 
	struct ArcNode * nextarc;			//指向吓一跳弧的指针  
}ArcNode;

//顶点的结构体 
typedef struct VNode{
	VertexType data;					//顶点信息 
	ArcNode * firstarc;					//指向第一条依附于该顶点的弧的指针 
}VNode, AdjList[MAX_VERTEX_NUM]; 

//图的结构体 
typedef struct{
	AdjList vertices;					 
	int vernum, arcnum;					//图中顶点和弧的个数 
	GraphKind kind;						//图的种类 
} ALGraph;



int visited[MAX_VERTEX_NUM];
int count;
int low[MAX_VERTEX_NUM];
int indegree[MAX_VERTEX_NUM];


int QueueLength(LinkQueue Q);						//队列的长度，元素个数 
Status QueueEmpty(LinkQueue *Q);					//判断是否为空 
Status DestoryQueue(LinkQueue *Q);					//销毁队列 
Status DeQueue(LinkQueue *Q, ElemType *e);			//进队
Status EnQueue(LinkQueue *Q, ElemType e);			//出队 
Status InitQueue(LinkQueue *Q);						//初始化队列 

void visit(SElemType e);                            //显示元素的函数
Status InitStack(sqStack *S);                       //初始化栈
Status Push(sqStack *S, SElemType e);               //压栈
Status Pop(sqStack *S, SElemType *e);               //弹栈
Status GetTop(sqStack *S, SElemType *e);            //获取栈顶元素，不删除栈顶元素
Status DestroyStack(sqStack *S);                    //销毁栈
Status ClearStack(sqStack *S);                      //清空栈
int StackLength(sqStack s);                         //获取当前栈的长度
Status StackEmpty(sqStack S);                       //判断栈是否为空
Status StackTraverse(sqStack S);                    //遍历栈元素显示出来

Status CreateGraph(ALGraph *g);
Status CreateUDG(ALGraph *g);											//创建无向图 
Status CreateDG(ALGraph *g);											//创建有向图 
Status LocateVex(ALGraph *g, int i );									//输出某一个特定位置i顶点的值 
Status PutVex(ALGraph *g,VertexType ch, VertexType an );				//对图中某一个顶点进行赋值,将顶点值为ch的顶点变成an 
ArcNode * FirstAdjVex(ALGraph *g, int VerLocation);						//获取顶点的第一个连接的边 
ArcNode * NextAdjVex(ALGraph *g, int VerLocation, ArcNode * adjarc);	//返回给定顶点的下一个连接的边
void DFSTraverse(ALGraph *g);											//深度优先遍历 
void DFS(ALGraph *g, int v); 
void BFSTraverse(ALGraph *g, LinkQueue *Q);								//广度优先遍历 
int GetVex(ALGraph *g, VertexType v);									//输入顶点的值求其向量坐标
void FindArticul(ALGraph *g);											//连通图G以邻接表存储，查找并输出所有关节点，全局count对访问计数
void DFSArticul(ALGraph *g , int v);									//从第0个点出发深度优先遍历图g， 查找并输出关节点。
Status TopologicalSort(ALGraph *g, sqStack *S);							//有向无环图g的拓扑排序 
void FindInDegree(ALGraph *g, int indegree[MAX_VERTEX_NUM]);			//求图g各顶点的入度 
