#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Struct com todas as informações necessarias do time, que uma vez ordenado é a classificacao.
struct time {
    char nome[31];
    int totalPontos;
    int jogosDisputados;
    int vitorias;
    int empates;
    int derrotas;
    int saldoDeGols;
    int golsMarcados;
    int golsSofridos;
} times[30];

// Recebe o nome de um time e copia o mesmo em uma nova array so que com todos os caracteres minusculos.
void nomeMinusculo(char nomeTimeMaiusculo[], char nomeTimeMinusculo[]){
    int i = 0;
    while (nomeTimeMaiusculo[i] != '\0') {
        nomeTimeMinusculo[i] = tolower(nomeTimeMaiusculo[i]);
        i++;
    }
    nomeTimeMinusculo[i] = '\0';
}

// Funcao necessaraia para o qsort, e verifica cada criterio de preferencia na tabela de classificacao final.
int comparaClassificacao(const void* time1, const void* time2) {
    if ((*(struct time*)time1).totalPontos == (*(struct time*)time2).totalPontos) {
        if ((*(struct time*)time1).vitorias == (*(struct time*)time2).vitorias) {
            if ((*(struct time*)time1).saldoDeGols == (*(struct time*)time2).saldoDeGols) {
                if ((*(struct time*)time1).golsMarcados == (*(struct time*)time2).golsMarcados) {
                    if ((*(struct time*)time1).jogosDisputados == (*(struct time*)time2).jogosDisputados) {
                        char nomeTime1[31], nomeTime2[31];
                        nomeMinusculo((*(struct time*)time1).nome, nomeTime1);
                        nomeMinusculo((*(struct time*)time2).nome, nomeTime2);
                        if (strcmp (nomeTime1, nomeTime2) == 0) {
                            return 0;
                        } else {
                            if (strcmp (nomeTime1, nomeTime2) > 0) {
                                return 1;
                            } else {
                                return -1;
                            }
                        }
                    } else {
                        if ((*(struct time*)time1).jogosDisputados < (*(struct time*)time2).jogosDisputados) {
                            return -1;
                        } else {
                            return 1;
                        }
                    }
                } else {
                    if ((*(struct time*)time1).golsMarcados < (*(struct time*)time2).golsMarcados) {
                        return 1;
                    } else {
                        return -1;
                    }
                }
            } else {
                if ((*(struct time*)time1).saldoDeGols < (*(struct time*)time2).saldoDeGols) {
                    return 1;
                } else {
                    return -1;
                }
            }
        } else {
            if ((*(struct time*)time1).vitorias < (*(struct time*)time2).vitorias) {
                return 1;
            } else {
                return -1;
            }
        }
    } else {
        if ((*(struct time*)time1).totalPontos < (*(struct time*)time2).totalPontos) {
            return 1;
        } else {
            return -1;
        }
    }
}

int main(void) {

    int numeroTorneios;

    scanf("%d", &numeroTorneios);

    for (int i = 0; i < numeroTorneios; i++) {
        char nomeTorneio[100];

        scanf(" %100[^\n]", nomeTorneio);

        int numeroTimes;

        scanf("%d", &numeroTimes);

        // Recebe o nome de cada time, e tambem inicia todas as informacoes do time com 0.
        for (int i = 0; i < numeroTimes; i++) {
            scanf(" %31[^\n]", times[i].nome);
            times[i].totalPontos = 0;
            times[i].jogosDisputados = 0;
            times[i].vitorias = 0;
            times[i].empates = 0;
            times[i].derrotas = 0;
            times[i].saldoDeGols = 0;
            times[i].golsMarcados = 0;
            times[i].golsSofridos = 0;
        }

        int numeroJogos;

        scanf("%d", &numeroJogos);

        for (int i = 0; i < numeroJogos; i++) {
            char timeCasa[31], timeFora[31];
            int golsTimeCasa, golsTimeFora;

            scanf(" %31[^#]#%d@%d#%31[^\n]", timeCasa, &golsTimeCasa, &golsTimeFora, timeFora);

            int pontosCasa = 0, pontosFora = 0, vCasa = 0, vFora = 0, eCasa = 0, eFora = 0, dCasa = 0, dFora = 0;

            // Verifica qual time ganhou o jogo, ou se eles empataram, e atribui as informcoes relevantes, que nao deixam de ser 0.
            if (golsTimeCasa > golsTimeFora) {
                pontosCasa = 3;
                vCasa = 1;
                dFora = 1;
            } else if (golsTimeFora > golsTimeCasa) {
                pontosFora = 3;
                vFora = 1;
                dCasa = 1;
            } else {
                pontosCasa = 1;
                pontosFora = 1;
                eCasa = 1;
                eFora = 1;
            }

            // Percorre a array de times, com a finalidade de encontrar um dos times que jogaram.
            for (int numeroTime = 0; numeroTime < numeroTimes; numeroTime++) {
                // Verifica se o time em questao é o time da casa ou o visitante, e atualiza suas informacoes.
                if (strcmp (times[numeroTime].nome, timeCasa) == 0) {
                    times[numeroTime].totalPontos += pontosCasa;
                    times[numeroTime].jogosDisputados += 1;
                    times[numeroTime].vitorias += vCasa;
                    times[numeroTime].empates += eCasa;
                    times[numeroTime].derrotas += dCasa;
                    times[numeroTime].saldoDeGols += (golsTimeCasa - golsTimeFora);
                    times[numeroTime].golsMarcados += golsTimeCasa;
                    times[numeroTime].golsSofridos += golsTimeFora;

                } else if (strcmp (times[numeroTime].nome, timeFora) == 0) {
                    times[numeroTime].totalPontos += pontosFora;
                    times[numeroTime].jogosDisputados += 1;
                    times[numeroTime].vitorias += vFora;
                    times[numeroTime].empates += eFora;
                    times[numeroTime].derrotas += dFora;
                    times[numeroTime].saldoDeGols += (golsTimeFora - golsTimeCasa);
                    times[numeroTime].golsMarcados += golsTimeFora;
                    times[numeroTime].golsSofridos += golsTimeCasa;
                }
            }
        }

        if (i == 0) {
            printf("%s\n", nomeTorneio);
        } else {
            printf("\n%s\n", nomeTorneio);
        }

        // Pega a array de structs 'times', que nao esta necessariamente na ordem correta e o ordena, de acordo com a funcao comparaClassificacao.
        qsort(times, numeroTimes, sizeof(struct time), comparaClassificacao);

        for (int numeroTime = 0; numeroTime < numeroTimes; numeroTime++) {
            printf("%d) %s, %dp, %dj (%d-%d-%d), %ds (%d-%d)\n", numeroTime + 1, times[numeroTime].nome, times[numeroTime].totalPontos,times[numeroTime].jogosDisputados,times[numeroTime].vitorias,times[numeroTime].empates,times[numeroTime].derrotas,times[numeroTime].saldoDeGols,times[numeroTime].golsMarcados,times[numeroTime].golsSofridos);
        }
    }

    return 0;
}
