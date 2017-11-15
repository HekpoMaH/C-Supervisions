#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 10 // set to sth larger if not testing
struct heap{
    int freeStart;
    int memory[SIZE+1];
};
typedef struct heap heap;
heap *init(){
    heap *re=malloc(sizeof(struct heap));
    re->freeStart=0;
    memset(re->memory,0,sizeof(re->memory));
    //for(int i=2;i<SIZE;i++)
    //    re->memory[i]=0;
    re->memory[0]=SIZE;
    re->memory[1]=-1;
    return re;
}
int allocate(heap *hp, int sz){
    if(hp==NULL){
        printf("Can't alloc from NULL heap!\n");
        return -1;
    }
    int curr=hp->freeStart;
    while(curr<SIZE&&curr!=-1){
        if(hp->memory[curr]>=sz+1){
            int newFree=hp->memory[curr];
            int tmp=hp->memory[curr+1];
            int ret=curr;

            hp->memory[curr]=sz+1;
            hp->memory[curr+1]=0;//0 for taken
            //only change if no gap
            if(curr==hp->freeStart)
                hp->freeStart+=sz+1;
            curr+=sz+1;
            hp->memory[curr]=newFree-sz-1;//calculate new number of free blocks
            if(curr+1<SIZE)//don't write the nxt free number if fully occupied heap
                hp->memory[curr+1]=tmp;
            return ret;
        }
        else{
            if(curr+1<SIZE)
                curr=hp->memory[curr+1];
            else
                break;
        }
    }
    printf("Cannot alloc: heap full or not enough large space");
    return -1;
}
void print(heap *hp){
    printf("\n");
    printf("----------------\n");
    for(int i=SIZE-1;i>=0;i--){
        printf("            %d: %d\n",i,hp->memory[i]);
    }
    printf("FreeStart: %d\n",hp->freeStart);
    printf("----------------\n");
}
void deallocate(heap* hp, int ptr){
    if(ptr+1<SIZE&&hp->memory[ptr+1]!=0){
        printf("CANNOT DEALLOCATE FREE MEMORY!!!\n");
        return;
    }
    if(hp->freeStart>ptr){
        hp->memory[ptr+1]=hp->freeStart>=SIZE ? -1 : hp->freeStart;//8->2 pointer in example
        hp->freeStart=ptr;
        return;
    }
    int curr=hp->memory[ptr];
    //int freePos=ptr+1;
    int nextFree=-1;
    int idx=ptr;
    while(idx<SIZE){
        if(idx+curr<SIZE&&hp->memory[idx+curr+1]!=0){
            nextFree=idx+curr;
            break;
        }
        idx+=hp->memory[idx];
        curr=hp->memory[idx];
    }
    if(ptr+1<SIZE){
        hp->memory[ptr+1]=nextFree;
    }
    idx=hp->freeStart;
    int prev;
    while(idx<ptr&&idx+1<SIZE&&hp->memory[idx+1]!=-1){
        prev=idx+1;
        idx=hp->memory[idx+1];
        if(hp->memory[prev]>ptr){
            hp->memory[prev]=ptr;
        }
    }
    if(idx+1<ptr&&idx+1<SIZE){
        hp->memory[idx+1]=ptr;
    }
    
    //combine stage
    idx=hp->freeStart;
    int dbg=1;
    while(idx+1<SIZE){
        int nextFree=hp->memory[idx+1];
        int sumMem=hp->memory[idx];
        if(dbg){
            dbg=0;
        }
        if(nextFree==-1)
            break;
        int calculated=idx+hp->memory[idx];//calculated .. ;)
        while(nextFree!=-1&&nextFree==calculated){
            int newNext=hp->memory[nextFree+1];
            int newCalc=calculated+hp->memory[calculated];
            sumMem+=hp->memory[calculated];
            hp->memory[nextFree+1]=0;
            hp->memory[nextFree]=0;
            nextFree=newNext;
            calculated=newCalc;
        }
        if(hp->memory[idx+1]!=nextFree){
            hp->memory[idx+1]=nextFree;
            hp->memory[idx]=sumMem;
        }
        else break;
    }
}
int main(void){
    heap *test;
    int p1,p2,p3,p4;
    //to be tested with SIZE 12
    //*test=init();
    //print(test);
    //p1=allocate(test,1);
    //print(test);
    //p2=allocate(test,2);
    //print(test);
    //p3=allocate(test,3);
    //print(test);
    //p4=allocate(test,2);
    //print(test);
    //deallocate(test,p1);
    //print(test);
    //deallocate(test,p3);
    //print(test);
    //deallocate(test,p2);
    //print(test);
    //deallocate(test,p4);
    //print(test);
    //free(test);
    //printf("***********************\n");
    //1)
    test=init();
    print(test);
    p1=allocate(test,4);
    print(test);
    p2=allocate(test,2);
    print(test);
    deallocate(test,p1);
    print(test);
    p3=allocate(test,1);
    print(test);
    free(test);
    //2)
    test=init();
    printf("***********************\n");
    p1=allocate(test,4);
    print(test);
    p2=allocate(test,4);
    print(test);
    deallocate(test,p1);
    print(test);
    deallocate(test,p2);
    print(test);
    p3=allocate(test,7);
    print(test);
}
