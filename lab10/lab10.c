#include <stdio.h>
#include <stdlib.h>

struct coluna {
    struct coluna* proximaColuna;
    int elemento;
    int indiceColuna;
};
typedef struct coluna coluna;

struct linha {
    struct linha* proximaLinha;
    struct coluna* primeiraColuna;
    int numeroColunas;
    int indiceLinha;
};
typedef struct linha linha;

struct matriz {
    struct linha* primeiraLinha;
    int numeroLinhas;
};
typedef struct matriz matriz;

// Libera a memoria alocada pelo malloc
void liberaMemoria(matriz* matrizEsparsa) {
    free(matrizEsparsa);
}

// Recupera o elemento da linha e coluna desejada e retorna o mesmo; Se os indices dados correspodem a uma posicao nula, retornamos 0
int recuperaElemento(matriz* matrizEsparsa, int iLinha, int iColuna) {
    linha* linhaAtual = matrizEsparsa->primeiraLinha;
    for(int i = 0; i < matrizEsparsa->numeroLinhas; i++) {
        coluna* colunaAtual = linhaAtual->primeiraColuna;
        for(int i = 0; i < linhaAtual->numeroColunas; i++) {
            if (linhaAtual->indiceLinha == iLinha && colunaAtual->indiceColuna == iColuna) {
                return colunaAtual->elemento;
            }
            colunaAtual = colunaAtual->proximaColuna;
        }
        linhaAtual = linhaAtual->proximaLinha;
    }
    return 0;
}

// Imprime a matriz esparsa
void imprimirMatriz(matriz* matrizEsparsa) {
    linha* linhaAtual = matrizEsparsa->primeiraLinha;
    printf("M: ");
    for(int i = 0; i < matrizEsparsa->numeroLinhas; i++) {
        coluna* colunaAtual = linhaAtual->primeiraColuna;
        for(int i = 0; i < linhaAtual->numeroColunas; i++) {
            printf("(%d,%d,%d) ", linhaAtual->indiceLinha, colunaAtual->indiceColuna, colunaAtual->elemento);
            colunaAtual = colunaAtual->proximaColuna;
        }
        linhaAtual = linhaAtual->proximaLinha;
    }
    printf("\n");
    return;
}

// Atualiza o elemento da posicao desejada, colocando o numero dado na mesma
void atualizaElemento(matriz* matrizEsparsa, int iLinha, int iColuna, int numero) {
    linha* novaLinha = malloc(sizeof(linha));

    int elementoAtual = recuperaElemento(matrizEsparsa, iLinha, iColuna);

    // Se o elemento da posicao dada for 0 (não esta na matriz) e o numero dado for 0, nao devemos fazer nada
    if (elementoAtual == 0 && numero == 0) {
        return;
    } else if (!matrizEsparsa->primeiraLinha) { // Se primeiraLinha for NULL, sabemos que a matriz esta vazia atualmente, portanto a linha atual sera a primeira e unica linha, consequentemente teremos uma unica coluna na linha
        novaLinha->proximaLinha = NULL;
        novaLinha->indiceLinha = iLinha;

        coluna* novaColuna = malloc(sizeof(linha));
        novaColuna->indiceColuna = iColuna;
        novaColuna->elemento = numero;
        novaColuna->proximaColuna = NULL;
        novaLinha->primeiraColuna = novaColuna;
        novaLinha->numeroColunas = 1;

        matrizEsparsa->primeiraLinha = novaLinha;
        matrizEsparsa->numeroLinhas = 1;
        
    } else {
        linha* linhaAtual = matrizEsparsa->primeiraLinha;
        linha* linhaAnterior = NULL;
        if(linhaAtual->indiceLinha > iLinha) { // Se essa condicao for verdadeira, a linha a ser adicionada sera a primeira linha, e como é uma linha nova, temos apenas uma coluna
            novaLinha->proximaLinha = matrizEsparsa->primeiraLinha;
            novaLinha->indiceLinha = iLinha;

            coluna* novaColuna = malloc(sizeof(linha));
            novaColuna->indiceColuna = iColuna;
            novaColuna->elemento = numero;
            novaColuna->proximaColuna = NULL;
            novaLinha->primeiraColuna = novaColuna;
            novaLinha->numeroColunas = 1;
            
            matrizEsparsa->primeiraLinha = novaLinha;
            matrizEsparsa->numeroLinhas += 1;
        } else {
            for(int i = 0; i < matrizEsparsa->numeroLinhas; i++) {
                if(linhaAtual->indiceLinha == iLinha) { // Se essa condicao for verdadeira, sabemos que ja temos uma linha desse indice, assim precisamos agora encontrar a coluna desejada
                    coluna* colunaAnterior = NULL;
                    coluna* colunaAtual = linhaAtual->primeiraColuna;
                    coluna* novaColuna = malloc(sizeof(linha));
                    if(colunaAtual->indiceColuna > iColuna) { // Se essa condicao for verdadeira, sabemos que a coluna atual vai ser adicionada como a primeira coluna
                        novaColuna->indiceColuna = iColuna;
                        novaColuna->elemento = numero;
                        novaColuna->proximaColuna = linhaAtual->primeiraColuna;
                        linhaAtual->primeiraColuna = novaColuna;
                        linhaAtual->numeroColunas += 1;
                    } else {
                        for(int i = 0; i < linhaAtual->numeroColunas; i++) {
                            // Se essa condicao for verdadeira, precisamos apenas atualizar o elemento dela
                            if(colunaAtual->indiceColuna == iColuna) {
                                // se o novo numero é 0, devemos excluir a coluna da linha, ja que queremos apenas elementos não nulos
                                if (numero == 0) {
                                    if (colunaAnterior == NULL)
                                    {
                                        linhaAtual->primeiraColuna = colunaAtual->proximaColuna;
                                        linhaAtual->numeroColunas -= 1;
                                        free(colunaAtual);
                                    } else if (colunaAtual->proximaColuna == NULL) {
                                        colunaAnterior->proximaColuna = NULL;
                                        linhaAtual->numeroColunas -= 1;
                                        free(colunaAtual);
                                    } else {
                                        colunaAnterior->proximaColuna = colunaAtual->proximaColuna;
                                        linhaAtual->numeroColunas -= 1;
                                        free(colunaAtual);
                                    }
                                    
                                    // Se o numero de colunas da linha for 0, devemos remover a linha
                                    if (linhaAtual->numeroColunas == 0) {
                                        if (linhaAnterior == NULL) {
                                            matrizEsparsa->primeiraLinha = linhaAtual->proximaLinha;
                                            matrizEsparsa->numeroLinhas -= 1;
                                            free(linhaAtual);
                                        } else if (linhaAtual->proximaLinha == NULL) {
                                            linhaAnterior->proximaLinha = NULL;
                                            matrizEsparsa->numeroLinhas -= 1;
                                            free(linhaAtual);
                                        } else {
                                            linhaAnterior->proximaLinha = linhaAtual->proximaLinha;
                                            matrizEsparsa->numeroLinhas -= 1;
                                            free(linhaAtual);
                                        }
                                    }

                                    // Se o numero de linhas for 0, a matriz esta vazia
                                    if (matrizEsparsa->numeroLinhas == 0)
                                    {
                                        matrizEsparsa = NULL;
                                        liberaMemoria(matrizEsparsa);
                                    }
                                    
                                } else {
                                    colunaAtual->elemento = numero;
                                }
                                break;
                            } else {
                                // Se essa condicao for verdadeira, a coluna atual sera a ultima coluna
                                if (colunaAtual->proximaColuna == NULL) {
                                    novaColuna->indiceColuna = iColuna;
                                    novaColuna->elemento = numero;
                                    novaColuna->proximaColuna = NULL;
                                    colunaAtual->proximaColuna = novaColuna;
                                    linhaAtual->numeroColunas += 1;
                                    break;
                                } else if (colunaAtual->proximaColuna->indiceColuna > iColuna) { // Se essa condicao for verdadeira, a coluna atual esta entre duas colunas
                                    novaColuna->indiceColuna = iColuna;
                                    novaColuna->elemento = numero;
                                    novaColuna->proximaColuna = colunaAtual->proximaColuna;
                                    colunaAtual->proximaColuna = novaColuna;
                                    linhaAtual->numeroColunas += 1;
                                    break;
                                }
                            }
                            colunaAnterior = colunaAtual;
                            colunaAtual = colunaAtual->proximaColuna;
                        }
                    }
                    break;
                } else {
                    // Se essa condicao for verdadeira, a linha atual sera a ultima linha
                    if (linhaAtual->proximaLinha == NULL) {
                        novaLinha->proximaLinha = NULL;
                        novaLinha->indiceLinha = iLinha;

                        coluna* novaColuna = malloc(sizeof(linha));
                        novaColuna->indiceColuna = iColuna;
                        novaColuna->elemento = numero;
                        novaColuna->proximaColuna = NULL;
                        novaLinha->primeiraColuna = novaColuna;
                        novaLinha->numeroColunas = 1;

                        linhaAtual->proximaLinha = novaLinha;
                        matrizEsparsa->numeroLinhas += 1;
                        break;
                    } else if (linhaAtual->proximaLinha->indiceLinha > iLinha) { // Se essa condicao for verdadeira, a linha atual esta entre duas linhas
                        
                        novaLinha->proximaLinha = linhaAtual->proximaLinha;
                        novaLinha->indiceLinha = iLinha;

                        coluna* novaColuna = malloc(sizeof(linha));
                        novaColuna->indiceColuna = iColuna;
                        novaColuna->elemento = numero;
                        novaColuna->proximaColuna = NULL;
                        novaLinha->primeiraColuna = novaColuna;
                        novaLinha->numeroColunas = 1;

                        linhaAtual->proximaLinha = novaLinha;
                        matrizEsparsa->numeroLinhas += 1;
                        break;
                    }
                }
                linhaAnterior = linhaAtual;
                linhaAtual = linhaAtual->proximaLinha;
            }
        }
    }
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
            matrizEsparsa->numeroLinhas = 0;

        } else if (operacao == 'a') {
            int indiceLinha, indiceColuna, numero;
            scanf(" [%d,%d] %d", &indiceLinha, &indiceColuna, &numero);
            atualizaElemento(matrizEsparsa, indiceLinha, indiceColuna, numero);

        } else if (operacao == 'p') {
            if (matrizEsparsa->numeroLinhas != 0) {
                imprimirMatriz(matrizEsparsa);
            } else {
                printf("A matriz e' nula.\n");
            }
        } else if (operacao == 'r') {
            int indiceLinha, indiceColuna, elemento;
            scanf(" [%d,%d]", &indiceLinha, &indiceColuna);
            elemento = recuperaElemento(matrizEsparsa, indiceLinha, indiceColuna);
            printf("M[%d][%d] == %d\n", indiceLinha, indiceColuna, elemento);
        } else if (operacao == 't') {
            executaLoop = 0;
        }
    }

    if (matrizEsparsa)
        liberaMemoria(matrizEsparsa);
}