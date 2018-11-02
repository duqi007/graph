#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Status InitStack(sqStack *S){
    S->base = (SElemType * )malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S->base){
        exit(0);
    }
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    printf("栈初始化成功！\n");
    return OK;

}


Status Push(sqStack *S, SElemType e)
{
    if(S->top - S->base >= S->stacksize)           //栈满， 追加空间
    {
        S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT)* sizeof(SElemType));
        if(!S->base){
            exit(0);                 //分配失败
        }
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }

    *(S->top) = e;
    S->top++;
    return OK;
}

Status Pop(sqStack *S, SElemType *e){
    if(S->top == S->base){
        return ERROR;                  //判空
    }
    *e = * --(S->top);
    return OK;
}

Status GetTop(sqStack *S, SElemType *e){
    if(S->top == S->base){
        return ERROR;
    }
    *e = *(S->top-1);
    return OK;

}

Status DestroyStack(sqStack *S){
    free(S);
    return OK;
}
Status ClearStack(sqStack *S){

    S->top = S->base;
    S->stacksize = 0;
    return OK;
}
int StackLength(sqStack s){
    return (s.top - s.base);
}

Status StackEmpty(sqStack S){
    if(S.top - S.base == 0){
        //printf("StackEmpty()当前栈为空！\n");
        return ERROR;
    }
    return OK;
}
//从栈底开始依次显示栈内元素
Status StackTraverse(sqStack S){
    SElemType e;
    sqStack T;              //辅助栈
    InitStack(&T);
    if(StackEmpty(S) == 0){
        printf("当前栈为空！\n");
        return ERROR;
    }
    while(1){
        if(StackEmpty(S) == 0){
            break;
        }
        Pop(&S, &e);

        Push(&T,e);
    }
    while(1){
        if(StackEmpty(T) == 0){
            break;
        }
        Pop(&T, &e);
        visit(e);
        Push(&S, e);
    }
    printf("\n");
    return OK;
}

void visit(SElemType e){
    printf("%d  ", e);
}


