/*#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "my_malloc.h"

int main(int argc, char* argv[]){
  int i;
  int* tab;
  depart = current_offset + _mem_pool + POOL_SIZE;

  srand(time(NULL));
  
  for (i=0 ; i<1500 ; i++){
    tab = my_malloc(rand() % 1000);
    if (tab == NULL)
      fprintf(stderr, "Echec allocation\n");
    else
      fprintf(stderr, "Adr : %lu\n", tab);
  }
  printf("C'est fait !\n");  

  my_free(tab);
  

  return 0;
}*/


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "my_malloc.h"

#define NB_ADDR 10000
#define NB_TESTS 200000

#define MAX_ALLOC 0x100000

int main(int argc, char *argv[]) {
    int i, j, t, s, st;
    char *tab[NB_ADDR] = {0};

    srand(time(NULL));

    /* allocation et désallocation random */
    for (i = 0; i < NB_TESTS; i++) {
        j = rand() % NB_ADDR;
        if (tab[j]) {
            my_free(tab[j]);
            fprintf(stderr, "Libération: %p\n", tab[j]);
            tab[j] = NULL;
        } else {
            t = rand() % MAX_ALLOC + 1;
            tab[j] = my_malloc(t);
            if (tab[j] == NULL)
                fprintf(stderr, "Echec allocation de %do\n", t);
            else {
                fprintf(stderr, "Allocation de %5do: %p\n", t, tab[j]);
            }
        }
    }

    /* allocation d'une zone pour y placer des 42 */
    fprintf(stderr, "Allocation d'un chunk pour y placer la réponse\n");
    for (s = 0; s < NB_ADDR && tab[s]; s++)
        ;
    assert(s < NB_ADDR);
    st = MAX_ALLOC; 
    while(st > 0) {
      tab[s] = my_malloc(st);
      if (!tab[s]) st >>= 1;
      else break;
    }
    assert(tab[s]);
    memset(tab[s], 42, st);
    fprintf(stderr, "J'ai placé %d 42\n", st);

    /* on écrit partout voir si ça plante pas */
    for (i = 0; i < NB_TESTS; i++) {
        j = rand() % NB_ADDR;
        if (j != s) {
            if (tab[j]) {
                my_free(tab[j]);
                tab[j] = NULL;
            } else {
                t = rand() % MAX_ALLOC + 1;
                tab[j] = my_malloc(t);
                if (tab[j]) {
                    memset(tab[j], 0, t);
                }
            }
        }
    }

    /* et on s'assure qu'aucun 0 n'est arrivé dans le tableau à 42 */
    assert(memchr(tab[s], 0, st) == NULL);

    printf("C'est fait !\n");

    return 0;
}



