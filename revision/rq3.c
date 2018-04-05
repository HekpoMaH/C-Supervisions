//This is the way I'd handle 2d arrays with int**
#include<stdlib.h>
#include<stdio.h>
int COLS=4;
int ROWS=5;
//foo wasn't declared
int foo(int*** array);
int main( ) {
    //change to initialisation
    int** A = malloc(ROWS * sizeof(int*));

    //prevous had no allocation for each row
    for(int i=0;i<ROWS;i++){
        A[i]=malloc(COLS*sizeof(int));
    }
    A[0][0]=1;
    foo(&A);
    ROWS *= 2;
    printf("%d\n",A[0][0]);
    A[9][0]=1;//doesn't segfault so it's doubled
    return 0;
}
int foo(int*** array){
    //change to init
    int** arrayint = malloc(2*ROWS*sizeof(int*));
    //Malloc the rest of the rows, not all of them.
    //Doing malloc to the first ROWS rows 
    //will resund in a memory leak,
    //since after that each arrayint [0;ROWS)
    //will be set to point at (*array)[0;ROWS)
    //and those allocated before that will hang somewhere
    //in the memory, not freed
    for(int i=ROWS;i<2*ROWS;i++){
        arrayint[i]=malloc(COLS*sizeof(int));
    }

    //i was undeclared before that
    for (int i=0; i < ROWS; i ++)
        arrayint[i] = (*array)[i];

    
    free(*array);

    //N.B. Note the change
    //array is local, but what is pointed to is not
    (*array) = arrayint;
    return 0;
}
