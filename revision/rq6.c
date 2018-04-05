#include<stdlib.h>
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

matrix* allocate(int n, int m){
    matrix *re=malloc(sizeof(matrix));
    re->rows=n;
    re->columns=m;
    re->rowList=malloc(sizeof(node*)*n);
    re->columnList=malloc(sizeof(node*)*m);
    return re;
}
int main(void){
    matrix *test=NULL;
    test=allocate(3,4);
    assert(test!=NULL);
}
