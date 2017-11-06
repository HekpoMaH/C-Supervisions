#include<stdio.h>
#include<stdlib.h>
struct List { 
    int head;
    struct List *tail;
};
typedef struct List List;
//from lecture practicals
List *cons(int head, List *tail) { 
    List *cell = malloc(sizeof(List));
    cell->head = head;
    cell->tail = tail;
    return cell;
}

void push(List **stack,int el){
    *stack=cons(el,*stack);
}
int pop(List **stack){
    //some err value
    if(stack==NULL)
        return -1;
    if(*stack==NULL)
        return -1;

    int ret=(*stack)->head;
    *stack=(*stack)->tail;
    return ret;
}
int main(void){
    List *stack=NULL;
    push(&stack,1);
    push(&stack,2);
    push(&stack,3);
    printf("%d\n",pop(&stack));
    printf("%d\n",pop(&stack));
    printf("%d\n",pop(&stack));
    printf("%d\n",pop(&stack));
}
