#include <stdio.h>
#include <stdlib.h>
 
#define SIZE 10
 
typedef struct heap{
  int freestart;
  int mem[SIZE];
} *Heap;
 
Heap createheap(){
  //Create a heap
  Heap myheap = malloc(sizeof(struct heap));
  if(myheap == NULL){
    printf("Heap cannot be allocated\n");
    return NULL;
  }
 
  //Initialise it
  myheap->freestart = 0;
  myheap->mem[0] = SIZE; 
  myheap->mem[1] = -1; 
  for(int i = 2; i < SIZE; i++){
    myheap->mem[i] = 0;
  }
  return myheap;
}
int allocate(Heap h, int size){
  if (h == NULL) return -1;
 
  int i = h->freestart;
  while(i < SIZE){
    if(h->mem[i] >= size+1){ 
      //Allocate here
      int fullsize = h->mem[i];
      h->mem[i] = size+1;
      int nxt = h->mem[i+1];
      h->mem[i+1] = 0;
 
      int ret = i;
 
      if(i == h->freestart){
        h->freestart += size + 1;
      }
      i += size + 1;
      h->mem[i] = fullsize - size - 1;
      h->mem[i+1] = nxt; //Could fail if heap full
 
      return ret;
    }else{
      //Jump to next free block
      if(h->mem[i+1] != -1){
        i = h->mem[i+1];
      }else{
        printf("Heap full");
        return -1;
      }
    }
  }
}
 
void deallocate(Heap h, int loc){
  if(h->freestart > loc){
    //Update freestart
    h->mem[loc+1] = h->freestart;
    h->freestart = loc;
  }else{
    //Find next, previous free block
    int prev = h->freestart;
    int iter = h->mem[prev+1];
    while(iter != -1 && iter < loc){
      int nxt = h->mem[iter+1];
      prev = iter;
      iter = nxt;
    }
 
    if(iter == -1){
        //Either merge loc with iter
        //Or add loc to freelist
        printf("%d DOBO\n",iter);
        if(loc == iter + h->mem[iter]){
          //Merge loc into iter
          h->mem[iter] += h->mem[loc];
          h->mem[loc] = 0;
        }else{
          //Add loc to freelist
          h->mem[iter+1] = loc;
          h->mem[loc+1] = -1;
        }
    }else{
      //Update prev size, next pointer
      if(iter == loc + h->mem[loc] && loc == prev + h->mem[prev] ){
        //Create continuous free space
        h->mem[prev] += h->mem[loc] + h->mem[iter];
        h->mem[prev+1] = h->mem[iter+1];
 
        //Clear data (for legibility)
        h->mem[loc] = 0;
        h->mem[loc+1] = 0;
        h->mem[iter] = 0;
        h->mem[iter+1] = 0;
      }else if(iter == loc + h->mem[loc]) {
        //Add iter to this block's space 
        h->mem[loc] += h->mem[iter];
        h->mem[loc+1] = h->mem[iter+1];
 
        h->mem[iter] = h->mem[iter+1] = 0;
      }else if(loc == prev + h->mem[prev]){
        //Add this block's space to prev
        h->mem[prev] += h->mem[loc];
 
        h->mem[loc] = h->mem[loc+1] = 0;
      }else{
        //Free this block, connect prev to this
        //And this to iter
        h->mem[prev+1] = loc;
        h->mem[loc+1] = iter;
      }
    }
  }
}
 
void printheap(Heap h){
  for(int i = SIZE-1; i >= 0; i--){
    printf("%d: %d\n", i, h->mem[i]);
  }
  printf("\n");
}
 
int main(void){
  Heap myheap = createheap();
  printheap(myheap);
  
  /*Easy*/
  int p1 = allocate(myheap, 4);
  printheap(myheap);
  int p2 = allocate(myheap, 2);
  printheap(myheap);
  deallocate(myheap, p1);
  printheap(myheap);
  int p3 = allocate(myheap, 1);
  printheap(myheap);
   
  printf("====================\n");
 
  free(myheap);
  myheap = createheap();
  /*Tough*/
  p1 = allocate(myheap, 4);
  printheap(myheap);
  p2 = allocate(myheap, 4);
  printheap(myheap);
  deallocate(myheap, p1);
  printheap(myheap);
  deallocate(myheap, p2);
  printheap(myheap);
  p3 = allocate(myheap, 7);
  printheap(myheap);
 
  return 0;
}
