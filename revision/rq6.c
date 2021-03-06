#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
typedef struct node {
    int row, column;
    double value;
    struct node* rowPtr;
    struct node* colPtr;
} node;

typedef struct matrix {
    node** rowList; // rowList is a pointer to the array of rows
    node** columnList; // column list is a pointer to the array of columns.
    int rows, columns; // store the number of rows and columns of the matrix
} matrix;

matrix *test=NULL;
matrix* allocate(int n, int m){
    matrix *re=malloc(sizeof(matrix));
    re->rows=n;
    re->columns=m;
    re->rowList=malloc(sizeof(node*)*n);
    re->columnList=malloc(sizeof(node*)*m);
    return re;
}

void printRow(node *rw){
    if(rw==NULL){
        puts("NULL");
        return;
    }
    //Row Col Val
    printf("(%d,%d,%lf) -> ",rw->row, rw->column, rw->value);
    printRow(rw->rowPtr);
}

//Code duplication :(
void printCol(node *col){
    if(col==NULL){
        puts("NULL");
        return;
    }
    //Row Col Val
    printf("(%d,%d,%lf) -> ",col->row, col->column, col->value);
    printCol(col->colPtr);
}

void print(matrix *m){
    for(int i=0;i<(m->rows);i++){
        printf("row %d->",i);
        printRow(m->rowList[i]);
        puts("");
    }
}

void printByCol(matrix *m){
    for(int i=0;i<(m->columns);i++){
        printf("col %d->",i);
        printCol(m->columnList[i]);
        puts("");
    }
}

void copyElement(node *x, node **c){
    (*c)=malloc(sizeof(node));
    (*c)->value=x->value;
    (*c)->row=x->row;
    (*c)->column=x->column;
    (*c)->rowPtr=x->rowPtr;
    (*c)->colPtr=x->colPtr;
}
void increaseColIdx(node *x){
    if(x==NULL)
        return;
    x->column++;
    increaseColIdx(x->rowPtr);
}

void changeColPtrs(matrix **m,node *x){
    //if it was (only one row)
    //0  1  2  3
    //|  |  |  |
    //v  v  v  v
    //1
    //
    //and 2 gets added
    //gets changed to
    //0  1  2  3
    //|  |  |  |
    //v  v  v  v
    //2  1
    //(empty means NULL)
    //
    for(int i=(*m)->columns-1;i>=1;i--){
        (*m)->columnList[i]=(*m)->columnList[i-1];
    }
    (*m)->columnList[0]=x;
}
void addPointer(matrix **m,node *x){
    node *cp=NULL;
    node *prev=NULL;
    node *firstInCol=NULL;
    for(int i=0;i<((*m)->rows);i++){
        copyElement(x,&cp);
        if(prev!=NULL){
            prev->colPtr=cp;
            assert(cp!=NULL);
        }
        cp->row=i;
        cp->rowPtr=(*m)->rowList[i];
        increaseColIdx((*m)->rowList[i]);
        (*m)->rowList[i]=cp;
        prev=cp;
        if(firstInCol==NULL){
            firstInCol=cp;
        }
    }
    changeColPtrs(m,firstInCol);
}

//for help in testing
void addElement(double x){
    node *tmp=malloc(sizeof(node));
    tmp->value=x;
    tmp->rowPtr=tmp->colPtr=NULL;
    tmp->column=0;
    addPointer(&test,tmp);
    tmp=NULL;
}

int searchRow(double value, node *rw){
    if(rw==NULL)
        return 0;
    if(rw->value==value)
        return 1;
    return searchRow(value, rw->rowPtr);
}
int searchCol(double value, node *col){
    if(col==NULL)
        return 0;
    if(col->value==value)
        return 1;
    return searchCol(value, col->colPtr);
}
int duplicateValue(matrix *M, double value){
    for(int i=0;i<(M->rows);i++){
        if(searchRow(value,M->rowList[i]))
            return 1;
    }

    //in case matrix was sparser than in our case
    for(int i=0;i<(M->columns);i++){
        if(searchCol(value,M->columnList[i]))
            return 1;
    }
    return 0;
}

int resize(matrix **m){
    (*m)->rows=(*m)->rows*2;
    (*m)->columns=(*m)->columns*2;
    node **tmp=NULL;
    tmp=realloc((*m)->rowList,sizeof(node*)*(*m)->rows);
    if(tmp==NULL)
        return 0;
    (*m)->rowList=tmp;

    tmp=NULL;
    tmp=realloc((*m)->columnList,sizeof(node*)*(*m)->columns);
    if(tmp==NULL)
        return 0;
    (*m)->columnList=tmp;
    return 1;
}
int main(void){
    test=allocate(3,4);
    assert(test!=NULL);
    addElement(9);
    print(test);
    puts("");
    printByCol(test);
    puts("-------");

    addElement(6);
    print(test);
    puts("");
    printByCol(test);
    puts("-------");

    addElement(6.5f);
    print(test);
    puts("");
    printByCol(test);
    puts("-------");
    
    addElement((double)1/3);
    print(test);
    puts("");
    printByCol(test);
    puts("-------");

    printf("%d\n",duplicateValue(test,9.0f));
    printf("%d\n",duplicateValue(test,19.0f));
    puts("----------");

    //test until it breaks
    //(USE ulimit for safety)
    for(int i=0;i<100;i++){
        printf("%d %d\n",i,resize(&test));
    }
    //somewhere ~ i=31 gives segfault

}
