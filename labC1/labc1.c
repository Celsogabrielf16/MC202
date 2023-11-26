#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct par {
    int chave;
    int custo;
} par;

// Aloca um heap do tamanho dado
par* criaHeap(int numeroPares) {
    par* novoHeap = malloc(2 * numeroPares * sizeof(par));
    if (!novoHeap)
        return NULL;
    return novoHeap;
}

// Aloca um vetor para usarmos como indexador das chaves do heap
int* criaVetor(int numeroPares) {
    int* novoVetor = malloc(numeroPares * sizeof(int));
    if (!novoVetor)
        return NULL;
    for (int i = 0; i < numeroPares; i++) 
        novoVetor[i] = -1;
    return novoVetor;
}

void liberaHeap(par* heap) {
    free(heap);
    return;
}

void liberaVetor(int* vetor) {
    free(vetor);
    return;
}

// Insere o par {chave,custo} no heap
void insereNoHeap(par* heap, int* vetorIndexacao, int tamanhoHeap, int chave, int custo) {
    // Coloca o par dado na ultima posicao do heap e atualiza o vetor de indexacao
    heap[tamanhoHeap].chave = chave;
    heap[tamanhoHeap].custo = custo;
    vetorIndexacao[chave] = tamanhoHeap;

    par auxiliar;
    int indiceAtual = tamanhoHeap;
    int indicePai = floor((indiceAtual - 1) / 2);

    // Enquanto o pai tiver custo maior que o do par adicionado trocamos eles de lugar
    while (indiceAtual > 0 && ((heap[indiceAtual].custo < heap[indicePai].custo) ||  (heap[indiceAtual].custo == heap[indicePai].custo && heap[indiceAtual].chave < heap[indicePai].chave))) {
        vetorIndexacao[heap[indicePai].chave] = indiceAtual;
        vetorIndexacao[chave] = indicePai;
        auxiliar = heap[indiceAtual];
        heap[indiceAtual] = heap[indicePai];
        heap[indicePai] = auxiliar;

        indiceAtual = indicePai;
        indicePai = floor((indiceAtual - 1) / 2);
    }
    return;
}

// Como acabamos de remover a raiz e colocar o ultimo par na mesma, provavelmente o heap nao esta com a hierarquia correta entao devemos corrigir isso pra continuarmos com um heap de minimo
void verificaPrioridadeHeapRaizParaFolha(par* heap, int* vetorIndexacao, int tamanhoHeap, int numeroPares) {
    par auxiliar;
    int indiceFilhoTroca, indiceAtual = 0;
    int indiceFilhoEsquerda;
    int indiceFilhoDireita;

    while (indiceAtual < numeroPares) {
        indiceFilhoEsquerda = 2 * indiceAtual + 1;
        indiceFilhoDireita = 2 * indiceAtual + 2;
        // Primeiramente precisamos saber se o par atual tem filhos
        if (indiceFilhoEsquerda < tamanhoHeap && indiceFilhoDireita < tamanhoHeap) {
            // Caso tenha os dois filhos escolhemos o filho de menor custo
            if (heap[indiceFilhoEsquerda].custo < heap[indiceFilhoDireita].custo) {
                indiceFilhoTroca = indiceFilhoEsquerda;
            } else {
                indiceFilhoTroca = indiceFilhoDireita;
            }
        } else if (indiceFilhoEsquerda < tamanhoHeap) {
            indiceFilhoTroca = indiceFilhoEsquerda;
        } else if (indiceFilhoDireita < tamanhoHeap) {
            indiceFilhoTroca = indiceFilhoDireita;
        }

        // Se o indiceFilhoTroca for igual a -1 nosso par nao tem filhos, mas caso tenha e esse filho tenha um custo menor que o do par atual trocamos eles de lugar 
        if (indiceFilhoTroca != -1 && heap[indiceFilhoTroca].custo < heap[indiceAtual].custo) {
            vetorIndexacao[heap[indiceAtual].chave] = indiceFilhoTroca;
            vetorIndexacao[heap[indiceFilhoTroca].chave] = indiceAtual;
            auxiliar = heap[indiceAtual];
            heap[indiceAtual] = heap[indiceFilhoTroca];
            heap[indiceFilhoTroca] = auxiliar;

            indiceAtual = indiceFilhoTroca;
            indiceFilhoTroca = -1;
        } else {
            break;
        }
    }
    return;
}

// Usamos essa funcao para verificar se nao quebremaos a hierarquia do heap minimo quando diminuimos o custo de alguma chave do mesmo
void verificaPrioridadeHeapFolhaParaRaiz(par* heap, int* vetorIndexacao, int indice) {
    par auxiliar;
    int indiceAtual = indice;
    int indicePai = floor((indiceAtual - 1) / 2);

    // Como o custo diminuiu precisamos apenas verificar se o pai do par atual tem custo maior, caso tenha, trocamos eles de lugar e repetimos ate que o par atualizado esteja no lugar certo
    while (indiceAtual > 0 && heap[indiceAtual].custo < heap[indicePai].custo) {
        vetorIndexacao[heap[indicePai].chave] = indiceAtual;
        vetorIndexacao[heap[indiceAtual].chave] = indicePai;
        auxiliar = heap[indiceAtual];
        heap[indiceAtual] = heap[indicePai];
        heap[indicePai] = auxiliar;

        indiceAtual = indicePai;
        indicePai = floor((indiceAtual - 1) / 2);
    }

    return;
}

int main(void) {
    char operacao;
    int numeroPares, tamanhoHeap = 0;
    par* heap = NULL;
    int* vetorIndexacao = NULL;
    while(scanf("%c", &operacao) == 1) {
        if (operacao == 'c') {
            scanf(" %d", &numeroPares);

            // Se ja existir um heap na memoria devemos libera-la antes de criar um novo heap
            if (heap) {
                liberaHeap(heap);
                liberaVetor(vetorIndexacao);
            }

            heap = criaHeap(numeroPares);
            vetorIndexacao = criaVetor(numeroPares + 1);
            tamanhoHeap = 0;
        } else if (operacao == 'i') {
            int chave;
            int custo;
            scanf(" %d %d", &chave, &custo);

            // Caso a chave dada nao esteja no heap, adicionamos o par no mesmo
            if (vetorIndexacao[chave] == -1) {
                insereNoHeap(heap, vetorIndexacao, tamanhoHeap, chave, custo);
                tamanhoHeap += 1;
            }
        } else if (operacao == 'm') {
            if (tamanhoHeap) {
                int chaveInicial = heap[0].chave;
                int custoInicial = heap[0].custo;

                // Copiamos o ultimo par do heap para a raiz e atualizamos o vetorIndexacao e o tamanho do heap, pois removemos um par
                heap[0] = heap[tamanhoHeap - 1];
                vetorIndexacao[heap[0].chave] = 0;
                vetorIndexacao[chaveInicial] = -1;
                tamanhoHeap -= 1;

                verificaPrioridadeHeapRaizParaFolha(heap, vetorIndexacao, tamanhoHeap, numeroPares);

                printf("minimo {%d,%d}\n", chaveInicial, custoInicial);
            } else {
                printf("heap vazio\n");
            }
        } else if (operacao == 'd') {
            int chave;
            int custo;
            scanf(" %d %d", &chave, &custo);

            // Atualizamos o valor do custo da chave dada
            heap[vetorIndexacao[chave]].custo = custo;

            verificaPrioridadeHeapFolhaParaRaiz(heap, vetorIndexacao, vetorIndexacao[chave]);
        } else if (operacao == 't') {
            liberaHeap(heap);
            liberaVetor(vetorIndexacao);
            break;
        }
    }
    return 0;
}