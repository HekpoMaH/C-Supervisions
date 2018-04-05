#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define MB 1024 * 1024

int main() {
    //no need to use memcpy...
    int a[MB];
    clock_t start;
    //takes 0.007317s 
    start=clock();
    for(int i=0;i<MB;i++)
        a[i]=i;
    printf("%.8lf\n",(double)(clock()-start)/CLOCKS_PER_SEC);

    //takes 24.402593s 
    start=clock();
    for(int k=0;k<10000;k++){
        for(int i=0;i<MB;i++)
            a[i]++;//just to access that value
    }
    printf("%.8lf\n",(double)(clock()-start)/CLOCKS_PER_SEC);
    start=clock();

    //takes 19.594413s which is less than the previous and it's not due to variations
    unsigned long steps= 10000L*MB;
    for(unsigned long k=0;k<steps;k++){
        a[0]++;
    }
    printf("%.8lf\n",(double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
