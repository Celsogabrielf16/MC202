#include <stdio.h>
#include <stdlib.h>

typedef struct Grafo {
    int numeroVertices;
    int** arestas;
    int* grau;
    int* PDVsCriticos;
} Grafo;

// Cria um grafo, representado por uma lista de aadjacencias
Grafo* criaGrafo(int numeroVertices) {
    Grafo* novoGrafo = (Grafo*) malloc(sizeof(Grafo));
    if (!novoGrafo)
        return NULL;

    novoGrafo->numeroVertices = numeroVertices;
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
        novoGrafo->arestas[i] = (int*) malloc((numeroVertices - 1) * sizeof(int));
        if (!novoGrafo->arestas[i])
            return NULL;
    }

    return novoGrafo;
}

// Libera o grafo dado
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

// Insere uma aresta no grafo sem repeticao
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

// Funcao recursiva que verifica se o vertice dado faz parte de um ciclo, ou seja tem como chegar nele apartir de dois ou mais vizinhos diferentes
int encontraCicloRec (Grafo* grafo, int verticeAtual, int verticeAnterior, int* visitados) {
    visitados[verticeAtual] = 1;
    int encontrouCiclo = 0;

    for(int i = 0; i < grafo->grau[verticeAtual]; i++) {
        int verticeVizinho = grafo->arestas[verticeAtual][i];
        if (visitados[verticeVizinho] == 0) {
            encontrouCiclo = encontraCicloRec (grafo, verticeVizinho, verticeAtual, visitados);
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

// Verifica se podemos chegar de um vizinho a outro sem passar pelo vertice em questao
int encontraPasseioEntreVizinhos (Grafo* grafo, int verticeAtual, int verticeMeta, int* verticesVisitados) {
    verticesVisitados[verticeAtual] = 1;
    int encontrouCaminho = 0;

    for(int i = 0; i < grafo->grau[verticeAtual]; i++) {
        int verticeVizinho = grafo->arestas[verticeAtual][i];
        if (verticeVizinho == verticeMeta) {
            return 1;
        } else if (verticesVisitados[verticeVizinho] == 0) {
            encontrouCaminho = encontraPasseioEntreVizinhos(grafo, verticeVizinho, verticeMeta, verticesVisitados);
            if (encontrouCaminho) {
                break;
            }
        }
    }

    return encontrouCaminho;
}

// Verifica se o vertice em questao faz parte de um ciclo, se ele faz verificamos se consiguimos chegar em um vizinho apartir de outro
int encontraCiclo(Grafo* grafo, int verticeAtual, int verticeInicial) {
    int visitados[grafo->numeroVertices], encontrouCiclo = 0;
    for (int i = 0; i < grafo->numeroVertices; i++)
        visitados[i] = 0;

    // Marcamos o vertice inicial como 2, pois se encontrarmos o mesmo no percurso, encontramos um ciclo
    visitados[verticeInicial] = 2;
    encontrouCiclo = encontraCicloRec(grafo, verticeAtual, verticeInicial, visitados);

    if (encontrouCiclo) {
        for(int i = 0; i < grafo->grau[verticeAtual]; i++) {
            int verticesVisitados[grafo->numeroVertices];
            for (int i = 0; i < grafo->numeroVertices; i++)
                verticesVisitados[i] = 0;

            verticesVisitados[verticeAtual] = 1;
            int vizinhoPosicaoI = grafo->arestas[verticeAtual][i];
            int vizinhoPosicaoIMais1 = grafo->arestas[verticeAtual][(i + 1) % grafo->grau[verticeAtual]];
            int encontrouPasseio = encontraPasseioEntreVizinhos(grafo, vizinhoPosicaoI, vizinhoPosicaoIMais1, verticesVisitados);

            // Se nao for encontrado um passeio entre os vizinho sem passar pelo vertice atual ele é um PDV mesmo fazendo parte de um ciclo
            if (!encontrouPasseio) {
                encontrouCiclo = 0;
                break;
            }
        }
    }

    return encontrouCiclo;
}

// Encontra PDVs criticos e retorna quantos encontrou apartir do vertice inicial, ou seja, quantos vizinhos do vertice dado sao criticos
int encontraPDVsCriticos(Grafo* grafo, int verticeInicial) {
    int PDVsCriticosAdicionados = 0;

    for (int i = 0; i < grafo->grau[verticeInicial]; i++) {
        int encontrouCiclo = encontraCiclo(grafo, grafo->arestas[verticeInicial][i], verticeInicial);
        if (grafo->grau[grafo->arestas[verticeInicial][i]] > 1 && !encontrouCiclo) {
            // Se o vizinho ainda nao foi marcado como PDV, marcamos e consideramos o mesmo
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
        Grafo* grafo = criaGrafo(numeroDePDV);
        int numeroPDVOrigem;
        for (int i = 0; i < numeroDePDV; i++) {

            int numeroPDVDestino;
            char lixo = 0;

            scanf("%d ", &numeroPDVOrigem);

            if (numeroPDVOrigem == 0)
                break;

            while (scanf("%d%c", &numeroPDVDestino, &lixo) != EOF) {
                insereAresta(grafo, numeroPDVOrigem - 1, numeroPDVDestino - 1);

                if (lixo == '\n')
                    break;
            }
        }

        if (numeroDePDV) {
            int numeroPDVCritico = 0;
            for (int i = 0; i < grafo->numeroVertices; i++)
                numeroPDVCritico += encontraPDVsCriticos(grafo, i);
            printf("%d\n", numeroPDVCritico);
        }

        liberaGrafo(grafo);
    }
    return 0;
}