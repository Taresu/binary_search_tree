#ifndef _abb_h_
#define _abb_h_

#define MAX 32000

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
void imprime_decrescente (Arvore* a);
int total_sum (Arvore* a);
int maior_ramo (Arvore* a);
int min (Arvore *a);
int max (Arvore *a);
Arvore* ancestral (Arvore* a, int e1, int e2);
void arvore_libera (Arvore* a);

#endif
