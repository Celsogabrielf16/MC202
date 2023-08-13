#include <stdio.h>
#include <math.h>

// Aqui usamos o Teorema de Pitágoras para calcular a distancia entre as coordenadas do animal e o do buraco
double pitagoras(double xAnimal, double yAnimal, double xBuraco, double yBuraco)
{
    return sqrt(pow(fabs(xAnimal - xBuraco), 2) + pow(fabs(yAnimal - yBuraco), 2));
}

int main(void){

    int numeroBuracos;
    float xCoelho, yCoelho, xRaposa, yRaposa;
    
    scanf("%d %f %f %f %f", &numeroBuracos, &xCoelho, &yCoelho, &xRaposa, &yRaposa);

    double coordenadasBuracos[numeroBuracos][2], xBuraco, yBuraco;
    
    // Aqui guardamos as coordenadas de cada buraco em um vetor, onde i representa o numero do mesmo e 0 e 1 representa o x e y respectivamente
    for (int i = 0; i < numeroBuracos; i++) 
    {
        scanf("%lf %lf", &xBuraco, &yBuraco);

        coordenadasBuracos[i][0] = xBuraco;
        coordenadasBuracos[i][1] = yBuraco;
    }

    for (int i = 0; i < numeroBuracos; i++) 
    {
        double distanciaCoelhoBuraco = pitagoras(xCoelho, yCoelho, coordenadasBuracos[i][0], coordenadasBuracos[i][1]);
        double distanciaRaposaBuraco = (pitagoras(xRaposa, yRaposa, coordenadasBuracos[i][0], coordenadasBuracos[i][1])) / 2; // Dividimos por dois pois a raposa tem o doobro da velocidade do coelho

        // Aqui verificamos se a distancia do coelho ate o buraco é menor do que a distancia da raposa ate o buraco
        if ( distanciaCoelhoBuraco < distanciaRaposaBuraco )
        {
            printf("O coelho pode escapar pelo buraco (%.3lf,%.3lf).\n", coordenadasBuracos[i][0], coordenadasBuracos[i][1]);
            return 0;
        }
    }

    printf("O coelho nao pode escapar.\n");
    
    return 0;
}