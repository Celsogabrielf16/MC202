#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char tipoDado;
    union {
        int d;
        float f;
        char c;
        char s[128];
    } dado;
    struct node* proximoNode;
} node;

typedef struct lista {
    int numeroDeNodes;
    node* primeiroNode;
} lista;

void limpaMemoria(lista* lista) {
    node* apontadorNodeAtual = lista->primeiroNode;
    while (lista->numeroDeNodes != 0) {
        lista->primeiroNode = apontadorNodeAtual->proximoNode;
        free(apontadorNodeAtual);
        apontadorNodeAtual = lista->primeiroNode;
        lista->numeroDeNodes -= 1;
    }
    free(lista);
    return;
}

lista* criaListaEncadeada(lista* lista) {
    if (lista != NULL)
        limpaMemoria(lista);
    
    lista = malloc(sizeof(lista));
    if (lista == NULL)
        return NULL;

    lista->numeroDeNodes = 0;
    lista->primeiroNode = NULL;

    return lista;
}

// Insere um node ao fim da lista, com o dado sendo do tipo desejado
void insereNaLista(lista* lista) {
    char tipoDado;
    scanf(" %c", &tipoDado);

    node* novoNode = malloc(sizeof(node));
    novoNode->proximoNode = NULL;

    // Recebe o dado dependendo do tipo e o adiciona ao no
    if (tipoDado == 'd') {
        scanf(" %d", &novoNode->dado.d);
        novoNode->tipoDado = 'd';
    } else if (tipoDado == 'f') {
        scanf(" %f", &novoNode->dado.f);
        novoNode->tipoDado = 'f';
    } else if (tipoDado == 'c') {
        scanf(" %c", &novoNode->dado.c);
        novoNode->tipoDado = 'c';
    } else if (tipoDado == 's') {
        scanf(" %128[^\n]", novoNode->dado.s);
        novoNode->tipoDado = 's';
    }

    // Se a lista tiver 0 nodes, significa que vamos adicionar o primeiro, se nao percorremos ate o ultimo node e adicionamos o proximo apos o mesmo
    if (lista->numeroDeNodes == 0) {
        lista->primeiroNode = novoNode;
    } else {
        node* apontadorNodeAtual = lista->primeiroNode;
        for (int i = 1; i < lista->numeroDeNodes; i++)  {
            apontadorNodeAtual = apontadorNodeAtual->proximoNode;
        }
        apontadorNodeAtual->proximoNode = novoNode;
    }
    lista->numeroDeNodes += 1;
    return;
}

void imprimeLista(lista* lista) {
    node* apontadorNodeAtual = lista->primeiroNode;
    for (int i = 0; i < lista->numeroDeNodes; i ++) {
        if (apontadorNodeAtual->tipoDado == 'd') {
            printf("%d ", apontadorNodeAtual->dado.d);
        } else if (apontadorNodeAtual->tipoDado == 'f') {
            printf("%.4f ", apontadorNodeAtual->dado.f);
        } else if (apontadorNodeAtual->tipoDado == 'c') {
            printf("%c ", apontadorNodeAtual->dado.c);
        } else if (apontadorNodeAtual->tipoDado == 's') {
            printf("%s ", apontadorNodeAtual->dado.s);
        }
        apontadorNodeAtual = apontadorNodeAtual->proximoNode;
    }
    printf("\n");
    return;
}

void reverteLista(lista* lista) {
    int posicaoI, posicaoJ;
    scanf(" %d %d", &posicaoI, &posicaoJ);

    // Apontadores auxilares para nao perdemos a posicao de nenhum dado
    node* apontadorNodeDaPosicaoAnteriorAoI = NULL;
    node* apontadorNodeDaPosicaoI = NULL;
    node* apontadorNodeDaPosicaoJ = NULL;
    node* apontadorNodeAtual = lista->primeiroNode;

    // Percorre a lista encontrando os nodes que desejamos
    for (int i = 0; i < lista->numeroDeNodes; i ++) {
         if (posicaoI == i + 1){
            apontadorNodeDaPosicaoAnteriorAoI = apontadorNodeAtual;
        }
        
        if (posicaoI == i) {
            apontadorNodeDaPosicaoI = apontadorNodeAtual;
        }
        
        if (posicaoJ == i) {
            apontadorNodeDaPosicaoJ = apontadorNodeAtual;
        }
        apontadorNodeAtual = apontadorNodeAtual->proximoNode;
    }

    node* apontadorParaProximo = apontadorNodeDaPosicaoI->proximoNode;
    node* apontadorParaUltimo = apontadorNodeDaPosicaoJ->proximoNode;

    // Percorre a sub lista de I ate J, onde I vai indo para o proximo ate chegar ao J
    for (int i = 0; i < posicaoJ - posicaoI; i++) {
        apontadorNodeDaPosicaoI->proximoNode = apontadorParaUltimo;
        apontadorParaUltimo = apontadorNodeDaPosicaoI;
        apontadorNodeDaPosicaoI = apontadorParaProximo;
        apontadorParaProximo = apontadorNodeDaPosicaoI->proximoNode;
    }

    apontadorNodeDaPosicaoJ->proximoNode = apontadorParaUltimo;

    // Agora falta apenas apontar o node inicialmente anterior ao node da posicao I para o node da posicao J que agora é o primeiro da sublista revertida
    if (posicaoI == 0) {
        lista->primeiroNode = apontadorNodeDaPosicaoJ;
    } else {
        apontadorNodeDaPosicaoAnteriorAoI->proximoNode = apontadorNodeDaPosicaoJ;
    }
    return;
}

void transpoeLista(lista* lista) {
    int posicaoI, posicaoJ, posicaoK;
    scanf(" %d %d %d", &posicaoI, &posicaoJ, &posicaoK);

    // Apontadores auxilares para nao perdemos a posicao de nenhum dado
    node* apontadorNodeDaPosicaoAnteriorAoI = NULL;
    node* apontadorNodeDaPosicaoI = NULL;
    node* apontadorNodeDaPosicaoJ = NULL;
    node* apontadorNodeDaPosicaoK = NULL;
    node* apontadorNodeAtual = lista->primeiroNode;

    // Percorre a lista encontrando os nodes que desejamos
    for (int i = 0; i < lista->numeroDeNodes; i ++) {
         if (posicaoI == i + 1){
            apontadorNodeDaPosicaoAnteriorAoI = apontadorNodeAtual;
        }
        
        if (posicaoI == i) {
            apontadorNodeDaPosicaoI = apontadorNodeAtual;
        }
        
        if (posicaoJ == i) {
            apontadorNodeDaPosicaoJ = apontadorNodeAtual;
        }
        
        if (posicaoK == i) {
            apontadorNodeDaPosicaoK = apontadorNodeAtual;
        }

        apontadorNodeAtual = apontadorNodeAtual->proximoNode;
    }

    // Inicialmente fechamos a lista "removendo" a sublista de I a J
    if (posicaoI == 0) {
        lista->primeiroNode = apontadorNodeDaPosicaoJ->proximoNode;
    } else {
        apontadorNodeDaPosicaoAnteriorAoI->proximoNode = apontadorNodeDaPosicaoJ->proximoNode;
    }

    // Agora recolocamos a sublista de I a J a direita do node da posicao K caso o mesmo seja diferente de -1, se nao colocamos na primeira posicao da lista
    if (posicaoK == -1) {
        apontadorNodeDaPosicaoJ->proximoNode = lista->primeiroNode;
        lista->primeiroNode = apontadorNodeDaPosicaoI;
    } else {
        apontadorNodeDaPosicaoJ->proximoNode = apontadorNodeDaPosicaoK->proximoNode;
        apontadorNodeDaPosicaoK->proximoNode = apontadorNodeDaPosicaoI;
    }
    return;
}

int main(void) {
    char operacao;
    lista* listaEncadeada = NULL;
    while (scanf("%c", &operacao) == 1) {
        if (operacao == 'c') {
            listaEncadeada = criaListaEncadeada(listaEncadeada);
        } else if (operacao == 'i') {
            insereNaLista(listaEncadeada);
        } else if (operacao == 'r') {
            reverteLista(listaEncadeada);
        } else if (operacao == 't') {
            transpoeLista(listaEncadeada);
        } else if (operacao == 'p') {
            imprimeLista(listaEncadeada);
        } else if (operacao == 'f') {
            limpaMemoria(listaEncadeada);
            break;
        }
    }
    return 0;
}