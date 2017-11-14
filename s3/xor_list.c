#include<stdio.h>
#include<stdlib.h>
struct listElement{
    struct listElement *ptr;
    int data;
};
typedef struct listElement listElement;

listElement* xor(listElement *f, listElement *s){
    return (listElement*)((unsigned long)f ^ (unsigned long)s);
}
//easier to insert at head, like ML's
void cons(listElement **lst,int newData){   
    listElement *node=malloc(sizeof(listElement));
    node->data=newData;
    node->ptr=xor(*lst,NULL);
    if(*lst){
        (*lst)->ptr=xor((*lst)->ptr,node);
    }
    *lst=node;
}
//get's last element (pointer to it);
//NOT TO BE CONFUSED WITH ML'S TAIL AND THE OTHER TAIL FUNCTION
listElement *get_tail(listElement *lst){
    if(lst==NULL){
        printf("Can't reach tail element. LIST NULL FFS\n");
        return NULL;
    }
    listElement *p=lst;
    listElement *prev=NULL;
    do{
        listElement *tmp=p;
        p=xor(p->ptr,prev);
        prev=tmp;
    }while(p);
    return prev;
}
//tail([1,2,3])=[2,3]
listElement* tail(listElement *lst){
    if(lst==NULL){
        printf("Can't take tail. LIST NULL FFS\n");
        return NULL;
    }
    listElement *tmp=lst;
    lst=lst->ptr;
    lst->ptr=xor(lst->ptr,tmp);
    free(tmp);
    return lst;
}
void traverse_forward(listElement* lst){
    listElement *p=lst;
    listElement *prev=NULL;
    do{
        printf("%d\n",p->data);
        listElement *tmp=p;
        p=xor(p->ptr,prev);
        prev=tmp;
    }while(p);
}
void traverse_backward(listElement* lst){
    traverse_forward(get_tail(lst));//it's that simple :D
}
int main(){
    listElement *lst=NULL;
    cons(&lst,1);
    cons(&lst,2);
    cons(&lst,3);
    traverse_forward(lst);
    printf("----------\n");
    traverse_backward(lst);
    printf("----------\n");
    lst=tail(lst);
    traverse_forward(lst);
    printf("----------\n");
}
