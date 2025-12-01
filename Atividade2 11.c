#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---- Estrutura da Sala (nó da árvore) ----
typedef struct Sala {
    char nome[50];
    struct Sala *esq;  // caminho à esquerda
    struct Sala *dir;  // caminho à direita
} Sala;

// ---- Criar uma sala  ----
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

// ---- Explorar a árvore da mansão ----
void explorarSalas(Sala* atual) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está na sala: **%s**\n", atual->nome);

        // se for uma sala final (folha)
        if (atual->esq == NULL && atual->dir == NULL) {
            printf("Este é um cômodo sem saídas... Fim do caminho!\n");
            return;
        }

        printf("Escolha seu caminho:\n");
        if (atual->esq) printf("  (e) Ir para a esquerda -> %s\n", atual->esq->nome);
        if (atual->dir) printf("  (d) Ir para a direita  -> %s\n", atual->dir->nome);
        printf("  (s) Sair da exploração\n> ");

        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esq != NULL) {
            atual = atual->esq;
        } 
        else if (escolha == 'd' && atual->dir != NULL) {
            atual = atual->dir;
        }
        else if (escolha == 's') {
            printf("\nVocê decidiu voltar e parar a exploração.\n");
            return;
        }
        else {
            printf("Opção inválida!\n");
        }
    }
}

// ---- Montagem fixa da mansão ----
/*
    Exemplo de estrutura da mansão:

                    Hall de Entrada
                   /               \
         Corredor Leste        Corredor Oeste
            /       \             /        \
      Biblioteca  Sala de Música  Armário  Cozinha

*/
Sala* montarMansao() {
    Sala* hall = criarSala("Hall de Entrada");

    hall->esq = criarSala("Corredor Leste");
    hall->dir = criarSala("Corredor Oeste");

    hall->esq->esq = criarSala("Biblioteca");
    hall->esq->dir = criarSala("Sala de Música");

    hall->dir->esq = criarSala("Armário Antigo");
    hall->dir->dir = criarSala("Cozinha");

    return hall;
}

// ---- MAIN ----
int main() {
    Sala* mansao = montarMansao();

    printf("=== Exploração da Mansão Assombrada ===\n");
    explorarSalas(mansao);

    return 0;
}//TO CANSADO JEFREY TO CANSADO
