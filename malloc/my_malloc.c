
#include <stdio.h>
#include "my_malloc.h"

/* static pool of memory */

void* my_malloc(size_t size){
    _Segment* s = (_Segment*)(_mem_pool + current_offset);

    if ((POOL_SIZE < current_offset + size) || s->boolfree == 1)
      return NULL;

    s->prev = *_mem_pool - current_offset;
    s->next = *_mem_pool + current_offset;
    s->boolfree = 0;
    current_offset += size;
    return s;
}

void my_free(void* pouet){
  if (pouet != NULL){
    _Segment* s = (_Segment*) pouet;
    s->boolfree = 1;
  }
  
}
