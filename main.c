#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main(int argc, char *argv[]) {

	ALGraph *g;	
	LinkQueue Q;
	sqStack S;
	sqStack T;
	
	int vernum, arcnum, i;
	VertexType ch, an;
	//VNode * vnode;
	ArcNode * arc;
	g = (ALGraph *)malloc(sizeof(ALGraph));	
	CreateGraph(g);
	InitQueue(&Q);
	InitStack(&S);
	InitStack(&T);
	if(g->kind == DG){
		
		TopologicalSort(g, &S);
	}
	if(g->kind == DN){
		//TopologicalOrder(g, &S, &T);
		CriticalPath(g, &S, &T);
	}
	if(g->kind == UDG){
		FindArticul(g); 
		BFSTraverse(g, &Q);
		DFSTraverse(g);
	}
	if(g->kind == UDN){
		printf("UDN\n");
	}
		
	
	
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
	

	
	
	
	return 0;
}
