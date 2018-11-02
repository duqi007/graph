

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

//------------��ʽ���еĴ洢�ṹ------------------------// 
typedef struct QNode{
    ElemType data;
    struct QNode * next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front;         //��ͷָ��
    QueuePtr rear;          //��βָ��
}LinkQueue;


typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}sqStack;

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



int visited[MAX_VERTEX_NUM];
int count;
int low[MAX_VERTEX_NUM];
int indegree[MAX_VERTEX_NUM];


int QueueLength(LinkQueue Q);						//���еĳ��ȣ�Ԫ�ظ��� 
Status QueueEmpty(LinkQueue *Q);					//�ж��Ƿ�Ϊ�� 
Status DestoryQueue(LinkQueue *Q);					//���ٶ��� 
Status DeQueue(LinkQueue *Q, ElemType *e);			//����
Status EnQueue(LinkQueue *Q, ElemType e);			//���� 
Status InitQueue(LinkQueue *Q);						//��ʼ������ 

void visit(SElemType e);                            //��ʾԪ�صĺ���
Status InitStack(sqStack *S);                       //��ʼ��ջ
Status Push(sqStack *S, SElemType e);               //ѹջ
Status Pop(sqStack *S, SElemType *e);               //��ջ
Status GetTop(sqStack *S, SElemType *e);            //��ȡջ��Ԫ�أ���ɾ��ջ��Ԫ��
Status DestroyStack(sqStack *S);                    //����ջ
Status ClearStack(sqStack *S);                      //���ջ
int StackLength(sqStack s);                         //��ȡ��ǰջ�ĳ���
Status StackEmpty(sqStack S);                       //�ж�ջ�Ƿ�Ϊ��
Status StackTraverse(sqStack S);                    //����ջԪ����ʾ����

Status CreateGraph(ALGraph *g);
Status CreateUDG(ALGraph *g);											//��������ͼ 
Status CreateDG(ALGraph *g);											//��������ͼ 
Status LocateVex(ALGraph *g, int i );									//���ĳһ���ض�λ��i�����ֵ 
Status PutVex(ALGraph *g,VertexType ch, VertexType an );				//��ͼ��ĳһ��������и�ֵ,������ֵΪch�Ķ�����an 
ArcNode * FirstAdjVex(ALGraph *g, int VerLocation);						//��ȡ����ĵ�һ�����ӵı� 
ArcNode * NextAdjVex(ALGraph *g, int VerLocation, ArcNode * adjarc);	//���ظ����������һ�����ӵı�
void DFSTraverse(ALGraph *g);											//������ȱ��� 
void DFS(ALGraph *g, int v); 
void BFSTraverse(ALGraph *g, LinkQueue *Q);								//������ȱ��� 
int GetVex(ALGraph *g, VertexType v);									//���붥���ֵ������������
void FindArticul(ALGraph *g);											//��ͨͼG���ڽӱ�洢�����Ҳ�������йؽڵ㣬ȫ��count�Է��ʼ���
void DFSArticul(ALGraph *g , int v);									//�ӵ�0�������������ȱ���ͼg�� ���Ҳ�����ؽڵ㡣
Status TopologicalSort(ALGraph *g, sqStack *S);							//�����޻�ͼg���������� 
void FindInDegree(ALGraph *g, int indegree[MAX_VERTEX_NUM]);			//��ͼg���������� 
