#include<stdio.h>
int main(void){
    int A[]={1,2,3,4,5};
    int* ptr=A+5;
    int* ptr2=A;
    printf("%d\n",*ptr);//should be undefined
    printf("%d\n",*(ptr-3));//should give 3
    printf("%li\n",ptr-ptr2);//should give 0x00 00 00 05 = 5 in decimal
    printf("%d\n",*(ptr-1) + 2);//5+2 = 7
    printf("%d\n",&ptr);//gives address of ptr
}
