#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Realiza a soa do indice desejado ao outro
void somar(int truque, int primeiroIndice, int segundoIndice, int* vetorR, int* vetorV) {
    int soma = 0;
    // O loop roda sqrt(n) vezes, com a finilidade de encontrar e somar blocos [i,j] (correspondentes a um indice do vetorR) contidos entre
    // os indices dados e somar tambem os indices desejados do vetorV não incluidos completamente no vetorR
    for (int i = 0; i < truque; i++) {
        int ultimoElementoDoBloco = (i + 1) * truque - 1;
        int primeiroElementoDoBloco = i * truque;

        // Se o bloco [(i + 1) * truque - 1, i * truque] estiver contido nos indices desejados soma o indice do vetorR correspondente,
        // Se não estiver contido, verifica quais posicoes do vetorV faltam serem somadas
        if (primeiroElementoDoBloco >= primeiroIndice && ultimoElementoDoBloco <= segundoIndice ) {
            soma += *(vetorR + i);
        } else if (primeiroElementoDoBloco < primeiroIndice && ultimoElementoDoBloco >= primeiroIndice) {
            for (int j = (truque - 1) + truque * i; j >= primeiroIndice; j--) {
                soma += *(vetorV + j);
            }
        } else if (primeiroElementoDoBloco <= segundoIndice && ultimoElementoDoBloco > segundoIndice) {
            for (int j = segundoIndice - (primeiroElementoDoBloco - 1); j > 0; j--) {
                soma += *(vetorV + (primeiroElementoDoBloco - 1 + j));
            }
        }
    }
    printf("%d\n", soma);
}

// Atualiza o vetorV e o vetorR no indice dado, pelo numero desejado
void atualizar(int truque, int indice, int numero, int* vetorR, int* vetorV) {
    for (int i = 0; i < truque; i++) {
        if (indice >= i * truque && indice <= (i + 1) * truque - 1) {
            *(vetorR + i) -= *(vetorV + indice);
            *(vetorV + indice) = numero;
            *(vetorR + i) += *(vetorV + indice);
        }
    }
}

// Verifica qual operacao é a desejada, e chama a funcao correta
void verificaOpercao(char operacao, int truque, int primeiroNumero, int segundoNumero, int* vetorR, int* vetorV) {
    switch (operacao) {
        case 's':
            somar(truque, primeiroNumero, segundoNumero, vetorR, vetorV);
            break;
        case 'a':
            atualizar(truque, primeiroNumero, segundoNumero, vetorR, vetorV);
            break;
    }
}

int main(void) {
    int numeroElementos;
    scanf("%d", &numeroElementos);

    int vetorV[numeroElementos];

    // Preenche o vetorV
    for (int posicao = 0; posicao < numeroElementos; posicao++) {
        scanf("%d", &vetorV[posicao]);
    }

    // Preenche o vetorR
    int truque = ceil(sqrt(numeroElementos)), vetorR[truque];
    for (int posicaoVetorR = 0; posicaoVetorR < truque; posicaoVetorR++) {
        vetorR[posicaoVetorR] = 0;
        for (int posicaoVetorV = 0; posicaoVetorV < truque; posicaoVetorV++) {
            if (truque * posicaoVetorR + posicaoVetorV >= numeroElementos) {
                break;
            }
            vetorR[posicaoVetorR] += vetorV[truque * posicaoVetorR + posicaoVetorV];
        }
    }

    int conversoesBemSucedidas, primeiroNumero, segundoNumero, executarLoop = 1;
    char operacao;
    while (executarLoop) {
        conversoesBemSucedidas = scanf(" %c %d %d", &operacao, &primeiroNumero, &segundoNumero);

        if (conversoesBemSucedidas == 3) {
            verificaOpercao(operacao, truque, primeiroNumero, segundoNumero, vetorR, vetorV);
        } else { 
            executarLoop = 0;
        }
        
    };

    return 0;
}