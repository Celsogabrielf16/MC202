#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    int numeroElementos;
    scanf("%d", &numeroElementos);

    int vetorV[numeroElementos];

    for (int posicao = 0; posicao < numeroElementos; posicao++) {
        scanf("%d", &vetorV[posicao]);
    }

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
            if (operacao == 's') {
                int soma = 0;
                for (int i = 0; i < truque; i++) {
                    int ultimoElementoDoBloco = (i + 1) * truque - 1;
                    int primeiroElementoDoBloco = i * truque;

                    if (primeiroElementoDoBloco >= primeiroNumero && ultimoElementoDoBloco <= segundoNumero ) {
                        soma += vetorR[i];
                    } else if (primeiroElementoDoBloco < primeiroNumero && ultimoElementoDoBloco >= primeiroNumero) {
                        for (int j = (truque - 1) + truque * i; j >= primeiroNumero; j--) {
                            soma += vetorV[j];
                        }
                    } else if (primeiroElementoDoBloco <= segundoNumero && ultimoElementoDoBloco > segundoNumero) {
                        for (int j = segundoNumero - (primeiroElementoDoBloco - 1); j > 0; j--) {
                            soma += vetorV[primeiroElementoDoBloco - 1 + j];
                        }
                    }
                }
                printf("%d\n", soma);
            } else if (operacao == 'a') {
                for (int i = 0; i < truque; i++) {
                    if (primeiroNumero >= i * truque && primeiroNumero <= (i + 1) * truque - 1) {
                        vetorR[i] -= vetorV[primeiroNumero];
                        vetorV[primeiroNumero] = segundoNumero;
                        vetorR[i] += vetorV[primeiroNumero];
                    }
                }
            }
        } else { 
            executarLoop = 0;
        }
    };

    return 0;
}