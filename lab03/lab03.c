#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Recebe o numero do mes e o ano, e retorna quantos dias tem o mes, considerando inclusive anos bissextos.
int numeroDiasMes(int mes, int ano) {
    switch( mes )
    {
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return ano % 4 == 0 && ano % 100 != 0 ? 29 : 28;
        default:
            return 31;
    };
}

int main(void) {

    int diaInicial, mesInicial, anoInicial, horaNascer, minutoNascer, segundoNascer, horaPor, minutoPor, segundoPor, conversoesBemSucedidas, totalSegundosNovoSistema = 0, solSePosNoDiaAnterior = 1;

    // Guarda as entradas recebidas, e a variavel conversoesBemSucedidas guarda se todas as conversoes foram bem sucedidas, util para saber quando terminar o while.
    conversoesBemSucedidas = scanf("%d/%d/%d %d:%d:%d %d:%d:%d", &diaInicial, &mesInicial, &anoInicial, &horaNascer, &minutoNascer, &segundoNascer, &horaPor, &minutoPor, &segundoPor);

    // Enquanto recebermos 9 entradas no scanf, continuamos o loop, uma vez que existe mais linhas a serem recebidas.
    while(conversoesBemSucedidas == 9) {

        int totalSegundosNascer, totalSegundosPor, dia, mes, ano, segundosComSol;

        // Transforma as horas e os minutos em segundo, e soma tudo para termos apenas uma unidade, assim facilitando sua manipulacao.
        totalSegundosNascer = (horaNascer * 60 * 60) + (minutoNascer * 60) + segundoNascer;
        totalSegundosPor = (horaPor * 60 * 60) + (minutoPor * 60) + segundoPor;

        // Aqui calculamos quantos segundos de sol ocorreu no dia, considerando todas as possibilidades de entrada.
        if (horaNascer != 99 && horaPor == 99) {
            segundosComSol = totalSegundosNascer - 86400;
            solSePosNoDiaAnterior = 0;
        } else if (horaNascer == 99 && horaPor != 99) {
            segundosComSol = 86400 + totalSegundosPor;
            solSePosNoDiaAnterior = 1;
        } else  if (horaNascer == 99 && horaPor == 99 && solSePosNoDiaAnterior == 1) {
            segundosComSol = 0;
        } else if (horaNascer == 99 && horaPor == 99 && solSePosNoDiaAnterior == 0) {
            segundosComSol = 86400;
        } else if (totalSegundosNascer > totalSegundosPor) {
            segundosComSol = 86400 + totalSegundosPor - totalSegundosNascer;
        } else {
            segundosComSol =  totalSegundosPor - totalSegundosNascer;
        }

        // Aqui armazenamos a soma de todos os segundos de sol ate o momento.
        totalSegundosNovoSistema += abs(segundosComSol);

        // Aqui recebemos novamente as entradas, e atualizamos a variavel conversoesBemSucedidas, para podermos saber se ainda tem uma proxima linha de dados, caso ao tenha o loop acaba.
        conversoesBemSucedidas = scanf("%d/%d/%d %d:%d:%d %d:%d:%d", &dia, &mes, &ano, &horaNascer, &minutoNascer, &segundoNascer, &horaPor, &minutoPor, &segundoPor);
    }

    int diaFinal, mesFinal, anoFinal, diasTotais;

    // Aqui arrendondamos para baixo o numero de dias no novo sistema.
    diasTotais = floor(totalSegundosNovoSistema / 43200);

    diaFinal = diaInicial + diasTotais;
    mesFinal = mesInicial;
    anoFinal = anoInicial;

    // Aqui verificamos se o numero de dias totais ultrapassa o numero de dias do mes, caso ocorra entramos no loop, e ficamos nele ate que esse numero seja inferior.
    while (diaFinal > numeroDiasMes(mesFinal, anoFinal)) {
        // Ja que o numero de dias totais ultrapassou o numero de dias do mes, subtraimos do mesmo o numero de dias do mes, e vamos para o proximo mes.
        diaFinal -= numeroDiasMes(mesFinal, anoFinal);
        mesFinal += 1;

        // Caso o numero do mes seja maior que doze, vamos para o proximo ano.
        if (mesFinal > 12) {
            anoFinal += 1;
            mesFinal = 1;
        }
    }

    printf("%d/%d/%d\n", diaFinal, mesFinal, anoFinal);

    return 0;
}

