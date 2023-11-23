#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct par{
    char cadeia[250];
    int timestamp;
} Par;

typedef struct tabela {
    Par* dados;
    int estadoAtual; // 0 livre, 1 ocupado, 2 removido
} Tabela;

int verificaNumeroPrimo(int numero) {
    int isPrimo = 1;
    for (int i = 2; i < numero; i++) {
        if (numero % i == 0) {
            isPrimo = 0;
        }
    }
    return isPrimo;
}

int tamanhoIdealTabela(int numeroPares) {
    int dobroNumeroPares = numeroPares * 2 + 1;
    while (verificaNumeroPrimo(dobroNumeroPares) != 1) dobroNumeroPares += 2;
    return dobroNumeroPares;
}

unsigned long djb2(unsigned char *str, int tamanhoTabela) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) hash = ((hash << 5) + hash) ^ c;
  return hash % tamanhoTabela;
}

Tabela* criaTabela(int tamanhoTabela) {
    Tabela* tabelaHash = (Tabela*)malloc(tamanhoTabela * sizeof(Tabela));

    if(!tabelaHash) {
        return NULL;
    }

    for (int i = 0; i < tamanhoTabela; i++) {
        tabelaHash[i].dados = NULL;
        tabelaHash[i].estadoAtual = 0;
    }

    return tabelaHash;
}

void liberaTabela(Tabela* tabelaHash, int tamanhoTabela) {
    for (int i = 0; i < tamanhoTabela; i++) {
        free(tabelaHash[i].dados);
    }

    free(tabelaHash);
    return;
}

int resolveColisoes (Tabela* tabelaHash, unsigned long chave, int tamanhoTabela) {
    unsigned long chaveAtual = chave;
    int numeroColisoes = 0;
    while (tabelaHash[chaveAtual].estadoAtual == 1) {
        numeroColisoes++;
        chaveAtual = (chaveAtual % tamanhoTabela + numeroColisoes * (1 + (chaveAtual % (tamanhoTabela - 1)))) % tamanhoTabela;
    }
    return chaveAtual % tamanhoTabela;
}

Par* encontraDados (Tabela* tabelaHash, unsigned long chave, int tamanhoTabela, unsigned char* string) {
    unsigned long chaveAtual = chave;
    int numeroColisoes = 0;
    while (tabelaHash[chaveAtual].estadoAtual != 0) {
        if (tabelaHash[chaveAtual].estadoAtual != 2 && strcmp(tabelaHash[chaveAtual].dados->cadeia, string) == 0) {
            return tabelaHash[chaveAtual].dados;
        } else {
            numeroColisoes++;
            chaveAtual = (chaveAtual % tamanhoTabela + numeroColisoes * (1 + (chaveAtual % (tamanhoTabela - 1)))) % tamanhoTabela;
        }
    }
    return NULL;
}

void removeDados (Tabela* tabelaHash, unsigned long chave, int tamanhoTabela, unsigned char* string) {
    unsigned long chaveAtual = chave;
    int numeroColisoes = 0;
    if (encontraDados(tabelaHash, chave, tamanhoTabela, string)) {
        while (tabelaHash[chaveAtual].estadoAtual != 0) {
            if (strcmp(tabelaHash[chaveAtual].dados->cadeia, string) == 0) {
                free(tabelaHash[chaveAtual].dados);
                tabelaHash[chaveAtual].dados = NULL;
                tabelaHash[chaveAtual].estadoAtual = 2;
                break;
            } else {
                numeroColisoes++;
                chaveAtual = (chaveAtual % tamanhoTabela + numeroColisoes * (1 + (chaveAtual % (tamanhoTabela - 1)))) % tamanhoTabela;
            }
        }
    }
}

int main(void) {
    char operacao;
    Tabela* tabelaHash;
    int tamanhoTabela = 0, timestampAtual = 0;
    while (scanf("%c", &operacao) == 1) {
        if (operacao == 'c') {
            int numeroPares;
            scanf(" %d", &numeroPares);
            tamanhoTabela = tamanhoIdealTabela(numeroPares);

            if(!tabelaHash) {
                liberaTabela(tabelaHash, tamanhoTabela);
                timestampAtual = 0;
            }

            tabelaHash = criaTabela(tamanhoTabela);
        } else if (operacao == 'i') {
            char espaco;
            unsigned char string[250];
            scanf("%c", &espaco);
            scanf("%250[^\n]", string);
            unsigned long chave = djb2(string, tamanhoTabela);

            if (!encontraDados(tabelaHash, chave, tamanhoTabela, string)) {
                chave = resolveColisoes(tabelaHash, chave, tamanhoTabela);

                tabelaHash[chave].dados = malloc(sizeof(Par));

                if (!tabelaHash) {
                    return 0;
                }

                tabelaHash[chave].dados->timestamp = timestampAtual;
                strcpy(tabelaHash[chave].dados->cadeia, string);
                tabelaHash[chave].estadoAtual = 1;

                timestampAtual++;
            }


        } else if (operacao == 'r') {
            char espaco;
            unsigned char string[250];
            scanf("%c", &espaco);
            scanf("%250[^\n]", string);
            unsigned long chave = djb2(string, tamanhoTabela);

            removeDados(tabelaHash, chave, tamanhoTabela, string);
        } else if (operacao == 'b') {
            char espaco;
            unsigned char string[250];
            scanf("%c", &espaco);
            scanf("%250[^\n]", string);
            unsigned long chave = djb2(string, tamanhoTabela);

            Par* dadoEncontrado = encontraDados(tabelaHash, chave, tamanhoTabela, string);

            if (dadoEncontrado) {
                printf("[%s] esta na tabela, timestamp %d\n", string, dadoEncontrado->timestamp);
            } else {
                printf("[%s] nao esta na tabela\n", string);
            }

        } else if (operacao == 'f') {
            liberaTabela(tabelaHash, tamanhoTabela);
            break;
        }
    }
    return 0;
}

/* for (int i = 0; i < tamanhoTabela; i++) {
    tabela[i].cadeia[0] = 'c';
    tabela[i].timestamp = i * 10;
}
printf("++ %p -- %d ++ %c", tabela, tabela[10].timestamp, tabela[10].cadeia[0]); */

/* printf("i\n");
int tmp[10];
for (int i = 0; i < 10; i++) {
    char string[100];
    scanf(" %100[^\n]", string);
    unsigned long hash = djb2(string) % 10;
    printf("%lu\n", hash);
} 
printf("%d %d %s %d\n\n", chave, tabelaHash[chave].estadoAtual, tabelaHash[chave].dados->cadeia, tabelaHash[chave].dados->timestamp);

for (int i = 0; i < tamanhoTabela; i++) {
    if (tabelaHash[i].estadoAtual == 1) {
        printf("%d %d %s %d\n", i, tabelaHash[i].estadoAtual, tabelaHash[i].dados->cadeia, tabelaHash[i].dados->timestamp);
    } else {
        printf("%d %d\n", i, tabelaHash[i].estadoAtual);
    }
}
printf("-------------------------\n\n");
*/