#include <stdio.h>
#include <stdlib.h>
#include <string.h>

               // ESTRUTURA DA ÁRVORE DA MANSÃO

typedef struct Sala {
    char nome[50];
    char pista[50];
    struct Sala *esq, *dir;
} Sala;

Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista ? pista : "");
    nova->esq = nova->dir = NULL;
    return nova;
}

              //  ÁRVORE DE BUSCA (BST) DE PISTAS

typedef struct NodoPista {
    char pista[50];
    struct NodoPista *esq, *dir;
} NodoPista;

NodoPista* criarNodoPista(char* pista) {
    NodoPista* novo = (NodoPista*) malloc(sizeof(NodoPista));
    strcpy(novo->pista, pista);
    novo->esq = novo->dir = NULL;
    return novo;
}

NodoPista* inserirPista(NodoPista* raiz, char* pista) {
    if (!raiz) return criarNodoPista(pista);
    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserirPista(raiz->esq, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->dir = inserirPista(raiz->dir, pista);
    return raiz;
}

void listarPistas(NodoPista* raiz) {
    if (!raiz) return;
    listarPistas(raiz->esq);
    printf(" - %s\n", raiz->pista);
    listarPistas(raiz->dir);
}

           //           TABELA HASH DE SUSPEITOS

#define TAM_HASH 10

typedef struct HashNode {
    char pista[50];
    char suspeito[50];
    struct HashNode* prox;
} HashNode;

HashNode* tabelaHash[TAM_HASH];

/* Função hash simples */
int hashFunc(const char* str) {
    int soma = 0;
    for (int i = 0; str[i] != '\0'; i++)
        soma += str[i];
    return soma % TAM_HASH;
}

void inserirNaHash(char* pista, char* suspeito) {
    int h = hashFunc(pista);

    HashNode* novo = (HashNode*) malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabelaHash[h];
    tabelaHash[h] = novo;
}

void mostrarTabelaHash() {
    printf("\n=== ASSOCIAÇÕES PISTA → SUSPEITO ===\n");
    for (int i = 0; i < TAM_HASH; i++) {
        HashNode* aux = tabelaHash[i];
        if (aux) {
            printf("\n[Hash %d]\n", i);
        }
        while (aux) {
            printf("Pista: %-20s → Suspeito: %s\n", aux->pista, aux->suspeito);
            aux = aux->prox;
        }
    }
}

char* suspeitoMaisCitado() {
    static char maisCitado[50];
    int maiorFreq = 0;

    // Contagem de suspeitos
    typedef struct {
        char nome[50];
        int cont;
    } SusCont;

    SusCont lista[20];
    int usados = 0;

    for (int i = 0; i < TAM_HASH; i++) {
        HashNode* aux = tabelaHash[i];
        while (aux) {
            int encontrado = 0;

            for (int j = 0; j < usados; j++) {
                if (strcmp(lista[j].nome, aux->suspeito) == 0) {
                    lista[j].cont++;
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado) {
                strcpy(lista[usados].nome, aux->suspeito);
                lista[usados].cont = 1;
                usados++;
            }

            aux = aux->prox;
        }
    }

    // Descobrir o mais citado
    for (int i = 0; i < usados; i++) {
        if (lista[i].cont > maiorFreq) {
            maiorFreq = lista[i].cont;
            strcpy(maisCitado, lista[i].nome);
        }
    }

    return maisCitado;
}

                       EXPLORAÇÃO DA MANSÃO
    

void explorarSalas(Sala* atual, NodoPista** bst) {
    char opc;

    while (atual) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Você encontrou a pista: \"%s\"!\n", atual->pista);
            *bst = inserirPista(*bst, atual->pista);
        }

        if (!atual->esq && !atual->dir) {
            printf("Fim do caminho!\n");
            return;
        }

        printf("\n(e) Ir para esquerda\n(d) Ir para direita\n(s) Sair\n> ");
        scanf(" %c", &opc);

        if (opc == 'e' && atual->esq) atual = atual->esq;
        else if (opc == 'd' && atual->dir) atual = atual->dir;
        else if (opc == 's') return;
        else printf("Opção inválida!\n");
    }
}


                 //  MONTAGEM FIXA DA MANSÃO

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

                  //          MAIN

int main() {
    // Inicializa tabela hash
    for (int i = 0; i < TAM_HASH; i++)
        tabelaHash[i] = NULL;

    Sala* mansao = montarMansao();
    NodoPista* bst = NULL;

    printf("=== Nível Mestre: Suspeitos e Solução com Hash Table ===\n");

    explorarSalas(mansao, &bst);

    printf("\n=== PISTAS COLETADAS ===\n");
    listarPistas(bst);

    // Conectar pistas → suspeitos automaticamente
    //
    inserirNaHash("Chave de Ferro", "Sr. Corvus");
    inserirNaHash("Página queimada", "Dona Mirella");
    inserirNaHash("Diário rasgado", "Sr. Corvus");

    mostrarTabelaHash();

    printf("\n>>> Suspeito mais citado: ***%s***\n",
           suspeitoMaisCitado());

    return 0;
}//Sem Palavras 

