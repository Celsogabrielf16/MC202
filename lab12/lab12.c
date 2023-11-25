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

// Recebe um numero qualquer e verifica se o mesmo é primo
int verificaNumeroPrimo(int numero) {
    int isPrimo = 1;
    for (int i = 2; i < numero; i++) {
        if (numero % i == 0) {
            isPrimo = 0;
        }
    }
    return isPrimo;
}

// Recebe o numero de parares que queremos armazenar e encontra o proximo primo em relação ao seu dobro mais um
int tamanhoIdealTabela(int numeroPares) {
    int dobroNumeroPares = numeroPares * 2 + 1;
    while (verificaNumeroPrimo(dobroNumeroPares) != 1) dobroNumeroPares += 2;
    return dobroNumeroPares;
}

// Funcao hash com uma boa dispercao, recebe uma string e retorna um numero positivo que sera usado como chave da nossa tabela hash
unsigned long djb2(unsigned char *str, int tamanhoTabela) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) hash = ((hash << 5) + hash) ^ c;
  return hash % tamanhoTabela;
}

// Cria e inicia uma tabela hash
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

// Limpa a memoria
void liberaTabela(Tabela* tabelaHash, int tamanhoTabela) {
    for (int i = 0; i < tamanhoTabela; i++) {
        free(tabelaHash[i].dados);
    }

    free(tabelaHash);
    return;
}

// Recebe uma chave que pode ou nao ter colisoes, se tiver colisoes encontra uma chave desocupada usando hashing dupla
int resolveColisoes (Tabela* tabelaHash, unsigned long chave, int tamanhoTabela) {
    unsigned long chaveAtual = chave;
    int numeroColisoes = 0;
    while (tabelaHash[chaveAtual].estadoAtual == 1) {
        numeroColisoes++;
        chaveAtual = (chaveAtual % tamanhoTabela + numeroColisoes * (1 + (chaveAtual % (tamanhoTabela - 1)))) % tamanhoTabela;
    }
    return chaveAtual % tamanhoTabela;
}

// Percorre todos os dados da tabela procurando determinada cadeia e retorna a mesma ou NULL caso não encontre
Par* encontraDados (Tabela* tabelaHash, unsigned long chave, int tamanhoTabela, unsigned char* string) {
    unsigned long chaveAtual = chave;
    int numeroColisoes = 0;
    while (tabelaHash[chaveAtual].estadoAtual != 0) {
        if (tabelaHash[chaveAtual].estadoAtual != 2 && strcmp((const char*)tabelaHash[chaveAtual].dados->cadeia, (const char*)string) == 0) {
            return tabelaHash[chaveAtual].dados;
        } else {
            numeroColisoes++;
            chaveAtual = (chaveAtual % tamanhoTabela + numeroColisoes * (1 + (chaveAtual % (tamanhoTabela - 1)))) % tamanhoTabela;
        }
    }
    return NULL;
}

// Remove da tabela hash o par na posicao da chave dada, caso tenha colisao resolve com hashing dupla
void removeDados (Tabela* tabelaHash, unsigned long chave, int tamanhoTabela, unsigned char* string) {
    unsigned long chaveAtual = chave;
    int numeroColisoes = 0;
    while (tabelaHash[chaveAtual].estadoAtual != 0) {
        if (tabelaHash[chaveAtual].estadoAtual == 1 && strcmp((const char*)tabelaHash[chaveAtual].dados->cadeia, (const char*)string) == 0) {
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

int main(void) {
    char operacao;
    Tabela* tabelaHash = NULL;
    int tamanhoTabela = 0, timestampAtual = 0;
    while (scanf("%c", &operacao) == 1) {
        if (operacao == 'c') {
            int numeroPares;
            scanf(" %d", &numeroPares);

            // Caso ja exista uma tabela hash devemos libera-la antes de criar uma nova
            if(tabelaHash) {
                liberaTabela(tabelaHash, tamanhoTabela);
                timestampAtual = 0;
            }

            tamanhoTabela = tamanhoIdealTabela(numeroPares);
            tabelaHash = criaTabela(tamanhoTabela);
        } else if (operacao == 'i') {
            char espaco;
            unsigned char string[250];
            scanf("%c", &espaco);
            scanf("%250[^\n]", string);
            unsigned long chave = djb2(string, tamanhoTabela);

            // Caso a cadeia dada ja esteja na tabela hash nao devemos fazer nada, caso contrario inserimos a cadeia e o timestamp
            if (!encontraDados(tabelaHash, chave, tamanhoTabela, string)) {
                chave = resolveColisoes(tabelaHash, chave, tamanhoTabela);

                tabelaHash[chave].dados = malloc(sizeof(Par));

                if (!tabelaHash) {
                    return 0;
                }

                tabelaHash[chave].dados->timestamp = timestampAtual;
                strcpy((char*)tabelaHash[chave].dados->cadeia, (const char*)string);
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