// Tabela Hash com lista encadeada
#include <stdio.h>

typedef struct no {
    int chave;
    struct no* proximoNo;
} No;

typedef struct lista {
    No* primeiroNo;
    int tamanho;
} Lista;

void iniciaLista (Lista* lista) {
    lista->primeiroNo = NULL;
    lista->tamanho = 0;
    return;
}

void insereNaLista(Lista *lista, int valor) {
    No* novoNo = malloc(sizeof(No));

    if (!novoNo) {
        printf("Deu ruim");
        return;
    } else {
        novoNo->chave = valor;
        novoNo->proximoNo = lista->primeiroNo;
        lista->primeiroNo = novoNo;
        lista->tamanho += 1;
    }
}

int buscaNaLista(Lista* lista, int valor) {
    No* aux = lista->primeiroNo;
    while(aux && aux->chave != valor)
        aux = aux->proximoNo;

    if (aux) {
        return aux->chave;
    } else {
        return -1;
    }
}

void imprimeLista(Lista* lista) {
    No* aux = lista->primeiroNo;
    printf(" Tam: %d ", lista->tamanho);
    while(aux) {
        printf("%d ", aux->chave);
        aux = aux->proximoNo;
    }

}

void iniciaTabela (Lista tabela[]) {
    for (int i = 0; i < 31; i++) {
        iniciaLista(&tabela[i]);
    }
    return;
}

int funcaoHash (int valor) {
    return valor % 31;
}

void inserir (Lista tabela[], int valor) {
    int chave = funcaoHash(valor);

    insereNaLista(&tabela[chave], valor);
}

void imprimir (Lista tabela[]) {
    for (int i = 0; i < 31; i++) {
        printf("%d = ", i);
        imprimeLista(&tabela[i]);
        printf("\n");

    }
    printf("--------------\n");
}

int busca (Lista tabela[], int valor) {
    int chave = funcaoHash(valor);
    return buscaNaLista(&tabela[chave], valor);
}

int main() {
    Lista tabela[31];
    
    iniciaTabela(tabela);
    inserir(tabela, 30);
    inserir(tabela, 3);
    inserir(tabela, 16);
    inserir(tabela, 22);
    inserir(tabela, 17);
    imprimir(tabela);
    busca(tabela, 3) != -1 ? printf("Encontrou\n") : printf("Nao encontrou\n");

    return 0;
}


/* 
// Tabela Hash com soondagem
#include <stdio.h>

void iniciaTabela (int tabela[]) {
    for (int i = 0; i < 31; i++) {
        tabela[i] = -1;
    }
    return;
}

int funcaoHash (int valor) {
    return valor % 31;
}

void inserir (int tabela[], int valor) {
    int chave = funcaoHash(valor);

    while (tabela[chave] != -1) {
        chave = funcaoHash(chave + 1);
    }

    tabela[chave] = valor;
}

void imprimir (int tabela[]) {
    for (int i = 0; i < 31; i++) {
        printf("%d = %d\n", i, tabela[i]);
    }
    printf("--------------\n");
}

int busca (int tabela[], int valor) {
    int chave = funcaoHash(valor);

    while (tabela[chave] != -1) { 
        if (tabela[chave] == valor) {
            return chave;
        } else {
            chave = funcaoHash(chave + 1);
        }
    }
    return -1;
}

int main() {
    int tabela[31];
    
    iniciaTabela(tabela);
    inserir(tabela, 30);
    inserir(tabela, 3);
    inserir(tabela, 16);
    inserir(tabela, 22);
    inserir(tabela, 17);
    imprimir(tabela);
    busca(tabela, 3) != -1 ? printf("Encontrou\n") : printf("Nao encontrou\n");

    return 0;
} */