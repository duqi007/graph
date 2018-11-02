#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


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


