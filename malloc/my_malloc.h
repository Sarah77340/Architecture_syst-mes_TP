#ifndef __MY_MALLOC_
#define __MY_MALLOC_

void* my_malloc(size_t size);
void my_free(void* pouet);

#endif

#include <stdio.h>

/*#define POOL_SIZE 30*/
#define POOL_SIZE 1000000000 /*1 giga*/
static char _mem_pool[POOL_SIZE]; /* static pool of memory*/
long int current_offset;
long int depart;

typedef struct _segment{
    int prev; /* saut à faire pour attrapper le segment précédent*/
    int next; /* saut à faire pour aller au segment suivant*/
    int boolfree; /*dit si le segment est libre ou pas*/
    char data; /* &(s->data) sera l'adresse de la zone à retourner...*/ 
}_Segment;
