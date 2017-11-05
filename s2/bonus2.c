#include<stdlib.h>
#include<limits.h>
#include<stdio.h>
//wtf is that tree man,
//just implement a normal heap
//everyone does so
//this even has bad worst case complexity
struct node{
    int val;
    struct node *left,*right;
};
typedef struct node * Tree;
//tree is pointer to root 
//[start;end)
Tree create(int a[], int start, int end){
    if(start+1>end){
        return NULL;
    }
    if(start+1==end){
        Tree leaf=malloc(sizeof(struct node));
        leaf->val=a[start];
        return leaf;
    }
    int mnidx=-1;
    for(int i=start; i<end; i++){
        if(mnidx==-1||a[i]<a[mnidx]){
            mnidx=i;
        }
    }

    Tree l=create(a,start,mnidx);
    Tree r=create(a,mnidx+1,end);
    Tree ret=malloc(sizeof(struct node));
    ret->val=a[mnidx];
    ret->left=l;
    ret->right=r;
    return ret;
}
Tree createTournament(int a[], int size){
    return create(a,0,size);
}
//extra from me for printing
void parse(int level, Tree node){
    if(node==NULL)
        return;
    for(int i=0;i<2*level;i++)printf(" ");
    printf("%d\n",node->val);
    parse(level+1,node->left);
    parse(level+1,node->right);
}
void printPreorder(Tree node){
    if(node==NULL)
        return;
    printf("%d\n",node->val);
    printPreorder(node->left);
    printPreorder(node->right);
}
//N.B.
//Returns depth: root depth is 0
int extractMin(Tree *node){
    if(*node==NULL)
        return 0;
    int v1= (*node)->left==NULL ? INT_MAX : (*node)->left->val;
    int v2= (*node)->right==NULL ? INT_MAX : (*node)->right->val;
    if(v1==v2&&v1==INT_MAX){
        free((*node));
        (*node)=NULL;
        return 0;
    }
    if(v1 < v2){
        (*node)->val=v1;
        return extractMin(&(*node)->left)+1;
    }
    else{
        (*node)->val=v2;
        return extractMin(&(*node)->right)+1;
    }

}
int insert(Tree *node, int v){
    if(*node==NULL){
        *node=malloc(sizeof(struct node));
        (*node)->val=v;
        (*node)->left=(*node)->right=NULL;
        return 0;
    }
    if(v<(*node)->val){
        int tmp=(*node)->val;
        (*node)->val=v;
        v=tmp;
    }
    int v1= (*node)->left==NULL ? INT_MAX: (*node)->left->val;
    int v2= (*node)->right==NULL ? INT_MAX: (*node)->right->val;
    //insert into larger always
    if(v1<v2)
        return insert(&(*node)->right,v)+1;
    else
        return insert(&(*node)->left,v)+1;
}
void simul(Tree t,int M,double p,int K){
    int visExtract=0;
    int visInsert=0;
    int opExtract=0,opInsert=0;

    for(int i=0;i<M;i++){
        double prob=(double)rand()/(double)RAND_MAX;
        if(prob<p){
            visExtract+=extractMin(&t);
            opExtract++;
        }
        else{
            visInsert+=insert(&t,rand()%K+1);
            opInsert++;
        }
    }
    //Printing interface credit to Tom Benn
    printf("Extractions: %d   Insertions: %d\n", opExtract, opInsert);
    printf("     Visits: %d       Visits: %d\n", visExtract, visInsert);
    printf("Average visits per op: %f\n", ((double) (visExtract + visInsert)) / ((double) (opExtract + opInsert)));
}
int main(void){
    srand(47);//my lucky number
    int n=100;
    int K=10000;
    int M=500;
    double p=1.0/3.0;
    int a[100];
    for(int i=0;i<n;i++)a[i]=rand()%K+1;
    Tree t=createTournament(a,n);
    simul(t,M,p,K);
    //int a[9]={22,48,13,97,35,3,17,5,53};
    //Tree t=createTournament(a,9);
    //parse(0,t);
    //printf("\n");
    //printf("%d\n",insert(&t,2));
    //printf("%d\n",insert(&t,26));
    //parse(0,t);
    //printPreorder(t);
    //for(int i=0;i<9;i++){
    //    printf("%d\n",extractMin(&t));
    //    //parse(0,t);
    //    printf("\n");
    //}
}
