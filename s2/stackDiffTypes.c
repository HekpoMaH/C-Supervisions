#include "stackDiffTypes.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
void push(StackType *ps, stackEl se){
    if(ps->top==SIZE-1){
        printf("Stack full! No push!\n");
        return;
    }
    (ps->top)++;
    //ps->elements[ps->top]=malloc(sizeof(stackEl));
    ps->elements[ps->top]=se;
}
stackEl pop(StackType *ps){
    stackEl ret;
    if(ps==NULL){
        printf("Stack pointer is NULL! Can't take top element!\n");
        exit(0);
    }
    if(ps->top==-1){
        printf("Stack is empty! Can't take top element!\n");
        exit(0);
    }
    ret=ps->elements[ps->top];
    ps->top--;
    return ret;
}
void print(stackEl se){
    if(se.type==1)
        printf("%d\n",se.data.iData);
    if(se.type==2)
        printf("%c\n",se.data.cData);
    if(se.type==3)
        printf("%lf\n",se.data.dData);
}
int main(void){
    StackType *someStack;
    someStack=malloc(sizeof(someStack));
    someStack->top=-1;
    stackEl *se=malloc(sizeof(stackEl));
    se->type=1;
    se->data.iData=9;
    push(someStack,*se);

    se=malloc(sizeof(stackEl));
    se->type=1;
    se->data.iData=4;
    push(someStack,*se);

    se=malloc(sizeof(stackEl));
    se->type=2;
    se->data.cData='b';
    push(someStack,*se);
    se=malloc(sizeof(stackEl));
    se->type=3;
    se->data.dData=(double)3.14;
    push(someStack,*se);
    print(pop(someStack));//prints 3.14
    print(pop(someStack));//prints a
    print(pop(someStack));//prints 4
    print(pop(someStack));//prints 9

}
