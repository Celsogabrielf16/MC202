#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcao recursiva que limpa a posicao atual da matriz e verifica se alguma das casas visinhas tem petroleo, se tiver, chama ela mesma com a posicao do petroleo encontrado.  
void encontraDepositoDePetroleo(char** matriz, int linhaLote, int colunaLote, int linhasTotais, int colunasTotais) {
    matriz[linhaLote][colunaLote] = '*';
    if (colunaLote - 1 >= 0 && matriz[linhaLote][colunaLote - 1] == '@') {
        encontraDepositoDePetroleo(matriz, linhaLote, colunaLote - 1, linhasTotais, colunasTotais);
    }
    if (linhaLote - 1 >= 0 && colunaLote - 1 >= 0 && matriz[linhaLote - 1][colunaLote - 1] == '@') {
        encontraDepositoDePetroleo(matriz, linhaLote - 1, colunaLote - 1, linhasTotais, colunasTotais);
    }
    if (linhaLote - 1 >= 0 && matriz[linhaLote - 1][colunaLote] == '@') {
        encontraDepositoDePetroleo(matriz, linhaLote - 1, colunaLote, linhasTotais, colunasTotais);
    }
    if (linhaLote - 1 >= 0 && colunaLote + 1 <= colunasTotais && matriz[linhaLote - 1][colunaLote + 1] == '@') {
        encontraDepositoDePetroleo(matriz, linhaLote - 1, colunaLote + 1, linhasTotais, colunasTotais);
    }
    if (colunaLote + 1 <= colunasTotais && matriz[linhaLote][colunaLote + 1] == '@') {
        encontraDepositoDePetroleo(matriz, linhaLote, colunaLote + 1, linhasTotais, colunasTotais);
    }
    if (linhaLote + 1 <= linhasTotais && colunaLote + 1 <= colunasTotais && matriz[linhaLote + 1][colunaLote + 1] == '@') {
        encontraDepositoDePetroleo(matriz, linhaLote + 1, colunaLote + 1, linhasTotais, colunasTotais);
    }
    if (linhaLote + 1 <= linhasTotais && matriz[linhaLote + 1][colunaLote] == '@') {
        encontraDepositoDePetroleo(matriz, linhaLote + 1, colunaLote, linhasTotais, colunasTotais);
    }
    if (linhaLote + 1 <= linhasTotais && colunaLote - 1 >= 0 && matriz[linhaLote + 1][colunaLote - 1] == '@') {
        encontraDepositoDePetroleo(matriz, linhaLote + 1, colunaLote - 1, linhasTotais, colunasTotais);
    }
}

int main(void) {
    int linhas, colunas;
    do {
        scanf("%d %d", &linhas, &colunas);
        
        char **terreno;
        terreno = malloc(linhas * sizeof(char*));

        // Preenche a matriz terreno que representa todo o terreno.
        for (int linha = 0; linha < linhas; linha++) {
            terreno[linha] = malloc(colunas * sizeof(char));
            for (int coluna = 0; coluna < colunas; coluna++) {
                scanf(" %c", &terreno[linha][coluna]);
            }
        }

        int numeroDepositosPetroleo = 0;

        // Percorre a matriz terreno detectando petroleo.
        for (int linha = 0; linha < linhas; linha++) {
            for (int coluna = 0; coluna < colunas; coluna++) {
                if (terreno[linha][coluna] == '@') {
                    encontraDepositoDePetroleo(terreno, linha, coluna, linhas - 1, colunas - 1);
                    numeroDepositosPetroleo += 1;
                }
            }
        }

        if (colunas != 0) {
            printf("%d\n", numeroDepositosPetroleo);
        }

    } while (colunas != 0);
}