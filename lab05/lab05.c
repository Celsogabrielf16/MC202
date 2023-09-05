#include <stdio.h>
#include <ctype.h>

int main(void) {
    int executarLoop = 1;

    while ( executarLoop ) {
        int conversoesBemSucedidas;
        char palavra[20];

        conversoesBemSucedidas = scanf("%s", palavra);

        int numeroDePalindromos = 0;

        if ( conversoesBemSucedidas == 1 ) {

            for (int i = 1; palavra[i] != '\0'; i++) {
                /* char caractereAntecessor = tolower(palavra[i - 1]);
                char caractereAtual = tolower(palavra[i]);
                char caractereSucessor = tolower(palavra[i + 1]);

                if ( caractereAntecessor == caractereSucessor && caractereAtual != caractereAntecessor) {
                    numeroDePalindromos += 1;
                    printf ("Caractere %d: %c %c %c\n", i, caractereAntecessor, caractereAtual, caractereSucessor);
                } */
            }

        } else {
            executarLoop = 0;
        }

        if (  numeroDePalindromos >= 2 ) {
            printf("%s\n", palavra);
        }
    }

    return 0;
}