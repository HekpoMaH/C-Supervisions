#include<stdio.h>
#include<stdlib.h>
struct exprNode {
    enum { CONST, BIN_OP } code;
    union {
        double constant;
        struct {
            char op;
            struct exprNode *arg1, *arg2;
        } binop;
    } data;
};
typedef struct exprNode * ExprPtr;
double exprCalc(ExprPtr e){
    if(e->code==CONST)
        return e->data.constant;
    switch(e->data.binop.op){
        case '+':
            return exprCalc(e->data.binop.arg1)+exprCalc(e->data.binop.arg2);
        case '-':
            return exprCalc(e->data.binop.arg1)-exprCalc(e->data.binop.arg2);
        case '*':
            return exprCalc(e->data.binop.arg1)*exprCalc(e->data.binop.arg2);
        case '/':
            return exprCalc(e->data.binop.arg1)/exprCalc(e->data.binop.arg2);
        default:
            printf("Unknown operation\n");
            exit(0);
            break;
    }
}
int main(void){
    ExprPtr e=malloc(sizeof(struct exprNode));
    ExprPtr e2=malloc(sizeof(struct exprNode));
    ExprPtr e3=malloc(sizeof(struct exprNode));
    ExprPtr e4=malloc(sizeof(struct exprNode));
    ExprPtr e5=malloc(sizeof(struct exprNode));
    ExprPtr e6=malloc(sizeof(struct exprNode));
    ExprPtr e7=malloc(sizeof(struct exprNode));

    e2->code=CONST;
    e2->data.constant=3.0;
    e3->code=CONST;
    e3->data.constant=4.0;
    e6->code=BIN_OP;
    e6->data.binop.arg1=e2;
    e6->data.binop.arg2=e3;
    e6->data.binop.op='+';

    //(3+4)

    e4->code=CONST;
    e4->data.constant=6.0;
    e5->code=CONST;
    e5->data.constant=2.0;
    e7->code=BIN_OP;
    e7->data.binop.arg1=e4;
    e7->data.binop.arg2=e5;
    e7->data.binop.op='+';
    //(6+2)
    e->code=BIN_OP;
    e->data.binop.arg1=e6;
    e->data.binop.arg2=e7;
    e->data.binop.op='*';
    //(3+4)*(6+2)=7*8=56

    printf("%lf\n",exprCalc(e));
}
