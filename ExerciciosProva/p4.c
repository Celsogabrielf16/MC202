#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct heap {
    int* vetor;
    unsigned tamanhoVetor;
    unsigned tamanhoHeap;
} heap;

void aumentaValorChave(heap* heap, int indice, int novaChave) {
    heap->vetor[indice] = novaChave;
    int indicePai = floor((indice - 1) / 2);

    while (indice > 0 && heap->vetor[indicePai] < heap->vetor[indice]) {
        int aux = heap->vetor[indicePai];
        heap->vetor[indicePai] = heap->vetor[indice];
        heap->vetor[indice] = aux;

        indice = indicePai;
        indicePai = floor((indice - 1) / 2);
    }
}

int verificaHeap(int* vetor, int tamanho, int indice) {
    int indiceFilhoEsquerda = indice * 2 + 1;
    int indiceFilhoDireita = indice * 2 + 2;

    if (indiceFilhoEsquerda < tamanho && vetor[indiceFilhoEsquerda] < vetor[indice]) {
        return verificaHeap(vetor, tamanho, indiceFilhoEsquerda);
    } else if (indiceFilhoEsquerda < tamanho && vetor[indiceFilhoEsquerda] > vetor[indice]) {
        return 0;
    }

    if (indiceFilhoDireita < tamanho && vetor[indiceFilhoDireita] < vetor[indice]) {
        return verificaHeap(vetor, tamanho, indiceFilhoDireita);
    } else if (indiceFilhoDireita < tamanho && vetor[indiceFilhoDireita] > vetor[indice]) {
        return 0;
    }

    return 1;
}

void verificaHeapPrint(int isHeap) {
    if (isHeap) {
        printf("Is Heap\n");
    } else  {
        printf("Not is Heap\n");
    }
}

void imprimeHeap(heap* heap) {
    for (unsigned i = 0; i < heap->tamanhoHeap; i++) {
        printf("%d ", heap->vetor[i]);
    }
    printf("\n");
}

int devolveTerceiroMaiorValor(heap* vetorHeap) {
    int vetor[3];

    return encontraTerceiroMaior(vetorHeap, 0, 0, vetor);
}

int encontraTerceiroMaior(heap* heap, int indice, int posicoesOcupadas, int vetor[]) {
    int indiceFilhoEsquerda = indice * 2 + 1;
    int indiceFilhoDireita = indice * 2 + 2;

    if (posicoesOcupadas == 0) {
        vetor[posicoesOcupadas] = heap->vetor[indice];
        posicoesOcupadas++;
    } else if (posicoesOcupadas < 3) {
        if (indiceFilhoEsquerda < heap->tamanhoHeap && indiceFilhoDireita < heap->tamanhoHeap) {
            if (heap->vetor[indiceFilhoEsquerda] < heap->vetor[indiceFilhoDireita]) {
                vetor[posicoesOcupadas] = heap->vetor[indiceFilhoEsquerda];
                posicoesOcupadas++;
            } else if (heap->vetor[indiceFilhoEsquerda] > heap->vetor[indiceFilhoDireita]) {
                vetor[posicoesOcupadas] = heap->vetor[indiceFilhoDireita];
                posicoesOcupadas++;
            }
        } else if (indiceFilhoEsquerda < heap->tamanhoHeap) {

        }
    }
    
    if (maximosDiferentes != 0) {
        if (indiceFilhoEsquerda < heap->tamanhoHeap) {
            if (heap->vetor[indice] != heap->vetor[indiceFilhoEsquerda]) {
                terceiroMaior = encontraTerceiroMaior(heap, indiceFilhoEsquerda, maximosDiferentes - 1);
            } else {
                terceiroMaior = encontraTerceiroMaior(heap, indiceFilhoEsquerda, maximosDiferentes);
            }
        }

        if (indiceFilhoDireita < heap->tamanhoHeap) {
            if (heap->vetor[indice] != heap->vetor[indiceFilhoDireita]) {
                terceiroMaior = encontraTerceiroMaior(heap, indiceFilhoDireita, maximosDiferentes - 1);
            } else {
                terceiroMaior = encontraTerceiroMaior(heap, indiceFilhoDireita, maximosDiferentes);
            }
        }
    }
}

int main(void) {
    heap* tipoHeap = malloc(sizeof(heap));

    if (!tipoHeap)
        printf("Deu Ruim!");

    int vetorInt[7] = {10,9,6,3,2,1,4};

    tipoHeap->vetor = vetorInt;
    tipoHeap->tamanhoVetor = 10;
    tipoHeap->tamanhoHeap = 7;

    int isHeap = verificaHeap(tipoHeap->vetor, 7, 0);

    imprimeHeap(tipoHeap);

    verificaHeapPrint(isHeap);

    aumentaValorChave(tipoHeap, 3, 12);

    imprimeHeap(tipoHeap);

    verificaHeapPrint(isHeap);

    return 0;
}