#ifndef _abb_h_
#define _abb_h_

typedef struct arvore {  
    int info;
    struct arvore *esq;
    struct arvore *dir;
} Arvore;

Arvore* cria_arvore_vazia (void);
Arvore* inserir (Arvore *a, int v);
Arvore* remover (Arvore *a, int v);
int buscar (Arvore *a, int v);
void pre_order (Arvore* a);
int min (Arvore *a);
int max (Arvore *a);
void arvore_libera (Arvore* a);

#endif
