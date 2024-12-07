/*--------------------------------------------------------
 * Author: Isbah Ameer
 * Date: December 6th, 2024
 * Description: Custom mplementation of malloc and free 
 -------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//memory chunk struct
struct chunk {
    int size;
    int used;
    struct chunk *next;
};

//flist head
struct chunk *flist = NULL;

//custom implementation of malloc
void *malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    struct chunk *prev = NULL;
    struct chunk *current = flist;

    //first fit strategy
    while (current != NULL) {
        if (current->size >= size) {
            // find suitable chunk
            current->used = size;

            // remove from flist
            if (prev == NULL) {
                flist = current->next;
            } else {
                prev->next = current->next;
            }

            return (void *)(current + 1);
        }
        prev = current;
        current = current->next;
    }
    //if no suitable is available, request more memory in heap

    struct chunk *new_chunk = sbrk(size + sizeof(struct chunk));
   
    if (new_chunk == (void *)-1) {
        return NULL;
    }

    new_chunk->size = size;
    new_chunk->used = size;
    new_chunk->next = NULL;

    return (void *)(new_chunk + 1);
}

//custom implementation of free
void free(void *memory) {
    if (memory == NULL) {
        return;
    }

    // retrieve chunk
    struct chunk *chunk_to_free = (struct chunk *)memory - 1;
    chunk_to_free->used = 0;

    // add to flist
    chunk_to_free->next = flist;
    flist = chunk_to_free;
}
