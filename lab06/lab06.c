#include <stdio.h>
#include <string.h>

int main(void) {

    int numeroTorneios;

    scanf("%d", &numeroTorneios);

    for (int i = 0; i < numeroTorneios; i++) {
        struct time {
            char nome[30];
            int totalPontos;
            int jogosDisputados;
            int vitorias;
            int empates;
            int derrotas;
            int saldoDeGols;
            int golsMarcados;
            int golsSofridos;
        } times[30];

        char nomeTorneio[100];

        scanf(" %100[^\n]", nomeTorneio);

        int numeroTimes;

        scanf("%d", &numeroTimes);

        for (int i = 0; i < numeroTimes; i++) {
            scanf(" %30[^\n]", times[i].nome);
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
            char timeCasa[30], timeVisitante[30];
            int golsTimeCasa, golsTimeVisitante;

            scanf(" %30[^#]#%d@%d#%30[^\n]", timeCasa, &golsTimeCasa, &golsTimeVisitante, timeVisitante);

            for (int numeroTime = 0; numeroTime < numeroTimes; numeroTime++) {
                if (strcmp (times[numeroTime].nome, timeCasa) == 0) {
                    times[numeroTime].golsMarcados += golsTimeCasa;
                    printf("nt: %s, tp: %d\n", times[numeroTime].nome, times[numeroTime].golsMarcados);

                } else if (strcmp (times[numeroTime].nome, timeVisitante) == 0) {
                    times[numeroTime].golsMarcados += golsTimeVisitante;
                    printf("nt: %s, tp: %d\n", times[numeroTime].nome, times[numeroTime].golsMarcados);
                }
            }
        }
    }

    return 0;
}