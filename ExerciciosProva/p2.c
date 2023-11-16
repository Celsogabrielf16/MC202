#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no* direita;
    struct no* esquerda;
} no;

no* insereNaArvore(no* noRaiz, int valor) {
    if (noRaiz == NULL) {
        no* novoNo = malloc(sizeof(no));
        if (novoNo == NULL)
            return NULL;
        novoNo->valor = valor;
        novoNo->direita = NULL;
        novoNo->esquerda = NULL;
        return novoNo;
    } else {
        if (noRaiz->valor > valor) {
            noRaiz->esquerda = insereNaArvore(noRaiz->esquerda, valor);
        } else if (noRaiz->valor < valor) {
            noRaiz->direita = insereNaArvore(noRaiz->direita, valor);
        }
        return noRaiz;
    }
}

no* buscaValor(no* noRaiz, int valor) {
    if (noRaiz) {
        if(noRaiz->valor == valor){
            return noRaiz;
        } else if (noRaiz->valor > valor) {
            return buscaValor(noRaiz->esquerda, valor);
        } else {
            return buscaValor(noRaiz->direita, valor);
        }
        
    }
    return NULL;
}

int altura(no* noRaiz) {
    if (noRaiz == NULL) {
        return -1;
    } else {
        int esq = altura(noRaiz->esquerda);
        int dir = altura(noRaiz->direita);
        if(esq > dir) {
            return esq + 1;
        } else {
            return dir + 1;
        }
    }
}

int descendente(no* raiz, int valor) {
    if (raiz == NULL) {
        return 0;
    } else {
        if (raiz->valor == valor) {
            return 0;
        } else if (raiz->valor > valor) {
            return descendente(raiz->esquerda, valor) + 1;
        } else {
            return descendente(raiz->direita, valor) + 1;
        }
    }
}

void emOrdem(no* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        int soma = 0;
        if (raiz->esquerda != NULL)
            soma += raiz->esquerda->valor;
        if (raiz->direita != NULL)
            soma += raiz->direita->valor;
        raiz->valor += soma;
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

int quantidadeNosArvore(no* noRaiz) {
    if (noRaiz != NULL) {
        int quantEsq = quantidadeNosArvore(noRaiz->esquerda);
        int quantDir = quantidadeNosArvore(noRaiz->direita);
        return quantEsq + quantDir + 1;
    }
    return 0;
}

int quantidadeFolhas(no* noRaiz) {
    if (noRaiz != NULL) {
        if (noRaiz->esquerda != NULL || noRaiz->direita != NULL) {
            return quantidadeFolhas(noRaiz->esquerda) + quantidadeFolhas(noRaiz->direita);
        } else {
            return 1;
        }
    }
    return 0;
}

void imprimeArvore(no* noRaiz) {
    if (noRaiz != NULL) {
        imprimeArvore(noRaiz->esquerda);
        printf("%d ", noRaiz->valor);
        imprimeArvore(noRaiz->direita);
    }
}

no* removeNoDaArvore(no* noRaiz, int valor) {
    if (noRaiz != NULL) {
        if (noRaiz->valor == valor) {
            if (noRaiz->esquerda == NULL && noRaiz->direita == NULL) {
                free(noRaiz);
                return NULL;
            } else if (noRaiz->esquerda != NULL && noRaiz->direita != NULL) {
                no* noAux = noRaiz->esquerda;
                while(noAux->direita != NULL)
                    noAux = noAux->direita;
                noRaiz->valor = noAux->valor;
                noAux->valor = valor;
                noRaiz->esquerda = removeNoDaArvore(noRaiz->esquerda, valor);
                return noRaiz;
            } else {
                no* noAux;
                if (noRaiz->esquerda != NULL) {
                    noAux = noRaiz->esquerda;
                } else {
                    noAux = noRaiz->direita;
                }
                free(noRaiz);
                return noAux;
            }
        } else {
            if (noRaiz->valor > valor) {
                noRaiz->esquerda = removeNoDaArvore(noRaiz->esquerda, valor);
            } else {
                noRaiz->direita = removeNoDaArvore(noRaiz->direita, valor);
            }
            return noRaiz;
        }
    }
    return NULL;
}

int main(void) {
    no* raiz = NULL;

    raiz = insereNaArvore(raiz, 17);
    raiz = insereNaArvore(raiz, 26);
    raiz = insereNaArvore(raiz, 25);
    raiz = insereNaArvore(raiz, 8);
    raiz = insereNaArvore(raiz, 1);
    raiz = insereNaArvore(raiz, 32);
    raiz = insereNaArvore(raiz, 55);
    raiz = insereNaArvore(raiz, 48);
    raiz = insereNaArvore(raiz, 36);

    /* imprimeArvore(raiz); */

    /* if (buscaValor(raiz, 100)) {
        printf("Encontrou valor\n");
    } else {
        printf("Nao encontrou valor\n");
    }

    printf("Altura arvore: %d\n", altura(raiz));

    printf("Quantidade nos na arvore: %d\n", quantidadeNosArvore(raiz));

    printf("Quantidade de folhas na arvore: %d\n", quantidadeFolhas(raiz));

    raiz = removeNoDaArvore(raiz, 25);

    imprimeArvore(raiz);
    printf("\n");

    printf("Quantidade de descendentes: %d\n", descendente(raiz, 37)); */

    emOrdem(raiz);
    printf("\n");

    return 0;
}