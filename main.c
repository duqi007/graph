#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM		20
#define OK					1
#define ERROR				0


typedef enum { DG, DN, UDG, UDN }  GraphKind ;
typedef char 				VertexType;
typedef int 				Status;
typedef int 				ElemType;

//------------ͼ���ڽӱ�Ĵ洢-----------------// 
//���Ľṹ�� 
typedef struct ArcNode{
	int adjvex;							//�û���ָ��Ķ�����Ϣ 
	struct ArcNode * nextarc;			//ָ����һ������ָ��  
}ArcNode;

//����Ľṹ�� 
typedef struct VNode{
	VertexType data;					//������Ϣ 
	ArcNode * firstarc;					//ָ���һ�������ڸö���Ļ���ָ�� 
}VNode, AdjList[MAX_VERTEX_NUM]; 

//ͼ�Ľṹ�� 
typedef struct{
	AdjList vertices;					 
	int vernum, arcnum;					//ͼ�ж���ͻ��ĸ��� 
	GraphKind kind;						//ͼ������ 
} ALGraph;

//------------��ʽ���еĴ洢�ṹ------------------------// 
typedef struct QNode{
    ElemType data;
    struct QNode * next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front;         //��ͷָ��
    QueuePtr rear;          //��βָ��
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
	printf("��������Ҫ������ͼ�����ͣ������·���Ӧ�����֣�\n");
	printf("0: ����ͼDG\n");
	printf("1: ������DN\n");
	printf("2: ����ͼUDG\n");
	printf("3: ������UDN\n");
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
	printf("�����붥�����ͱ�����\n");
	scanf("%d%d", &g->vernum, &g->arcnum );
	printf("%d  %d\n", g->vernum, g->arcnum);
	printf("�����붥�����Ϣ��\n");
	for( i = 0; i < g->vernum ; i++){
		VNode *ver = (VNode *)malloc(sizeof(VNode));
		getchar(); 
		scanf("%c", &ver->data); 
		
		printf("��%d������Ϊ��%c\n", i, ver->data);
		ver->firstarc = NULL;
		g->vertices[i] = (*ver);
		
	}
	printf("�����뻡����Ϣ������ͷ�ͻ�β��ͼ�е����꣬���ÿո������һ������һ������\n");
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
		printf("�����߹�������%c��%c\n", g->vertices[start].data, g->vertices[end].data);
	}
	printf("����ͼ�Ĺ���ɹ���\n");
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

//��ȡ����ĵ�һ���ڽӶ���
ArcNode * FirstAdjVex(ALGraph *g, int VerLocation){
	if(VerLocation < g->vernum){
		return g->vertices[VerLocation].firstarc;
	} 
	return NULL;
}

//���ظ����������һ���ڽӶ���

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

Status InitQueue(LinkQueue *Q){

    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q->front)
        return ERROR;
    Q->front->next = NULL;
    printf("���г�ʼ���ɹ���\n");
    return OK;
}
//����
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

//ɾ����ͷ    --���� 
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
    //printf("ɾ����ͷ�ɹ���\n");
    return OK;
}
//���ٶ���
Status DestoryQueue(LinkQueue *Q){
    while(Q->front){
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }

    //printf("���ٶ��гɹ���\n");
    return OK;
}
//�ж��Ƿ�Ϊ�ն���
 Status QueueEmpty(LinkQueue *Q){
    if(Q->front == Q->rear){
        //printf("����Ϊ��\n");
        return ERROR;
    }
    //printf("���в�Ϊ��\n");
    return OK;
}
//����г���
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
	
	/*printf("�����붥���ֵ��\n");
	getchar();
	scanf("%c", &ch);
	printf("���������ֵ�ǣ�%d\n", GetVex(g, ch));
	
	
	printf("��������Ҫ��ѯ�Ķ����λ�ã�\n");
	scanf("%d", &i);
	LocateVex(g, i); 
	printf("��������Ҫ�޸ĵĶ����ԭʼֵ��\n");
	getchar();
	scanf("%c", &ch);
	printf("��������Ҫ�޸ĵĶ���Ľ��ֵ��\n");
	getchar();
	scanf("%c",&an);
	PutVex(g, ch, an );
	printf("��������Ҫ��ѯ�Ķ����λ�ã�\n");
	getchar();
	scanf("%d", &i);
	LocateVex(g, i);*/
	/*while(1){
			
	printf("��������Ҫ��ѯ�Ķ���������������ĵ�һ���ڽӶ��㣩,�������ִ���20�˳�ѭ��\n");
	getchar();
	scanf("%d", &i);
	if(i > 20 ){
		break;
	}
	arc = FirstAdjVex(g, i);
	printf("���ĵ�һ���ڽӶ����ֵ�ǣ�%c\n", g->vertices[arc->adjvex].data  );
	
	//getchar();
//	scanf("%d", &i);
	arc = NextAdjVex(g, i, arc);
	printf("��������ڵ�һ���ڽӶ�����һ���ڽӶ����ֵ�ǣ�%c\n", g->vertices[arc->adjvex].data  );
	arc = NextAdjVex(g, i, arc);
	if(arc == NULL){
		printf("û�и�����ڽӶ��㣡\n");
	} 
	else{
		printf("��������ڵڶ����ڽӶ�����һ���ڽӶ����ֵ�ǣ�%d\n",arc->adjvex);
	}
	
	}*/
	
	BFSTraverse(g, &Q);
	DFSTraverse(g);
	
	
	
	return 0;
}
