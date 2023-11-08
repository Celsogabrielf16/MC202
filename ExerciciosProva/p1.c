#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int elemento;
    struct node* proximo;
    struct stuff* data;
} node;

typedef struct list {
    node* head;
} list;

void func(list* cabecaA, int k, int offset) {
    
}

node* adicionaNaListaEncadeada(node* cabeca, int elemento) {
    node* proximo = cabeca;
    node* atual = malloc(sizeof(node));
    atual->elemento = elemento;
    atual->proximo = proximo;
    return atual;
}

void zuadorDeLista(node* cabeca) {
    node* atual = cabeca;
    while(1) {
        if (atual->proximo == NULL) {
            atual->proximo = cabeca->proximo->proximo;
            printf("--: %d\n", atual->elemento);
            printf("--++: %p\n", atual->proximo);
            break;
        }
        atual = atual->proximo;
    }
    printf("\n");
}

void imprimeLista(node* cabeca) {
    node* atual = cabeca;
    while(1) {
        if (atual->proximo != NULL) {
            printf("--: %d\n", atual->elemento);
            printf("--++: %p\n", atual->proximo);
        } else {
            printf("--: %d\n", atual->elemento);
            printf("--++: %p\n", atual->proximo);
            break;
        }
        atual = atual->proximo;
    }
    printf("\n");
}

node* removeDaLista(node* cabeca, int elemento) {
    int tirarCabeca = 0;
    if(cabeca->elemento == elemento) {
        tirarCabeca = 1;
    }

    node* atual = cabeca->proximo;
	node* anterior = cabeca;
    
	while(atual != NULL){

        if(atual->elemento == elemento){
        	anterior->proximo = atual->proximo;
        	free(atual);
        	atual = anterior->proximo;
       	 
    	} else{
        	anterior = atual;
        	atual = atual->proximo;
    	}
	}

    if (tirarCabeca) {
        node* novaCabeca = cabeca->proximo;
        free(cabeca);
        return novaCabeca;
    } else {
        return cabeca;
    }
}

int retornaMinimo(node* cabeca) {
    int menorNumero = cabeca->elemento;
    node* atual = cabeca;
    while(1) {
        if (atual->proximo != NULL) {
            if(atual->elemento < menorNumero) {
                menorNumero = atual->elemento;
            }
        } else {
            if(atual->elemento < menorNumero) {
                menorNumero = atual->elemento;
            }
            break;
        }
        atual = atual->proximo;
    }
    return menorNumero;
}

int main(void) {
    node* lista = NULL;

    lista = adicionaNaListaEncadeada(lista, 10);
    lista = adicionaNaListaEncadeada(lista, 20);
    lista = adicionaNaListaEncadeada(lista, 30);
    lista = adicionaNaListaEncadeada(lista, 20);
    lista = adicionaNaListaEncadeada(lista, 40);
    lista = adicionaNaListaEncadeada(lista, 20);
    lista = adicionaNaListaEncadeada(lista, 2);

    /* imprimeLista(lista);

    printf("minimo: %d\n\n", retornaMinimo(lista));

    lista = removeDaLista(lista, retornaMinimo(lista)); */

    /* imprimeLista(lista);

    zuadorDeLista(lista); */

    imprimeLista(lista);

    return 0;
}
