#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


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


