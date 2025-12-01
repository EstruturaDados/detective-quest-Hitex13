#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  // ESTRUTURA DA ÁRVORE DA MANSÃO

typedef struct Sala {
    char nome[50];
    char pista[50];          // pista encontrada nesta sala (se existir)
    struct Sala *esq;
    struct Sala *dir;
} Sala;

Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);

    if (pista)
        strcpy(nova->pista, pista);
    else
        strcpy(nova->pista, "");

    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}


 //ÁRVORE DE BUSCA (BST) DE PISTAS


typedef struct NodoPista {
    char pista[50];
    struct NodoPista *esq;
    struct NodoPista *dir;
} NodoPista;

NodoPista* criarNodoPista(char* pista) {
    NodoPista* novo = (NodoPista*) malloc(sizeof(NodoPista));
    strcpy(novo->pista, pista);
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

NodoPista* inserirPista(NodoPista* raiz, char* pista) {
    if (raiz == NULL) {
        return criarNodoPista(pista);
    }
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esq = inserirPista(raiz->esq, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->dir = inserirPista(raiz->dir, pista);
    }
    return raiz;
}

void listarPistasEmOrdem(NodoPista* raiz) {
    if (raiz == NULL) return;

    listarPistasEmOrdem(raiz->esq);
    printf(" - %s\n", raiz->pista);
    listarPistasEmOrdem(raiz->dir);
}

    //   EXPLORAÇÃO DA MANSÃO


void explorarSalas(Sala* atual, NodoPista** arvorePistas) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está na sala: **%s**\n", atual->nome);

        // Se a sala tiver uma pista, adiciona na BST
        if (strlen(atual->pista) > 0) {
            printf("Você encontrou uma pista: \"%s\"!\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        if (atual->esq == NULL && atual->dir == NULL) {
            printf("Este é um cômodo sem saídas... Fim do caminho!\n");
            return;
        }

        printf("Opções:\n");
        if (atual->esq) printf("  (e) Ir para a esquerda -> %s\n", atual->esq->nome);
        if (atual->dir) printf("  (d) Ir para a direita  -> %s\n", atual->dir->nome);
        printf("  (p) Listar pistas encontradas\n");
        printf("  (s) Sair da exploração\n> ");

        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esq != NULL) {
            atual = atual->esq;
        } 
        else if (escolha == 'd' && atual->dir != NULL) {
            atual = atual->dir;
        }
        else if (escolha == 'p') {
            printf("\n=== PISTAS ENCONTRADAS ===\n");
            listarPistasEmOrdem(*arvorePistas);
        }
        else if (escolha == 's') {
            printf("\nVocê saiu da exploração.\n");
            return;
        }
        else {
            printf("Opção inválida!\n");
        }
    }
}

   //   MONTAGEM DA MANSÃO (FIXA)

Sala* montarMansao() {
    Sala* hall = criarSala("Hall de Entrada", "");

    hall->esq = criarSala("Corredor Leste", "");
    hall->dir = criarSala("Corredor Oeste", "Chave de Ferro");

    hall->esq->esq = criarSala("Biblioteca", "Página queimada");
    hall->esq->dir = criarSala("Sala de Música", "");

    hall->dir->esq = criarSala("Armário Antigo", "Diário rasgado");
    hall->dir->dir = criarSala("Cozinha", "");

    return hall;
}

//               MAIN

int main() {
    Sala* mansao = montarMansao();
    NodoPista* arvorePistas = NULL;

    printf("=== Nível Aventureiro: Mansão + BST de Pistas ===\n");
    explorarSalas(mansao, &arvorePistas);

    printf("\nPistas coletadas durante a exploração:\n");
    listarPistasEmOrdem(arvorePistas);

    return 0;
}
