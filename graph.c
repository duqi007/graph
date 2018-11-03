#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


Status CreateGraph(ALGraph *g){
	int kind;
	printf("��������Ҫ������ͼ�����ͣ������·���Ӧ�����֣�\n");
	printf("0: ����ͼDG\n");
	printf("1: ������DN\n");
	printf("2: ����ͼUDG\n");
	printf("3: ������UDN\n");
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
 
Status CreateDG(ALGraph *g)						// ��������ͼ 
{
	
	int i;
	int start , end ;
	g->kind = DG;
	printf("����������ͼ�Ķ������ͱ�����\n");
	scanf("%d%d", &g->vernum, &g->arcnum );
	printf("�����붥�����Ϣ��\n");
	for( i = 0; i < g->vernum ; i++){							//��ʼ��ͼ�Ķ��� 
		VNode *ver = (VNode *)malloc(sizeof(VNode));
		getchar(); 
		scanf("%c", &ver->data); 
		
		printf("��%d������Ϊ��%c\n", i, ver->data);
		
		ver->firstarc = NULL;
		g->vertices[i] = (*ver);
	}
	printf("�����뻡����Ϣ������ͷ�ͻ�β��ͼ�е����꣬���ÿո������һ������һ������\n");
	for(i =0 ; i < g->arcnum ; i++){									//��ʼ���ߣ�����ͼ 
		
		ArcNode * arc = (ArcNode *)malloc(sizeof(ArcNode));
		getchar();
		scanf("%d%d", &start, &end); 
		arc->adjvex = end ;
		arc->info = NULL; 
		arc->nextarc = g->vertices[start].firstarc;
		g->vertices[start].firstarc = arc;
		printf("�������Ƕ���%cָ�򶥵�%c�ı�\n", g->vertices[start].data, g->vertices[end].data);
	}
	printf("����ͼ�Ĺ���ɹ���\n");
	return OK;
} 

Status CreateDN(ALGraph *g)						// ��������ͼ 
{
	
	int i;
	int start , end ;
	
	g->kind = DN;
	printf("����������ͼ�Ķ������ͱ�����\n");
	scanf("%d%d", &g->vernum, &g->arcnum );
	printf("�����붥�����Ϣ��\n");
	for( i = 0; i < g->vernum ; i++){							//��ʼ��ͼ�Ķ��� 
		VNode *ver = (VNode *)malloc(sizeof(VNode));
		getchar(); 
		scanf("%c", &ver->data); 
		
		printf("��%d������Ϊ��%c\n", i, ver->data);
		
		ver->firstarc = NULL;
		g->vertices[i] = (*ver);
	}
	printf("�����뻡����Ϣ������ͷ�ͻ�β�Լ�Ȩֵ��ͼ�е����꣬���ÿո������һ������һ������\n");
	
	for(i =0 ; i < g->arcnum ; i++){									//��ʼ���ߣ�����ͼ 
		
		ArcNode * arc = (ArcNode *)malloc(sizeof(ArcNode));
		getchar();
		scanf("%d%d%d", &start, &end, &info[i]); 
		 
		arc->adjvex = end ;
		arc->info = &info[i] ;
		arc->nextarc = g->vertices[start].firstarc;
		g->vertices[start].firstarc = arc;
		
	//	printf("�������Ƕ���%cָ�򶥵�%c�ı�ȨֵΪ��%d\n", g->vertices[start].data, g->vertices[end].data, *(g->vertices[start].firstarc->info));
	}
	for(i =0 ; i < g->arcnum ; i++){
		ArcNode *p = NULL;
		for(p = g->vertices[i].firstarc; p != NULL ; p = p->nextarc ){
			printf("�������Ƕ���%cָ�򶥵�%c�ı�ȨֵΪ��%d\n", g->vertices[i].data , g->vertices[p->adjvex].data , *(p->info) );
		}	
	}
	printf("�������Ĺ���ɹ���\n");
	return OK;
} 

Status CreateUDG(ALGraph *g){					// ��������ͼ 
	int i;
	int start , end ;
	g->kind = UDG;
	printf("����������ͼ�Ķ������ͱ�����\n");
	scanf("%d%d", &g->vernum, &g->arcnum );
	printf("%d  %d\n", g->vernum, g->arcnum);
	printf("�����붥�����Ϣ��\n");
	for( i = 0; i < g->vernum ; i++){						//��ʼ��ͼ�Ķ��� 
		VNode *ver = (VNode *)malloc(sizeof(VNode));
		getchar(); 
		scanf("%c", &ver->data); 
		
		printf("��%d������Ϊ��%c\n", i, ver->data);
		ver->firstarc = NULL;
		g->vertices[i] = (*ver);
		
	}
	printf("�����뻡����Ϣ������ͷ�ͻ�β��ͼ�е����꣬���ÿո������һ������һ������\n");
	for(i =0 ; i < g->arcnum ; i++){									//��ʼ���ߣ�����ͼ 
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
		printf("�����߹�������%c��%c\n", g->vertices[start].data, g->vertices[end].data);
	}
	printf("����ͼ�Ĺ���ɹ���\n");
	return OK;
}


Status CreateUDN(ALGraph *g){					// ��������ͼ 
	int i;
	int start , end ;
	
	g->kind = UDN;
	printf("����������ͼ�Ķ������ͱ�����\n");
	scanf("%d%d", &g->vernum, &g->arcnum );
	printf("%d  %d\n", g->vernum, g->arcnum);
	printf("�����붥�����Ϣ��\n");
	for( i = 0; i < g->vernum ; i++){						//��ʼ��ͼ�Ķ��� 
		VNode *ver = (VNode *)malloc(sizeof(VNode));
		getchar(); 
		scanf("%c", &ver->data); 
		
		printf("��%d������Ϊ��%c\n", i, ver->data);
		ver->firstarc = NULL;
		g->vertices[i] = (*ver);
		
	}
	printf("�����뻡����Ϣ������ͷ�ͻ�β��ͼ�е����꣬���ÿո������һ������һ������\n");
	for(i =0 ; i < g->arcnum ; i++){									//��ʼ���ߣ�����ͼ 
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
		printf("�����߹�������%c��%cȨֵΪ��%d\n", g->vertices[start].data, g->vertices[end].data, *(g->vertices[start].firstarc->info));
	}

	printf("�������Ĺ���ɹ���\n");
	return OK;
}
//���붥���ֵ������������ 
int GetVex(ALGraph *g, VertexType v){
	
	int i;
	for( i = 0 ; i < g->vernum ; i++){
		if(g->vertices[i].data == v){
			return i;
		}
	}
	
	return ERROR;
} 

//���ĳһ���ض�λ��i�����ֵ
Status LocateVex(ALGraph *g, int i ){

	if(g->vernum == 0){
		printf("������û�й�����ͼ��\n");
		return ERROR;
	} 
	if(i < g->vernum){
		printf("�ö����ֵ�ǣ�%c\n", g->vertices[i].data);
	}
	else{
		printf("�������,��ͼû����ô��Ľڵ㣡\n");
		return ERROR; 
	}
	return OK;
} 

//��ͼ��ĳһ��������и�ֵ,������ֵΪch�Ķ�����an 
Status PutVex(ALGraph *g,VertexType ch, VertexType an ){
	int i;
	if(g->vernum == 0){
		printf("������û�й�����ͼ��\n");
		return ERROR;
	} 
	for(i = 0; i < g->vernum;i++){
		if(g->vertices[i].data == ch){
			g->vertices[i].data = an; 
			printf("�޸ĳɹ���\n");
		}
	}
	return OK;
} 

//��ȡ����ĵ�һ�����ӵı� 
ArcNode * FirstAdjVex(ALGraph *g, int VerLocation){
	if(VerLocation < g->vernum){
		return g->vertices[VerLocation].firstarc;
	} 
	return NULL;
}

//���ظ����������һ�����ӵı�

ArcNode * NextAdjVex(ALGraph *g, int VerLocation, ArcNode * adjarc){
	if(VerLocation < g->vernum){
		return adjarc->nextarc;
	} 
	return NULL;	
} 

//������ȱ���
void DFSTraverse(ALGraph *g){
	int i;
	printf("��ȱ����Ľ����\n");
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

//������ȱ���

void BFSTraverse(ALGraph *g, LinkQueue *Q){	

	int i;
	
	ElemType v;
	ArcNode * w;
	printf("��ȱ����Ľ����\n");
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


//��ͨͼG���ڽӱ�洢�����Ҳ�������йؽڵ㣬ȫ��count�Է��ʼ���

void FindArticul(ALGraph *g){
	
	count = 1;
	visited[0] = 1;											//�����ڽӱ��ϵ�0�Ŷ���Ϊ�������ĸ� 
	int i, v;
	ArcNode * p;
	for(i = 1 ; i < g->vernum ; i++){
		visited[i] = 0;											//��ʼ�����㣬ȫ��Ϊ0 
	}	
	p = g->vertices[0].firstarc;
	v = p->adjvex;
	DFSArticul(g , v);
	if(count < g->vernum){									  //�������ĸ������������� 
		printf("�ؽڵ㣺%c\n", g->vertices[0].data);			//������ڵ� 
		while(p->nextarc){
			p = p->nextarc;
			v = p->adjvex;
			if(visited[v] == 0){
				DFSArticul(g, v);
			}
		}//while 
	}//if 
	
} 

//�ӵ�0�������������ȱ���ͼg�� ���Ҳ�����ؽڵ㡣
void DFSArticul(ALGraph *g , int v){
	
	int min, w;
	ArcNode * p;
	visited[v] = min = ++count;          //v�ǵ�count�����ʵĽڵ�
	for( p = g->vertices[v].firstarc; p != NULL ; p = p->nextarc ){					//��v��ÿ���ڽӶ����� 
		w = p->adjvex;
		if(visited[w] == 0){							//wΪv���ڽӵ� 
			DFSArticul(g, w);							//����ǰ���low[w] 
			if(low[w] < min){
				min = low[w];
			}
			if(low[w] >= visited[v]){
				printf("�ؽڵ㣺%c\n", g->vertices[v].data);
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


Status TopologicalSort(ALGraph *g, sqStack *S){													//�����޻�ͼg���������� 

	int i , OutputVex, k;
	ArcNode *p;
	FindInDegree(g, indegree);
	for(i = 0; i < g->vernum ; i++){
		if(indegree[i] == 0){						//������ȶ���ջS 
			Push(S, i);								
		} 
		//printf("����%c������ǣ�%d \n", g->vertices[i].data , indegree[i] );
	}
	//StackTraverse((*S)); 										//���ջ�е�Ԫ�� 
	OutputVex = 0;
	printf("����ͼ��һ�����������ǣ�\n");
	while(StackEmpty((*S)) == 1){								//ջ��Ϊ��ѭ�� 
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

void FindInDegree(ALGraph *g, int InDegree[MAX_VERTEX_NUM])										//����������� 
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


//������g�����ڽӱ�洢�Ľṹ������������¼������緢��ʱ��ve(ȫ�ֱ���)
// TΪ�������ж���ջ��SΪ����ȶ���ջ
//��g�޻�·����T����g��һ���������У��Һ���ֵΪOK������ΪERROR 
Status TopologicalOrder(ALGraph *g, sqStack *S, sqStack *T){
	
	int i , OutputVex, k;
	ArcNode *p;

	FindInDegree(g, indegree); 
	for(i = 0; i < g->vernum ; i++){
		ve[i] = 0;									//��ʼ��ve[]; 
		if(indegree[i] == 0){						//������ȶ���ջS 
			Push(S, i);								
		} 
		//printf("����%c������ǣ�%d \n", g->vertices[i].data , indegree[i] );
	}
	OutputVex = 0;
	while(StackEmpty((*S)) == 1){								//ջ��Ϊ��ѭ�� 
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
		printf("%d \n", ve[i]);							//��ʼ��ve[]; 
	}*/
	if(OutputVex < g->vernum){
		return ERROR;
	}
	else{
		return OK;
	}
} // TopologicalOrder

//���g�ĸ���ؼ�� 
Status CriticalPath(ALGraph *g , sqStack *S, sqStack *T){
	
	int i, k;
	ArcNode *p;
	InfoType dut;

	if(TopologicalOrder(g, S, T ) == 0)
		return ERROR; 
	
	for(i = 0; i < g->vernum ; i++){
		vl[i] = ve[ g->vernum - 1 ] ;								//��ʼ��vl[]; 
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
