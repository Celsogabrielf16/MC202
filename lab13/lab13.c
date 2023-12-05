#include <stdio.h>
#include <stdlib.h>

typedef struct Grafo {
    int numeroVertices;
    int grauMaximo;
    int** arestas;
    int* grau;
    int* PDVsCriticos;
} Grafo;

Grafo* criaGrafo(int numeroVertices, int grauMaximo) {
    Grafo* novoGrafo = (Grafo*) malloc(sizeof(Grafo));
    if (!novoGrafo)
        return NULL;

    novoGrafo->numeroVertices = numeroVertices;
    novoGrafo->grauMaximo = grauMaximo;
    novoGrafo->grau = (int*) calloc(numeroVertices, sizeof(int));
    if (!novoGrafo->grau)
        return NULL;

    novoGrafo->PDVsCriticos = (int*) calloc(numeroVertices, sizeof(int));
    if (!novoGrafo->PDVsCriticos)
        return NULL;

    novoGrafo->arestas = (int**) malloc(numeroVertices * sizeof(int*));
    if (!novoGrafo->arestas)
        return NULL;
    for(int i = 0; i < numeroVertices; i++) {
        novoGrafo->arestas[i] = (int*) malloc(grauMaximo * sizeof(int));
        if (!novoGrafo->arestas[i])
            return NULL;
    }

    return novoGrafo;
}

void liberaGrafo(Grafo* grafoAtual) {
    if(grafoAtual) {
        for (int i = 0; i < grafoAtual->numeroVertices; i++)
            free(grafoAtual->arestas[i]);
        free(grafoAtual->arestas);
        free(grafoAtual->grau);
        free(grafoAtual->PDVsCriticos);
        free(grafoAtual);
    }
}

void insereAresta(Grafo* grafo, int verticeOrigem, int verticeDestino) {
    int jaExisteNaLista = 0;
    for(int i = 0; i < grafo->grau[verticeOrigem]; i++) {
        if (grafo->arestas[verticeOrigem][i] == verticeDestino) {
            jaExisteNaLista = 1;
        }
    }

    if (!jaExisteNaLista) {
        grafo->arestas[verticeOrigem][grafo->grau[verticeOrigem]] = verticeDestino;
        grafo->grau[verticeOrigem]++;

        grafo->arestas[verticeDestino][grafo->grau[verticeDestino]] = verticeOrigem;
        grafo->grau[verticeDestino]++;
    }
}

int buscaProfundidadeRec (Grafo* grafo, int verticeAtual, int verticeAnterior, int* visitados) {
    visitados[verticeAtual] = 1;
    int encontrouCiclo = 0;

    for(int i = 0; i < grafo->grau[verticeAtual]; i++) {
        int verticeVizinho = grafo->arestas[verticeAtual][i];
        if (visitados[verticeVizinho] == 0) {
            encontrouCiclo = buscaProfundidadeRec (grafo, verticeVizinho, verticeAtual, visitados);
            if (encontrouCiclo) {
                break;
            }
        } else if (verticeAnterior != verticeVizinho && visitados[verticeVizinho] == 2) {
            encontrouCiclo = 1;
            break;
        }
    }

    return encontrouCiclo;
}

int buscaCaminho (Grafo* grafo, int verticeAtual, int verticeMeta, int* verticesVisitados) {
    verticesVisitados[verticeAtual] = 1;
    int encontrouCaminho = 0;

    for(int i = 0; i < grafo->grau[verticeAtual]; i++) {
        int verticeVizinho = grafo->arestas[verticeAtual][i];
        if (verticeVizinho == verticeMeta) {
            return 1;
        } else if (verticesVisitados[verticeVizinho] == 0) {
            encontrouCaminho = buscaCaminho(grafo, verticeVizinho, verticeMeta, verticesVisitados);
            if (encontrouCaminho) {
                break;
            }
        }
    }

    return encontrouCaminho;
}

int buscaCiclo(Grafo* grafo, int verticeAtual, int verticeInicial) {
    int visitados[grafo->numeroVertices], encontrouCiclo = 0;
    for (int i = 0; i < grafo->numeroVertices; i++)
        visitados[i] = 0;

    visitados[verticeInicial] = 2;
    encontrouCiclo = buscaProfundidadeRec(grafo, verticeAtual, verticeInicial, visitados);

    if (encontrouCiclo) {
        for(int i = 0; i < grafo->grau[verticeAtual]; i++) {
            int verticesVisitados[grafo->numeroVertices];
            for (int i = 0; i < grafo->numeroVertices; i++)
                verticesVisitados[i] = 0;

            verticesVisitados[verticeAtual] = 1;
            int encontrouCaminho = buscaCaminho(grafo, grafo->arestas[verticeAtual][i], grafo->arestas[verticeAtual][(i + 1) % grafo->grau[verticeAtual]], verticesVisitados);

            if (!encontrouCaminho) {
                encontrouCiclo = 0;
                break;
            }
        }
    }

    return encontrouCiclo;
}

int buscaProfundidade(Grafo* grafo, int verticeInicial) {
    int PDVsCriticosAdicionados = 0;

    for (int i = 0; i < grafo->grau[verticeInicial]; i++) {
        int temCiclo = buscaCiclo(grafo, grafo->arestas[verticeInicial][i], verticeInicial);
        if (grafo->grau[grafo->arestas[verticeInicial][i]] > 1 && !temCiclo) {
            if (grafo->PDVsCriticos[grafo->arestas[verticeInicial][i]] == 0) {
                grafo->PDVsCriticos[grafo->arestas[verticeInicial][i]] = 1;
                PDVsCriticosAdicionados++;
            }
        }
    }

    return PDVsCriticosAdicionados;
}

int main(void) {
    int numeroDePDV;
    while(scanf("%d", &numeroDePDV) == 1) {
        Grafo* grafo = criaGrafo(numeroDePDV, numeroDePDV - 1);
        int numeroPDVOrigem;
        for (int i = 0; i < numeroDePDV; i++) {

            int numeroPDVDestino;
            char lixo = 0;

            scanf("%d ", &numeroPDVOrigem);

            if (numeroPDVOrigem == 0)
                break;

            while ( scanf("%d%c", &numeroPDVDestino, &lixo) != EOF) {

                insereAresta(grafo, numeroPDVOrigem - 1, numeroPDVDestino - 1);

                if (lixo == '\n')
                    break;
            }
        }
        if (numeroDePDV) {
            int numeroPDVCritico = 0;
            for (int i = 0; i < grafo->numeroVertices; i++)
                numeroPDVCritico += buscaProfundidade(grafo, i);
            printf("%d\n", numeroPDVCritico);
        }
        liberaGrafo(grafo);
    }
    return 0;
}