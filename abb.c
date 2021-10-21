#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

int main () {
int i;
Arvore *a = cria_arvore_vazia ();
//inserir 
   //.....  
printf("\n");
pre_order (a);	
printf("\n");
// ====== Q3 ====
return 0;
}

Arvore* cria_arvore_vazia (void) {
return NULL;
}

void arvore_libera (Arvore* a) {
    if (a != NULL) {
        arvore_libera (a->esq);
        arvore_libera (a->dir);
        free(a);
    }
}
//========= Q1 - inserir
Arvore* inserir (Arvore *a, int v) {
   /* Completar */
    return a;
}
//========= Q1 - remover
Arvore* remover (Arvore *a, int v) {
   /* Completar */

return a;
}
//========= Q1 - busca
int buscar (Arvore *a, int v) {
   /* Completar */

return 1; 
}
//========= Q2 - min =====
//========= Q2 - max =====
//========= Q4 - imprime_decrescent =====
void pre_order (Arvore* a) {
    if (a != NULL) {
        printf("%d ", a->info);
        pre_order (a->esq);
        pre_order (a->dir);
    } 
}