#include <stdio.h>

/* Encontra os divisores proprios do numero dado, e devolve a soma deles. */
int encontraDivisoresProprios(int numero) {
    int i, somaDivisores = 0;
    for (i = 1; i <= numero / 2; i++) {
        int restoDivisao;
        restoDivisao = numero % i;
        if (restoDivisao == 0) {
            somaDivisores += i;
        }
    }
    return somaDivisores;
}

int main() {
    int primeiroNumero, segundoNumero;
    scanf("%d %d", &primeiroNumero, &segundoNumero);

    int somaDivisoresPrimeiroNumero, somaDivisoresSegundoNumero;
    somaDivisoresPrimeiroNumero = encontraDivisoresProprios(primeiroNumero);
    somaDivisoresSegundoNumero = encontraDivisoresProprios(segundoNumero);

    if (primeiroNumero == somaDivisoresSegundoNumero && segundoNumero == somaDivisoresPrimeiroNumero)
        printf("%d e %d sao amigos\n", primeiroNumero, segundoNumero);
    else
        printf("%d e %d nao sao amigos\n", primeiroNumero, segundoNumero);

    return 0;
}
