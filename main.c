#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main(int argc, char *argv[]) {

	ALGraph *g;	
	LinkQueue Q;
	sqStack S;
	
	int vernum, arcnum, i;
	VertexType ch, an;
	//VNode * vnode;
	ArcNode * arc;
	g = (ALGraph *)malloc(sizeof(ALGraph));	
	CreateGraph(g);
	InitQueue(&Q);
	InitStack(&S);
	
	TopologicalSort(g, &S);
	
	
	//FindArticul(g); 
	
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
	
	//BFSTraverse(g, &Q);
	//DFSTraverse(g);
	
	
	
	return 0;
}
