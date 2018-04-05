#include<stdlib.h>
#include<stdio.h>
struct LinkedElement{
    int val;
    struct LinkedElement *next;
};
typedef struct LinkedElement LinkedElement;
void print(LinkedElement *head){
    while(head!=NULL){
        printf("%d ",head->val);
        head = head->next;
    }
    puts("\n");
}
void add(LinkedElement **head,int element){
    LinkedElement *head2=*head;
    LinkedElement *prev=head2;
    while(head2!=NULL){
        prev=head2;
        head2 = (head2)->next;
    }
    head2 = malloc(sizeof(LinkedElement));
    (head2)->val = element;
    (head2)->next = NULL;

    if(*head==NULL)
        *head=head2;
    else
        prev->next=head2;

}
typedef LinkedElement* LinkedArray;
int main(void){
    LinkedElement **A=malloc(3*sizeof(LinkedElement));
    add((&A[0]),1);
    add((&A[1]),2);
    add((&A[2]),3);
    add((&A[0]),4);
    add((&A[1]),5);
    add((&A[2]),6);
    print(A[0]);//1 4
    print(A[1]);//2 5
    print(A[2]);//4 6
}
