#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abb.h"

int main () {

Arvore *a = cria_arvore_vazia ();

a = inserir (a, 50);
a = inserir (a, 30);
a = inserir (a, 90);
a = inserir (a, 20);
a = inserir (a, 40);
a = inserir (a, 95);
a = inserir (a, 10);
a = inserir (a, 35);
a = inserir (a, 45);

printf("\n");
printf("Percurso Pre-Ordem (arvore original): ");
pre_order (a);	
printf("\nElementos em ordem decrescente:       ");
imprime_decrescente(a);
printf("\nElemento MIN: %d", min(a));
printf("\nElemento MAX: %d", max(a));
printf("\nSoma dos elementos do maior ramo: %d", maior_ramo(a));
	
printf("\n\n");

int stop = 0, opcao, elem;
while (!stop) {
    do {
    printf("Digite (1) para inserir um elemento na arvore\n");
    printf("Digite (2) para remover um elemento da arvore\n\n");
    printf(">>> ");

    scanf("%d", &opcao);

    switch(opcao) {
        case 1: printf("Elemento a ser inserido: ");
                scanf("%d", &elem);
                inserir (a, elem);
                break;
        case 2: printf("Elemento a ser removido: ");
                scanf("%d", &elem);
                remover (a, elem);
                break;
        default:printf("\nInsira uma opcao valida!\a\n\n");
                break;
    }

    }while (opcao != 1 && opcao != 2);

    printf("\n");
    printf("Percurso Pre-Ordem (nova arvore): ");
    pre_order (a);	
    printf("\nElementos em ordem decrescente: ");
    imprime_decrescente(a);
    printf("\nElemento MIN: %d", min(a));
    printf("\nElemento MAX: %d", max(a));
    printf("\nSoma dos elementos do maior ramo: %d", maior_ramo(a));
    
    printf("\n\n");

    printf("Deseja parar? \n(1) SIM \n(0) NAO");
    printf("\n\n>>> ");
    scanf("%d", &stop);
}

arvore_libera(a);

Arvore *a2 = cria_arvore_vazia ();

clock_t start, end;
double elapsed_time;
srand(time(NULL));

start = clock();
for (int i = 0; i < MAX; i++) {a2 = inserir(a2, i);}

buscar (a2, MAX);
end = clock();
elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;

printf("\nTempo de busca (insercao crescente / arvore degenerada): %.2fs\n", elapsed_time);

arvore_libera(a2);

Arvore *a3 = cria_arvore_vazia ();

start = clock();
for (int i = 0; i < MAX; i++) {
    int random_elem = rand() % 100000;
    a3 = inserir(a3, random_elem);
}

buscar (a3, MAX);
end = clock();
elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;

printf("Tempo de busca (insercao aleatoria / arvore nao degenerada): %.2fs\n\n", elapsed_time);

arvore_libera(a3);

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

void inverte_nos (Arvore *a, Arvore *tmp, int v) {
    a->info = tmp->info;
    tmp->info = v;
}

Arvore* inserir (Arvore *a, int v) {
    if(a == NULL) {
        a = (Arvore*) malloc (sizeof(Arvore));
        a->info = v;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if (v < a->info) {a->esq = inserir (a->esq, v);}
    else {a->dir = inserir (a->dir, v);}

    return a;
}

Arvore* remover (Arvore *a, int v) {
    if(a == NULL) {return NULL;}
    else {
        if (v < a->info) {a->esq = remover (a->esq, v);}
        else if (v > a->info) {a->dir = remover (a->dir, v);}
        else {
            //Folha (não tem filhos / grau 0)
            if((a->esq == NULL) && (a->dir == NULL)) {
            free (a);
            a = NULL;
            }
            //Filho / Nó p/ esquerda (grau 1)
            else if (a->dir == NULL) {
                Arvore *tmp = a; //ponteiro "tmp" aponta p/ nó atual
                a = a->esq; //ponteiro "a" se liga com o nó / filho da esq
                free(tmp); //liberamos / removemos o elem de "tmp"
            } 
            //Filho / Nó p/ direita (grau 1)
            else if (a->esq == NULL) {
                Arvore *tmp = a; 
                a = a->dir;
                free(tmp);
            }
            //Dois filhos / Nó p/ esquerda e p/ direita (grau 2)
            else {
                //Procurando o maior nó da subárvore da esquerda p/ promover
                //à raiz (poderia ser da direita), reestruturando a árvore:
                Arvore *tmp = a->esq;
                while (tmp->dir != NULL) {tmp = tmp->dir;}
                //Função para inverter o valor da raiz com o da folha
                inverte_nos(a, tmp, v);
                a->esq = remover (a->esq, v); //removemos o nó
            }
        }
    }
return a;
}

int buscar (Arvore *a, int v) {
    if (a == NULL) {return 0;}
    else if (v < a->info) {return buscar(a->esq, v);}
    else if (v > a->info) {return buscar(a->dir, v);}
    else {return 0;}
}

int min (Arvore *a){
    int min_elem;

    if (a == NULL) {return -1;}
    else if (a->esq != NULL) {min_elem = min(a->esq);}
    else {min_elem = a->info;}

    return min_elem;
}

int max(Arvore *a) {
    int max_elem;

    if (a == NULL) {return -1;} 
    else if(a->dir != NULL) {max_elem = max(a->dir);}
    else {max_elem = a->info;}

    return max_elem;
}

void imprime_decrescente (Arvore* a) {
    //Percurso In-ordem invertido
    if(a == NULL) {return;}

    imprime_decrescente(a->dir);
    printf("%d ", a->info);
    imprime_decrescente(a->esq);
}

int maior_ramo (Arvore *a){

    if(a == NULL) {return 0;}

    int s_esq = maior_ramo(a->esq) + a->info;
    int s_dir = maior_ramo(a->dir) + a->info;

    if(s_esq > s_dir) {return s_esq;}
    else  {return s_dir;}
}

void pre_order (Arvore* a) {
    if (a != NULL) {
        printf("%d ", a->info);
        pre_order (a->esq);
        pre_order (a->dir);
    } 
}