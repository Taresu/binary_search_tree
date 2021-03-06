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

printf("\n\t       | ABB - Arvore Binaria de Busca |\n");
printf("\n");
printf("Percurso Pre-Ordem (arvore original): ");
pre_order (a);	
printf("\nElementos em ordem decrescente:       ");
imprime_decrescente(a);
printf("\n\nElemento MIN: %d", min(a));
printf("\nElemento MAX: %d", max(a));
printf("\n\nSoma dos elementos do maior ramo (numericamente): %d\n\n", maior_ramo(a));

Arvore *crescent_a = cria_arvore_vazia ();

clock_t start, end;
double elapsed_time;
srand(time(NULL));

start = clock();
for (int i = 0; i < MAX; i++) {crescent_a = inserir(crescent_a, i);}

buscar (crescent_a, MAX);
end = clock();
elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;

printf("Tempo de busca (insercao crescente / arvore degenerada): %.2fs\n", elapsed_time);

arvore_libera(crescent_a);

Arvore *random_a = cria_arvore_vazia ();

start = clock();
for (int i = 0; i < MAX; i++) {
    int random_elem = rand() % 100000;
    random_a = inserir(random_a, random_elem);
}

buscar (random_a, MAX);
end = clock();
elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;

printf("Tempo de busca (insercao aleatoria / arvore nao degenerada): %.2fs\n\n", elapsed_time);

arvore_libera(random_a);

int stop = 0, opcao, elem, no1, no2;
while (!stop) {
    do {
    printf("Digite (1) para inserir um elemento na arvore\n");
    printf("Digite (2) para remover um elemento da arvore\n");
    printf("Digite (3) para encontrar o ancestral comum de menor nivel de dois nos\n\n");
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
        case 3: do {
                printf("\nNo 1: ");
                scanf("%d", &no1);
                printf("No 2: ");
                scanf("%d", &no2);
                if((buscar(a, no1) == 0) || (buscar(a, no2) == 0)){ 
                    printf("\nDigite dois nos existentes na arvore!\a\n\n");
                }
                }while ((buscar(a, no1) == 0) || (buscar(a, no2) == 0));
                Arvore *t = ancestral(a, no1, no2);
                printf("O ancestral comum de menor nivel dos nos %d e %d eh %d", no1, no2, t->info);
                break;
        default:printf("\nInsira uma opcao valida!\a\n\n");
                break;
    }
    }while (opcao != 1 && opcao != 2 && opcao != 3);

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
            //Folha (n??o tem filhos / grau 0)
            if((a->esq == NULL) && (a->dir == NULL)) {
            free (a);
            a = NULL;
            }
            //Filho / N?? p/ esquerda (grau 1)
            else if (a->dir == NULL) {
                Arvore *tmp = a; //ponteiro "tmp" aponta p/ n?? atual
                a = a->esq; //ponteiro "a" se liga com o n?? / filho da esq
                free(tmp); //liberamos / removemos o elem de "tmp"
            } 
            //Filho / N?? p/ direita (grau 1)
            else if (a->esq == NULL) {
                Arvore *tmp = a; 
                a = a->dir;
                free(tmp);
            }
            //Dois filhos / N?? p/ esquerda e p/ direita (grau 2)
            else {
                //Procurando o maior n?? da sub??rvore da esquerda p/ promover
                //?? raiz (poderia ser da direita), reestruturando a ??rvore:
                Arvore *tmp = a->esq;
                while (tmp->dir != NULL) {tmp = tmp->dir;}
                //Fun????o para inverter o valor da raiz com o da folha
                inverte_nos(a, tmp, v);
                a->esq = remover (a->esq, v); //removemos o n??
            }
        }
    }
return a;
}

int buscar (Arvore *a, int v) {
    if (a == NULL) {return 0;}
    else if (v < a->info) {return buscar(a->esq, v);}
    else if (v > a->info) {return buscar(a->dir, v);}
    else {return 1;}
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

Arvore* ancestral (Arvore* a, int e1, int e2) {
    if(a == NULL) {return NULL;} //??rvore vazia, sem n??s

    else {
        if(a->info > e1 && a->info > e2) {return ancestral (a->esq, e1, e2);}
        
        if(a->info < e1 && a->info < e2) {return ancestral (a->dir, e1, e2);}

        return a;
    }
}

