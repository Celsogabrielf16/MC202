#include <stdio.h>
#include <stdlib.h>

/* struct coluna {
    struct coluna* proximaColuna;
    int indiceColuna;
    int valorElemento;
}; 
typedef struct coluna coluna;*/

struct matriz {
    struct linha* primeiraLinha;
    int numeroDeLinhas;
};

typedef struct matriz matriz;

struct linha {
    struct linha* proximaLinha;
    int indiceLinha;
};

typedef struct linha linha;

void liberaMemoria(matriz* matrizEsparsa) {
    printf("Criou\n");
    free(matrizEsparsa);
}

void atualizaElemento(matriz* matrizEsparsa, int iLinha, int iColuna, int numero) {
    linha* novaLinha = malloc(sizeof(linha));

    novaLinha->indiceLinha = iLinha;
    matrizEsparsa->numeroDeLinhas++;

    if (iLinha == 0) {
        novaLinha->proximaLinha = matrizEsparsa->primeiraLinha;
        matrizEsparsa->primeiraLinha = novaLinha;
    } else {
        linha* linhaAtual = matrizEsparsa->primeiraLinha;

        int indiceLinhaAtual = matrizEsparsa->primeiraLinha->indiceLinha;
        while(indiceLinhaAtual != iLinha) {
            printf("aaaaaaaaaaaaaaaaaaaaaaaaa -- %d\n", indiceLinhaAtual);
            indiceLinhaAtual++;
        } 
    }




    /* if (matrizEsparsa->primeiraLinha == NULL) {
        matrizEsparsa->primeiraLinha = malloc(sizeof(linha));

        if (!matrizEsparsa->primeiraLinha)
            printf("Deu ruim!");

        matrizEsparsa->primeiraLinha->proximaLinha = NULL;
        matrizEsparsa->primeiraLinha->numeroDeColunas = 1;
        matrizEsparsa->primeiraLinha->indiceLinha = iLinha;
        matrizEsparsa->primeiraLinha->primeiraColuna = malloc(sizeof(coluna));

        if (!matrizEsparsa->primeiraLinha->primeiraColuna)
            printf("Deu ruim!");

        matrizEsparsa->primeiraLinha->primeiraColuna->proximaColuna = NULL;
        matrizEsparsa->primeiraLinha->primeiraColuna->indiceColuna = iColuna;
        matrizEsparsa->primeiraLinha->primeiraColuna->valorElemento = numero;
    } */

    return;
}

int main(void) {
    char operacao;
    int executaLoop = 1;
    matriz* matrizEsparsa = NULL;

    while (executaLoop) {
        scanf("%c", &operacao);

        if (operacao == 'c') {
            if (matrizEsparsa)
                liberaMemoria(matrizEsparsa);

            matrizEsparsa = malloc(sizeof(matriz));
            if (!matrizEsparsa)
                printf("Deu ruim!");

            matrizEsparsa->primeiraLinha = NULL;
            matrizEsparsa->numeroDeLinhas = 0;

        } else if (operacao == 'a') {
            int indiceLinha, indiceColuna, numero;
            scanf(" [%d,%d] %d", &indiceLinha, &indiceColuna, &numero);
            atualizaElemento(matrizEsparsa, indiceLinha, indiceColuna, numero);

        } if (operacao == 't') {
            executaLoop = 0;
        }
    }

    if (matrizEsparsa)
        liberaMemoria(matrizEsparsa);
}