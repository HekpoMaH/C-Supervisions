#include "stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
void push(StackType *ps, int data){
    if(ps->top==SIZE-1){
        printf("Stack full! No push!\n");
        return;
    }
    ps->elements[++(ps->top)]=data;
}
int pop(StackType *ps){
    if(ps==NULL){
        printf("Stack pointer is NULL! Can't take top element!\n");
        return -1;//some error value
    }
    if(ps->top==-1){
        printf("Stack is empty! Can't take top element!\n");
        return -1;//some error value
    }
    return ps->elements[(ps->top)--];
}
int main(void){
    StackType *someStack;
    someStack=malloc(sizeof(someStack));
    someStack->top=-1;
    push(someStack,1);
    push(someStack,2);
    push(someStack,3);
    push(someStack,4);
    push(someStack,5);
    printf("%d\n",pop(someStack));
    printf("%d\n",pop(someStack));
    printf("%d\n",pop(someStack));
    printf("%d\n",pop(someStack));
    printf("%d\n",pop(someStack));
    printf("%d\n",pop(someStack));
    printf("%d\n",pop(someStack));
    free(someStack);
    someStack=NULL;
    printf("%d\n",pop(someStack));
}
