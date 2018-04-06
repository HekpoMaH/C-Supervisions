#include<stdlib.h>
#include<stdio.h>
int current_element=0;
int total_element=0;
char *dynamic=NULL;
int addelement(char c){
    if(total_element==0){
        //this usually works, so I don't add error handling
        dynamic=malloc(sizeof(char));
        total_element=1;
        current_element=1;
        dynamic[0]=c;
        //puts("initial allocation\n");
        return 0;
    }
    char *tmp=NULL;
    //amortize the cost
    if(current_element==total_element){
        tmp=realloc(dynamic,total_element*2*sizeof(char));
        if(tmp==NULL){
            //fail
            return 1;
        }
        dynamic=tmp;
        total_element*=2;
        //puts("size doubled\n");
    }
    dynamic[current_element]=c;
    current_element++;
    return 0;
}
//for testing purposes
int addelement_stupid(char c){
    char *tmp=NULL;
    if(current_element==total_element){
        //NOTE the mistake here
        tmp=malloc((total_element+10)*sizeof(char));
        if(tmp==NULL){
            //fail
            return 1;
        }
        dynamic=tmp;
        total_element+=10;
        //puts("plus 10\n");
    }
    dynamic[current_element]=c;
    current_element++;
    return 0;
}
void print(){
    for(int i=0;i<current_element;i++){
        printf("%d ",(int)dynamic[i]);//I'm printing them as ints for testing
    }
    puts("\n");
}
int main(void){
    //Correct usage
    //for(int i=0;i<300000;i++){
    //    if(addelement((char)i)!=0){
    //        puts("OOM error\n");
    //    }
    //    //print();
    //}
    //
    //
    //uncomment for testing just for the first two.
    //the other example wants to get an OOM error
    //
    ////correct solution uses addelement which uses realloc and 
    ////array doubling (for amortized cost)
    ////for testing purposes I used a 'stupid one' which just increases with 10 elements each time
    ////so if you use it with realloc (as in the normal case)
    ////the total memory usage was: 1636Kbytes.
    ////Use 'command time -v ./executable' and the 'maximum resident set size'
    ////is your total mem usage.
    ////when you do the same experiment, but with malloc and not freeing
    ////(therefore leaking memory) your total usage is 188196Kbytes
    ////(several magnitutes larger).
    ////Therefore realloc works correctly in the implementation
    //for(int i=0;i<300000;i++){
    //    if(addelement_stupid((char)i)!=0){
    //        puts("OOM error\n");
    //    }
    //    //print();
    //}
    //
    //
    //
    //TROLOLOLO example
    //N.B. Limit process memory beforehand if you use addelement_stupid
    //I had to restart my computer the first time as it crashed
    //use ulimit -v (KBytes) to set the vmemory to the desired Kbytes
    //when used with 2GB vmemory the code below crashes on k=0 and i=206250
    //when used with the addelement and same restrictions it works totally fine
    for(int k=0;k<=100;k++)for(int i=0;i<300000;i++){
        //with 
        if(addelement_stupid((char)i)!=0){
            puts("OOM error\n");
            printf("%d %d\n",k,i);
            return 0;
        }
        //print();
    }

}
