/*--------------------------------------------------------
 * Author: Isbah Ameer
 * Date: December 6th, 2024
 * Description: Implementation of memstats to print blocks, 
 * memory allocated and underutilized memory
 -------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "rand.h"


#define ROUNDS 3
#define BUFFER 5
#define LOOP 10

struct chunk {
  int size;
  int used;
  struct chunk *next;
};

void memstats(struct chunk *freelist, void *buffer[], int len) {
    // track stats
    int btotal = 0, bused = 0, bfree = 0;
    int mtotal = 0, mused = 0, mfree = 0;

    // transverse blocks in buffer
    for (int i = 0; i < len; i++) {
        if (buffer[i] != NULL) {
            struct chunk *current_chunk = (struct chunk *)buffer[i] - 1;
            btotal++;
            bused++;
            mtotal += current_chunk->size;
            mused += current_chunk->used;
        }
    }

    // transverse freelist
    struct chunk *current = freelist;
    while (current != NULL) {
        btotal++;
        bfree++;
        mtotal += current->size;
        mfree += current->size; 
        current = current->next;
    }

    //calculate size of heap
    void *heap_top = sbrk(0);
    void *heap_start = (void *)freelist;
    int total_heap_allocated = (char *)heap_top - (char *)heap_start;

    //calculate underutilized memory
    int underutilized_memory = total_heap_allocated - mused;
    double underutilized_percent = (double)underutilized_memory / total_heap_allocated;

    //print statistics
    printf("Total blocks: %d Free blocks: %d Used blocks: %d\n", btotal, bfree, bused);
    printf("Total memory allocated: %d Free memory: %d Used memory: %d\n", mtotal, mfree, mused);
    printf("Underutilized memory: %.2f\n", underutilized_percent);
}


int main ( int argc, char* argv[]) {

  printf("Starting test..\n");

  srand(100);

  double timer;
  struct timeval tstart, tend;

  gettimeofday(&tstart, NULL);

  void *buffer[BUFFER];
  for (int i = 0; i < BUFFER; i++) {
    buffer[i] = NULL;
  }


  void *init = sbrk(0);

  void *current;
  printf("The initial top of the heap is %p.\n", init);
  for (int j = 0 ; j < ROUNDS; j++) {
    printf("---------------\n%d\n" , j);

    for (int i= 0 ; i < LOOP ; i++) {
      int index = rand() % BUFFER;
      if (buffer[index] != NULL) {
        free(buffer[index]);
        buffer[index] = NULL;
        printf("Freeing index %d\n", index);
      } 
      else {
        size_t size = (size_t) randExp(8, 4000); 
        int *memory = NULL;
        memory = malloc(size);

        if (memory == NULL) {
          fprintf(stderr, "malloc failed\n");
          return(1);
        } 
        *memory = 123;
        buffer[index] = memory;
        printf("Allocating %d bytes at index %d\n", (int) size, index);
      }
    }
    extern struct chunk* flist;

    current = sbrk(0);

    int allocated = current - init;
    init = current;

    printf("The new top of the heap is %p.\n", current);
    printf("Increased by %d (0x%x) bytes\n", allocated, allocated);
    memstats(flist, buffer, BUFFER);
  }

  for (int i = 0; i < BUFFER; i++) {
    free(buffer[i]); 
  }
  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Time is %g\n", timer);
  return 0 ;
}
