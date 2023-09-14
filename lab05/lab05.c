#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int verificaSucessorEAntecessor(char* caractere, int nElementosAnteriores, int nElementosSucessores, int comprimentoPalindromo, int totalCaracteresPalavra) {
    char caractereAntecessor = tolower(*(caractere - nElementosAnteriores));
    char caractereAtual = tolower(*(caractere));
    char caractereSucessor = tolower(*(caractere + nElementosSucessores));

    if ( caractereAntecessor == caractereSucessor && (comprimentoPalindromo * 2 + 1) != totalCaracteresPalavra) {
        return verificaSucessorEAntecessor(caractere, nElementosAnteriores + 1, nElementosSucessores + 1, comprimentoPalindromo + 1, totalCaracteresPalavra);
    } else {
        return comprimentoPalindromo;
    }
}

int main(void) {
    int executarLoop = 1;

    while ( executarLoop ) {
        int conversoesBemSucedidas;
        char palavra[256];

        conversoesBemSucedidas = scanf("%s", palavra);

        int numeroPalindromos = 0;

        if ( conversoesBemSucedidas == 1 ) {

            int totalCaracteresPalavra = strlen(palavra);

            char palindromosDaPalavra[64][64];

            for (int i = 1; i < totalCaracteresPalavra - 1; i++) {

                char* caractere = palavra + i;

                char caractereAntecessor = tolower(*(caractere - 1));
                char caractereAtual = tolower(*(caractere));
                char caractereSucessor = tolower(*(caractere + 1));

                int numeroCaracteresPalindromo;
                char palindromo[256];

                if (caractereAtual == caractereAntecessor && caractereAtual != caractereSucessor) {
                    numeroCaracteresPalindromo = verificaSucessorEAntecessor(caractere, 2, 1, 0, totalCaracteresPalavra);

                    palindromo[numeroCaracteresPalindromo + 1] = *(caractere);
                    palindromo[numeroCaracteresPalindromo] = *(caractere);

                    if (numeroCaracteresPalindromo >= 1 && numeroCaracteresPalindromo * 2 + 2 == totalCaracteresPalavra) {

                        int aux = 2;

                        for (int i = 1; i <= numeroCaracteresPalindromo; i++) {
                            palindromo[numeroCaracteresPalindromo - i] = *(caractere - i - 1);
                            aux ++;
                        }

                        for (int i = 1; i <= numeroCaracteresPalindromo; i++) {
                            palindromo[numeroCaracteresPalindromo + i + 1] = *(caractere + i);
                            aux ++;
                        }

                        palindromo[aux] = '\0';

                        

                    } else if (numeroCaracteresPalindromo >= 1 && numeroCaracteresPalindromo * 2 + 2 > totalCaracteresPalavra) {

                        numeroCaracteresPalindromo -= 1;
                        int aux = 2;

                        for (int i = 1; i <= numeroCaracteresPalindromo; i++) {
                            palindromo[numeroCaracteresPalindromo - i] = *(caractere - i - 1);
                            aux ++;
                        }

                        for (int i = 1; i <= numeroCaracteresPalindromo; i++) {
                            palindromo[numeroCaracteresPalindromo + i + 1] = *(caractere + i);
                            aux ++;
                        }

                        palindromo[aux] = '\0';

                        
                    }


                } else {
                    numeroCaracteresPalindromo = verificaSucessorEAntecessor(caractere, 1, 1, 0, totalCaracteresPalavra);

                    if (numeroCaracteresPalindromo >= 1) {
                        palindromo[numeroCaracteresPalindromo] = *(caractere);
                        
                        int aux = 1;

                        for (int i = 1; i <= numeroCaracteresPalindromo; i++) {
                            palindromo[numeroCaracteresPalindromo - i] = *(caractere - i);
                            aux ++;
                        }

                        for (int i = 1; i <= numeroCaracteresPalindromo; i++) {
                            palindromo[numeroCaracteresPalindromo + i] = *(caractere + i);
                            aux ++;
                        }


                        palindromo[aux] = '\0';

                        

                    }
                }

                palindromosDaPalavra[i] = palindromo;

                printf("p: %s\n", palindromosDaPalavra);
            }

        } else {
            executarLoop = 0;
        }

        if (numeroPalindromos > 1) {
            printf("%s\n", palavra);
        }
    }

    return 0;
}