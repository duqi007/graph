#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


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
			CreateDG(g);
			break;
		case 1:
			CreateDN(g);
			break;
		case 2:
			CreateUDG(g);
			break;
		case 3:
			CreateUDN(g);
			break;
		default:
			return ERROR;
	}
	return OK;
}
 
Status CreateDG(ALGraph *g)						// 创建有向图 
{
	
	int i;
	int start , end ;
	g->kind = DG;
	printf("请输入有向图的顶点数和边数！\n");
	scanf("%d%d", &g->vernum, &g->arcnum );
	printf("请输入顶点的信息！\n");
	for( i = 0; i < g->vernum ; i++){							//初始化图的顶点 
		VNode *ver = (VNode *)malloc(sizeof(VNode));
		getchar(); 
		scanf("%c", &ver->data); 
		
		printf("第%d个顶点为：%c\n", i, ver->data);
		
		ver->firstarc = NULL;
		g->vertices[i] = (*ver);
	}
	printf("请输入弧的信息！（弧头和弧尾在图中的坐标，并用空格隔开！一次输入一个弧）\n");
	for(i =0 ; i < g->arcnum ; i++){									//初始化边，构造图 
		
		ArcNode * arc = (ArcNode *)malloc(sizeof(ArcNode));
		getchar();
		scanf("%d%d", &start, &end); 
		arc->adjvex = end ;
		arc->info = NULL; 
		arc->nextarc = g->vertices[start].firstarc;
		g->vertices[start].firstarc = arc;
		printf("这条边是顶点%c指向顶点%c的边\n", g->vertices[start].data, g->vertices[end].data);
	}
	printf("有向图的构造成功！\n");
	return OK;
} 

Status CreateDN(ALGraph *g)						// 创建有向图 
{
	
	int i;
	int start , end ;
	
	g->kind = DN;
	printf("请输入有向图的顶点数和边数！\n");
	scanf("%d%d", &g->vernum, &g->arcnum );
	printf("请输入顶点的信息！\n");
	for( i = 0; i < g->vernum ; i++){							//初始化图的顶点 
		VNode *ver = (VNode *)malloc(sizeof(VNode));
		getchar(); 
		scanf("%c", &ver->data); 
		
		printf("第%d个顶点为：%c\n", i, ver->data);
		
		ver->firstarc = NULL;
		g->vertices[i] = (*ver);
	}
	printf("请输入弧的信息！（弧头和弧尾以及权值在图中的坐标，并用空格隔开！一次输入一个弧）\n");
	
	for(i =0 ; i < g->arcnum ; i++){									//初始化边，构造图 
		
		ArcNode * arc = (ArcNode *)malloc(sizeof(ArcNode));
		getchar();
		scanf("%d%d%d", &start, &end, &info[i]); 
		 
		arc->adjvex = end ;
		arc->info = &info[i] ;
		arc->nextarc = g->vertices[start].firstarc;
		g->vertices[start].firstarc = arc;
		
	//	printf("这条边是顶点%c指向顶点%c的边权值为：%d\n", g->vertices[start].data, g->vertices[end].data, *(g->vertices[start].firstarc->info));
	}
	for(i =0 ; i < g->arcnum ; i++){
		ArcNode *p = NULL;
		for(p = g->vertices[i].firstarc; p != NULL ; p = p->nextarc ){
			printf("这条边是顶点%c指向顶点%c的边权值为：%d\n", g->vertices[i].data , g->vertices[p->adjvex].data , *(p->info) );
		}	
	}
	printf("有向网的构造成功！\n");
	return OK;
} 

Status CreateUDG(ALGraph *g){					// 创建无向图 
	int i;
	int start , end ;
	g->kind = UDG;
	printf("请输入无向图的顶点数和边数！\n");
	scanf("%d%d", &g->vernum, &g->arcnum );
	printf("%d  %d\n", g->vernum, g->arcnum);
	printf("请输入顶点的信息！\n");
	for( i = 0; i < g->vernum ; i++){						//初始化图的顶点 
		VNode *ver = (VNode *)malloc(sizeof(VNode));
		getchar(); 
		scanf("%c", &ver->data); 
		
		printf("第%d个顶点为：%c\n", i, ver->data);
		ver->firstarc = NULL;
		g->vertices[i] = (*ver);
		
	}
	printf("请输入弧的信息！（弧头和弧尾在图中的坐标，并用空格隔开！一次输入一个弧）\n");
	for(i =0 ; i < g->arcnum ; i++){									//初始化边，构造图 
		ArcNode * arcs = (ArcNode *)malloc(sizeof(ArcNode));
		ArcNode * arce = (ArcNode *)malloc(sizeof(ArcNode));
		getchar();
		scanf("%d%d", &start, &end); 
		arce->adjvex = end ;
		arce->info = NULL; 
		arce->nextarc = g->vertices[start].firstarc;
		g->vertices[start].firstarc = arce;
		
		arcs->adjvex = start;
		arcs->info = NULL; 
		arcs->nextarc = g->vertices[end].firstarc;
		g->vertices[end].firstarc = arcs;
		printf("这条边关联顶点%c和%c\n", g->vertices[start].data, g->vertices[end].data);
	}
	printf("无向图的构造成功！\n");
	return OK;
}


Status CreateUDN(ALGraph *g){					// 创建无向图 
	int i;
	int start , end ;
	
	g->kind = UDN;
	printf("请输入无向图的顶点数和边数！\n");
	scanf("%d%d", &g->vernum, &g->arcnum );
	printf("%d  %d\n", g->vernum, g->arcnum);
	printf("请输入顶点的信息！\n");
	for( i = 0; i < g->vernum ; i++){						//初始化图的顶点 
		VNode *ver = (VNode *)malloc(sizeof(VNode));
		getchar(); 
		scanf("%c", &ver->data); 
		
		printf("第%d个顶点为：%c\n", i, ver->data);
		ver->firstarc = NULL;
		g->vertices[i] = (*ver);
		
	}
	printf("请输入弧的信息！（弧头和弧尾在图中的坐标，并用空格隔开！一次输入一个弧）\n");
	for(i =0 ; i < g->arcnum ; i++){									//初始化边，构造图 
		ArcNode * arcs = (ArcNode *)malloc(sizeof(ArcNode));
		ArcNode * arce = (ArcNode *)malloc(sizeof(ArcNode));
		getchar();
		scanf("%d%d%d", &start, &end, &info); 
		arce->adjvex = end ;
		arce->info = &info[i]; 
		arce->nextarc = g->vertices[start].firstarc;
		g->vertices[start].firstarc = arce;
		
		arcs->adjvex = start;
		arcs->info = &info[i]; 
		arcs->nextarc = g->vertices[end].firstarc;
		g->vertices[end].firstarc = arcs;
		printf("这条边关联顶点%c和%c权值为：%d\n", g->vertices[start].data, g->vertices[end].data, *(g->vertices[start].firstarc->info));
	}

	printf("无向网的构造成功！\n");
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

//获取顶点的第一个连接的边 
ArcNode * FirstAdjVex(ALGraph *g, int VerLocation){
	if(VerLocation < g->vernum){
		return g->vertices[VerLocation].firstarc;
	} 
	return NULL;
}

//返回给定顶点的下一个连接的边

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


Status TopologicalSort(ALGraph *g, sqStack *S){													//有向无环图g的拓扑排序 

	int i , OutputVex, k;
	ArcNode *p;
	FindInDegree(g, indegree);
	for(i = 0; i < g->vernum ; i++){
		if(indegree[i] == 0){						//建零入度顶点栈S 
			Push(S, i);								
		} 
		//printf("顶点%c的入度是：%d \n", g->vertices[i].data , indegree[i] );
	}
	//StackTraverse((*S)); 										//输出栈中的元素 
	OutputVex = 0;
	printf("有向图的一种拓扑排序是：\n");
	while(StackEmpty((*S)) == 1){								//栈不为空循环 
		Pop(S, &i); 
		printf("%c  ", g->vertices[i].data);
		++OutputVex;
		for(p = g->vertices[i].firstarc; p != NULL ; p = p->nextarc ){
			k = p->adjvex;
			if((--indegree[k]) == 0 ){
				Push(S , k);
			}
		}//for
	}//while
	if(OutputVex < g->vernum){
		return ERROR;
	}
	else{
		return OK;
	}
} 		//TopologicalSort

void FindInDegree(ALGraph *g, int InDegree[MAX_VERTEX_NUM])										//求个顶点的入度 
{

	int i,j;
	ArcNode *p;
	for(i = 0; i < g->vernum ; i++){
		
		InDegree[i] = 0  ;
	}
	
	for(i = 0; i < g->vernum ; i++){
		for(p = g->vertices[i].firstarc ; p != NULL ; p = p->nextarc){
			InDegree[p->adjvex] += 1  ;
		}	
	} 

} // FindInDegree


//有向网g采用邻接表存储的结构，求各个顶点事件的最早发生时间ve(全局变量)
// T为拓扑序列顶点栈，S为零入度顶点栈
//若g无回路，则T返回g的一个拓扑序列，且函数值为OK，否则为ERROR 
Status TopologicalOrder(ALGraph *g, sqStack *S, sqStack *T){
	
	int i , OutputVex, k;
	ArcNode *p;

	FindInDegree(g, indegree); 
	for(i = 0; i < g->vernum ; i++){
		ve[i] = 0;									//初始化ve[]; 
		if(indegree[i] == 0){						//建零入度顶点栈S 
			Push(S, i);								
		} 
		//printf("顶点%c的入度是：%d \n", g->vertices[i].data , indegree[i] );
	}
	OutputVex = 0;
	while(StackEmpty((*S)) == 1){								//栈不为空循环 
		Pop(S, &i); 
		Push(T, i);
		++OutputVex;
		for(p = g->vertices[i].firstarc; p != NULL ; p = p->nextarc ){
			k = p->adjvex;
			if((--indegree[k]) == 0 ){
				Push(S , k);
			}
			
			if(ve[i] + *(p->info) > ve[k] ){
				ve[k] = ve[i] + *(p->info); 
			}
		}//for    *(p->info) = dut(<i, k>)
	}//while 
/*	for(i = 0; i < g->vernum ; i++){
		printf("%d \n", ve[i]);							//初始化ve[]; 
	}*/
	if(OutputVex < g->vernum){
		return ERROR;
	}
	else{
		return OK;
	}
} // TopologicalOrder

//输出g的各项关键活动 
Status CriticalPath(ALGraph *g , sqStack *S, sqStack *T){
	
	int i, k;
	ArcNode *p;
	InfoType dut;

	if(TopologicalOrder(g, S, T ) == 0)
		return ERROR; 
	
	for(i = 0; i < g->vernum ; i++){
		vl[i] = ve[ g->vernum - 1 ] ;								//初始化vl[]; 
	}	
	while(StackEmpty((*T)) == 1){
		Pop(T, &i); 
		for( p = g->vertices[i].firstarc; p != NULL ; p = p->nextarc ){
			k = p->adjvex;
			dut = *(p->info);						//dut<i, k>
			if(vl[k] - dut < vl[i]){
				vl[i] = vl[k] - dut;
			}
		}//for
	}
	int ee,el;
	for(i = 0; i < g->vernum ;  i++ ){
		for(p = g->vertices[i].firstarc ;  p != NULL ; p = p->nextarc){
			k = p->adjvex;
			dut = *(p->info);
			ee = ve[i]; 
			el = vl[k] - dut;
			
			if(ee == el){
				printf("%c-----%c = %d\n", g->vertices[i].data, g->vertices[k].data, dut);
			}
			
		}
	}
	 
	return OK;
}
