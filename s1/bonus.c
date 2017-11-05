#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef struct {
double x;
double y;
}
point;
typedef struct node {
point data; /* Node data */
struct node *next; /* Pointer to the next node */
} *node_t;
void InsertPoint(node_t *list, point p){
    if((*list)==NULL){
        (*list)=(node_t)malloc(sizeof(node_t));
        (*list)->data=p;
        (*list)->next=NULL;
        return;
    }
    //if((*list)->next==NULL){
    //    node_t nw=(node_t)malloc(sizeof(node_t));
    //    nw->data=p;
    //    nw->next=NULL;
    //    (*list)->next=nw;
    //    return;
    //}
    InsertPoint(&((*list)->next),p);
}
int ListLength(node_t list){
    return list==NULL ? 0 : 1+ListLength(list->next);
}
void PrintPoints(node_t list){
    if(list==NULL)
        return;
    printf("(%lf,%lf)\n",list->data.x,list->data.y);
    PrintPoints(list->next);
}
//Function needs to be named SeekNDestroy
//\m/
void SearchDestroy(node_t *list){
    if((*list)==NULL)
        return;
    //find furthest
    //mx stands for max
    node_t curr=*list,mx,prev=NULL;
    double mx_dist=curr->data.x*curr->data.x+curr->data.y*curr->data.y;
    mx=curr;
    curr=curr->next; while(curr!=NULL){
        double dist=curr->data.x*curr->data.x+curr->data.y*curr->data.y;
        if(dist>mx_dist){
            mx_dist=dist;
            mx=curr;
        }
        curr=curr->next;
    }
    //and destroy
    if(mx==(*list)){ // if it's the head just removing it
        (*list)=mx->next;
        free(mx);
        return;
    }
    else { //keep track of the previous element so you could relink
           // p -> c -> n to be
           // p -> n  and free c
        prev=(*list);
        assert(list!=NULL);
        curr=(*list)->next;
        while(curr!=NULL){
            if(curr==mx){
                prev->next=curr->next;
                free(curr);
                return;
            }
            prev=curr;
            curr=curr->next;
        }
    }

}
int main(void){
    node_t nd = NULL;
    point pp;
    pp.x=9;pp.y=5;
    InsertPoint(&nd,pp);
    pp.x=91;pp.y=15;
    InsertPoint(&nd,pp);
    pp.x=1;pp.y=1;
    InsertPoint(&nd,pp);
    pp.x=0;pp.y=1;
    InsertPoint(&nd,pp);
    PrintPoints(nd);
    printf("-----------\n");
    SearchDestroy(&nd);
    PrintPoints(nd);
    printf("-----------\n");
    SearchDestroy(&nd);
    PrintPoints(nd);
    printf("-----------\n");
    SearchDestroy(&nd);
    PrintPoints(nd);
    printf("-----------\n");
    SearchDestroy(&nd);
    PrintPoints(nd);
    printf("-----------\n");
    SearchDestroy(&nd);
    PrintPoints(nd);
    printf("-----------\n");
    SearchDestroy(&nd);
    PrintPoints(nd);
    printf("-----------\n");
}
