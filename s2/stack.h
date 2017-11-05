#define SIZE 100
struct stack{
    int top;
    int elements[SIZE];
};
typedef struct stack StackType;
void push(StackType *ps, int data);
int pop(StackType *ps);
