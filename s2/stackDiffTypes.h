#define SIZE 100
struct stackElement{
    int type;
    //lets say 1 for int, 2 for char and 3 for double for this example
    union data{
        int iData;
        char cData;
        double dData;
    }data;
};
typedef struct stackElement stackEl;
struct stackDiffTypes{
    int top;
    stackEl elements[SIZE];
};
typedef struct stackDiffTypes StackType;
void push(StackType *ps, stackEl se);
stackEl pop(StackType *ps);
