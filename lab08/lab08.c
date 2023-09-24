#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Push é uma operacao da pilha que adiciona um numero no fim da mesma
int push(int* vetor, int numero, int posicaoFinal) {
    posicaoFinal++;
    vetor[posicaoFinal] = numero;
    return posicaoFinal;
}

// Pop é uma operacao da pilha que remove um numero do fim da mesma
int pop(int* vetor, int posicaoFinal) {
    vetor[posicaoFinal] = 0;
    return --posicaoFinal;
}

// Last é uma operacao da pilha que devolve o numero do final da mesma
int last(int* vetor, int posicaoFinal) {
    int numero = vetor[posicaoFinal];
    return numero;
}

int main(void) {
    int tamanhoSequencia;

    do {
        scanf("%d", &tamanhoSequencia);

        // Se recebemos o numero 0 o programa acaba
        if (tamanhoSequencia == 0) {
            break;
        }

        // Sera usada para verificar se as bonecas estao fechadas corretamente
        int pilhaBonecas[tamanhoSequencia];
        int indiceFinalPilhaBonecas = -1;
        // Sera usada para somar as bonecas internas e ver se cabe na superior
        int pilhaNivel[tamanhoSequencia];
        int indiceFinalPilhaNivel = -1;
        int eMatriosca = 1;
        int permanecerNoNivel = 0;

        for (int i = 0; i < tamanhoSequencia; i++) {
            int numeroAtual;
            scanf("%d", &numeroAtual);

            // Entra no if se o numero recebido for negativo
            if (numeroAtual < 0) {
                // Adiciono o numero da entrada na pilha pois encontrei o comeco de uma boneca
                indiceFinalPilhaBonecas = push(pilhaBonecas, numeroAtual, indiceFinalPilhaBonecas);

                // Se a variavel permanecer no nivel for verdadeira, sabemos que na interacao interior uma boneca se completou, e como a entrada atual é negativa seguinifica que estamos dentro de uma boneca com mais de uma boneca diretamente contida, com isso somamos o tamanho delas, se nao estamos dentro de uma boneca que ate o momento tem apenas uma boneca diretamente contida, assim apenas adicionamos na pilha
                if (permanecerNoNivel) {
                    int ultimoNumero = last(pilhaNivel, indiceFinalPilhaNivel) + abs(numeroAtual);
                    indiceFinalPilhaNivel = pop(pilhaNivel, indiceFinalPilhaNivel);
                    indiceFinalPilhaNivel = push(pilhaNivel, ultimoNumero, indiceFinalPilhaNivel);
                    permanecerNoNivel = 0;
                } else {
                    indiceFinalPilhaNivel = push(pilhaNivel, abs(numeroAtual), indiceFinalPilhaNivel);
                }
            } else {

                // Se a variavel permanecer no nivel for verdadeira, sabemos que na interacao interior uma boneca se completou, e como a entrada atual é positiva seguinifica que ja verificamos todas as bonecas contidas na boneca atual, assim se o tamanho da boneca atual for maior que a soma das bonecas diretamente contidas, temos uma matriosca, do contrario nao temos uma matriosca
                if (numeroAtual > last(pilhaNivel, indiceFinalPilhaNivel) && permanecerNoNivel) {
                    indiceFinalPilhaNivel = pop(pilhaNivel, indiceFinalPilhaNivel);
                } else if (permanecerNoNivel) {
                    eMatriosca = 0;
                }
                // Se o anterior for o negativo do numero atual, encontramos o fim de uma boneca
                if (numeroAtual == abs(last(pilhaBonecas, indiceFinalPilhaBonecas))) {
                    // Retiro da pilha pois encontrei o fim de uma boneca
                    indiceFinalPilhaBonecas = pop(pilhaBonecas, indiceFinalPilhaBonecas);
                    // Como uma boneca se completou vamos continuar dentro da mesma boneca superior
                    permanecerNoNivel = 1;
                } else {
                    eMatriosca = 0;
                }
            }
        }

        if (eMatriosca) {
            printf(":-) Matriosca!\n");
        } else {
            printf(":-( Tente novamente.\n");
        }

    } while (tamanhoSequencia != 0);

    return 0;
}