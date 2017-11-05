#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//gonna be circular
#define SIZE 3
//Just to check circularity SIZE is 3
//otherwise set sth large
struct LinkedList{
    int start,end,size;
    int list[SIZE];
};
typedef struct LinkedList LinkedList;
//push to end
void push(LinkedList *lst, int data){
    if(lst->size==SIZE){
        printf("no empty space\n");
        return;
    }
    lst->list[lst->end]=data;
    lst->end++;
    lst->end%=SIZE;
    lst->size++;
}
void create(LinkedList **lst){
    *lst=malloc(sizeof(LinkedList));
    (*lst)->start=0;
    (*lst)->end=0;
    (*lst)->size=0;
}
//pop from front
int pop(LinkedList *lst){
    if(lst==NULL){
        printf("List pointer is NULL! Can't pop element!\n");
        return -1;//some error value
    }
    if(lst->size==0){
        printf("List is empty! Can't pop element!\n");
        return -1;//some error value
    }
    int ret=lst->list[lst->start];
    lst->start++;
    lst->start%=SIZE;
    lst->size--;
    return ret;
}
int main(void){
    LinkedList *test;
    create(&test);
    push(test,1);
    push(test,2);
    push(test,3);
    push(test,3);//prints NoSpace
    printf("%d\n",pop(test));
    printf("%d\n",pop(test));
    push(test,4);
    push(test,5);
    printf("%d\n",pop(test));
    printf("%d\n",pop(test));
    printf("%d\n",pop(test));
    printf("%d\n",pop(test));//List empty - prints -1
    free(test);
}
