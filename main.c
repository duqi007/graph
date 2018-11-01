#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM		20
#define OK					1
#define ERROR				0


typedef enum { DG, DN, UDG, UDN }  GraphKind ;
typedef char 				VertexType;
typedef int 				Status;
typedef int 				ElemType;

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

//------------链式队列的存储结构------------------------// 
typedef struct QNode{
    ElemType data;
    struct QNode * next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front;         //队头指针
    QueuePtr rear;          //队尾指针
}LinkQueue;



int visited[MAX_VERTEX_NUM];
int count;
int low[MAX_VERTEX_NUM];


Status CreateUDG(ALGraph *g);
Status LocateVex(ALGraph *g, int i );
Status PutVex(ALGraph *g,VertexType ch, VertexType an );
ArcNode * FirstAdjVex(ALGraph *g, int VerLocation);
ArcNode * NextAdjVex(ALGraph *g, int VerLocation, ArcNode * adjarc);
void DFSTraverse(ALGraph *g);
void DFS(ALGraph *g, int v); 
void BFSTraverse(ALGraph *g, LinkQueue *Q);
int GetVex(ALGraph *g, VertexType v);
void FindArticul(ALGraph *g);
void DFSArticul(ALGraph *g , int v);


int QueueLength(LinkQueue Q);
Status QueueEmpty(LinkQueue *Q);
Status DestoryQueue(LinkQueue *Q);
Status DeQueue(LinkQueue *Q, ElemType *e);
Status EnQueue(LinkQueue *Q, ElemType e);
Status InitQueue(LinkQueue *Q);


Status CreateGraph(ALGraph *g){
	int kind;
	printf("请输入需要建立的图的类型（输入下方对应的数字）\n");
	printf("0: 有向图DG\n");
	printf("1: 有向网DN\n");
	printf("2: 无向图UDG\n");
	printf("3: 无向网UDN\n");
	scanf("%d", &kind);
	switch(kind){
		case 0:
			printf("DG");
			break;
		case 1:
			printf("DN");
			break;
		case 2:
			CreateUDG(g);
			break;
		case 3:
			printf("UDN");
			break;
		default:
			return ERROR;
	}
	return OK;
}


Status CreateUDG(ALGraph *g){
	int i;
	int start , end ;
	g->kind = UDG;
	printf("请输入顶点数和边数！\n");
	scanf("%d%d", &g->vernum, &g->arcnum );
	printf("%d  %d\n", g->vernum, g->arcnum);
	printf("请输入顶点的信息！\n");
	for( i = 0; i < g->vernum ; i++){
		VNode *ver = (VNode *)malloc(sizeof(VNode));
		getchar(); 
		scanf("%c", &ver->data); 
		
		printf("第%d个顶点为：%c\n", i, ver->data);
		ver->firstarc = NULL;
		g->vertices[i] = (*ver);
		
	}
	printf("请输入弧的信息！（弧头和弧尾在图中的坐标，并用空格隔开！一次输入一个弧）\n");
	for(i =0 ; i < g->arcnum ; i++){
		ArcNode * arcs = (ArcNode *)malloc(sizeof(ArcNode));
		ArcNode * arce = (ArcNode *)malloc(sizeof(ArcNode));
		getchar();
		scanf("%d%d", &start, &end); 
		arce->adjvex = end ;
		arce->nextarc = g->vertices[start].firstarc;
		g->vertices[start].firstarc = arce;
		
		arcs->adjvex = start;
		arcs->nextarc = g->vertices[end].firstarc;
		g->vertices[end].firstarc = arcs;
		printf("这条边关联顶点%c和%c\n", g->vertices[start].data, g->vertices[end].data);
	}
	printf("无向图的构造成功！\n");
	return OK;
}

//输入顶点的值求其向量坐标 
int GetVex(ALGraph *g, VertexType v){
	
	int i;
	for( i = 0 ; i < g->vernum ; i++){
		if(g->vertices[i].data == v){
			return i;
		}
	}
	
	return ERROR;
} 

//输出某一个特定位置i顶点的值
Status LocateVex(ALGraph *g, int i ){

	if(g->vernum == 0){
		printf("出错，还没有构建此图！\n");
		return ERROR;
	} 
	if(i < g->vernum){
		printf("该顶点的值是：%c\n", g->vertices[i].data);
	}
	else{
		printf("输入错误,该图没有这么多的节点！\n");
		return ERROR; 
	}
	return OK;
} 

//对图中某一个顶点进行赋值,将顶点值为ch的顶点变成an 
Status PutVex(ALGraph *g,VertexType ch, VertexType an ){
	int i;
	if(g->vernum == 0){
		printf("出错，还没有构建此图！\n");
		return ERROR;
	} 
	for(i = 0; i < g->vernum;i++){
		if(g->vertices[i].data == ch){
			g->vertices[i].data = an; 
			printf("修改成功！\n");
		}
	}
	return OK;
} 

//获取顶点的第一个邻接顶点
ArcNode * FirstAdjVex(ALGraph *g, int VerLocation){
	if(VerLocation < g->vernum){
		return g->vertices[VerLocation].firstarc;
	} 
	return NULL;
}

//返回给定顶点的下一个邻接顶点

ArcNode * NextAdjVex(ALGraph *g, int VerLocation, ArcNode * adjarc){
	if(VerLocation < g->vernum){
		return adjarc->nextarc;
	} 
	return NULL;	
} 

//深度优先遍历
void DFSTraverse(ALGraph *g){
	int i;
	printf("深度遍历的结果：\n");
	for(i = 0; i < g->vernum ; i++){
		visited[i] = 0 ;
	}
	for(i = 0; i < g->vernum ; i++){
		if(visited[i] == 0){
			DFS(g, i);
		} 
	}
	
} 

void DFS(ALGraph *g, int v){
	
	ArcNode * w;
	visited[v] = 1;
	printf("%c  ", g->vertices[v].data);
	for(w = FirstAdjVex(g, v); w != NULL; w = NextAdjVex(g, v, w) ){
		if(visited[w->adjvex] == 0){
			DFS(g, w->adjvex);
		}
	}
}

//广度优先遍历

void BFSTraverse(ALGraph *g, LinkQueue *Q){	

	int i;
	
	ElemType v;
	ArcNode * w;
	printf("广度遍历的结果：\n");
	for(i = 0; i < g->vernum ; i++){
		visited[i] = 0 ;
	}
	for( i = 0; i < g->vernum ; i++){
		if(visited[i] == 0){
			visited[i] = 1;
			printf("%c  ", g->vertices[i].data);
			EnQueue(Q, i);
			while(QueueEmpty(Q) == 1){
				DeQueue(Q, &v);
				for(w = FirstAdjVex(g, v); w != NULL; w = NextAdjVex(g, v, w)){
					if(visited[w->adjvex] == 0){
						visited[w->adjvex] = 1;
						printf("%c  ", g->vertices[w->adjvex].data);
						EnQueue(Q,w->adjvex);
					}
				}
			}
		}
	}
	printf("\n");
} 


//连通图G以邻接表存储，查找并输出所有关节点，全局count对访问计数

void FindArticul(ALGraph *g){
	
	count = 1;
	visited[0] = 1;											//假设邻接表上的0号顶点为生成树的根 
	int i, v;
	ArcNode * p;
	for(i = 1 ; i < g->vernum ; i++){
		visited[i] = 0;											//初始化顶点，全部为0 
	}	
	p = g->vertices[0].firstarc;
	v = p->adjvex;
	DFSArticul(g , v);
	if(count < g->vernum){									  //生成树的根至少两个子树 
		printf("关节点：%c\n", g->vertices[0].data);			//输出根节点 
		while(p->nextarc){
			p = p->nextarc;
			v = p->adjvex;
			if(visited[v] == 0){
				DFSArticul(g, v);
			}
		}//while 
	}//if 
	
} 

//从第0个点出发深度优先遍历图g， 查找并输出关节点。
void DFSArticul(ALGraph *g , int v){
	
	int min, w;
	ArcNode * p;
	visited[v] = min = ++count;          //v是第count个访问的节点
	for( p = g->vertices[v].firstarc; p != NULL ; p = p->nextarc ){					//对v的每个邻接顶点检查 
		w = p->adjvex;
		if(visited[w] == 0){							//w为v的邻接点 
			DFSArticul(g, w);							//返回前求出low[w] 
			if(low[w] < min){
				min = low[w];
			}
			if(low[w] >= visited[v]){
				printf("关节点：%c\n", g->vertices[v].data);
			}
		}
		else{
			if(visited[w] < min ){
				min = visited[w]; 
			}
			
		}
		low[v] = min ;
	} 
	
} 

Status InitQueue(LinkQueue *Q){

    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q->front)
        return ERROR;
    Q->front->next = NULL;
    printf("队列初始化成功！\n");
    return OK;
}
//进队
Status EnQueue(LinkQueue *Q, ElemType e){
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if(!p)
        return ERROR;
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

//删除队头    --出队 
Status DeQueue(LinkQueue *Q, ElemType *e){

    QueuePtr p;

    if(Q->front == Q->rear)
        return ERROR;
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if(Q->rear == p)
        Q->rear = Q->front;
    free(p);
    //printf("删除队头成功！\n");
    return OK;
}
//销毁队列
Status DestoryQueue(LinkQueue *Q){
    while(Q->front){
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }

    //printf("销毁队列成功！\n");
    return OK;
}
//判断是否为空队列
 Status QueueEmpty(LinkQueue *Q){
    if(Q->front == Q->rear){
        //printf("队列为空\n");
        return ERROR;
    }
    //printf("队列不为空\n");
    return OK;
}
//求队列长度
int QueueLength(LinkQueue Q){
    if(QueueEmpty(&Q) == 0){
        return 0;
    }
    else{
        QueuePtr p;
        int i=0;
        p = Q.front->next;
        while(p){
            i++;
            p = p->next;
        }
        return i;
    }
}


int main(int argc, char *argv[]) {

	ALGraph *g;	
	LinkQueue Q;
	
	int vernum, arcnum, i;
	VertexType ch, an;
	//VNode * vnode;
	ArcNode * arc;
	g = (ALGraph *)malloc(sizeof(ALGraph));	
	CreateGraph(g);
	InitQueue(&Q);
	
	FindArticul(g); 
	
	/*printf("请输入顶点的值：\n");
	getchar();
	scanf("%c", &ch);
	printf("顶点的向量值是：%d\n", GetVex(g, ch));
	
	
	printf("请输入想要查询的顶点的位置：\n");
	scanf("%d", &i);
	LocateVex(g, i); 
	printf("请输入想要修改的顶点的原始值：\n");
	getchar();
	scanf("%c", &ch);
	printf("请输入想要修改的顶点的结果值：\n");
	getchar();
	scanf("%c",&an);
	PutVex(g, ch, an );
	printf("请输入想要查询的顶点的位置：\n");
	getchar();
	scanf("%d", &i);
	LocateVex(g, i);*/
	/*while(1){
			
	printf("请输入想要查询的顶点的索引（求他的第一个邻接顶点）,输入数字大于20退出循环\n");
	getchar();
	scanf("%d", &i);
	if(i > 20 ){
		break;
	}
	arc = FirstAdjVex(g, i);
	printf("他的第一个邻接顶点的值是：%c\n", g->vertices[arc->adjvex].data  );
	
	//getchar();
//	scanf("%d", &i);
	arc = NextAdjVex(g, i, arc);
	printf("他的相对于第一个邻接顶点下一个邻接顶点的值是：%c\n", g->vertices[arc->adjvex].data  );
	arc = NextAdjVex(g, i, arc);
	if(arc == NULL){
		printf("没有更多的邻接顶点！\n");
	} 
	else{
		printf("他的相对于第二个邻接顶点下一个邻接顶点的值是：%d\n",arc->adjvex);
	}
	
	}*/
	
	BFSTraverse(g, &Q);
	DFSTraverse(g);
	
	
	
	return 0;
}
