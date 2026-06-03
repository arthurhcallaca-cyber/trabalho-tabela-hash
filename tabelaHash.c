#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10

typedef struct No {
    char palavra[50];
    char definicao[200];
    struct No *prox;
} No;

No *tabela[TAM];

void inicializarTabela() {
    for (int i = 0; i < TAM; i++) {
        tabela[i] = NULL;
    }
}

int hash(char *palavra) {
    int soma = 0;

    while (*palavra) {
        soma += *palavra;
        palavra++;
    }

    return soma % TAM;
}

void inserir(char palavra[], char definicao[]) {

    int indice = hash(palavra);

    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL) {
        printf("\nErro de alocacao de memoria!\n");
        return;
    }

    strcpy(novo->palavra, palavra);
    strcpy(novo->definicao, definicao);

    novo->prox = tabela[indice];
    tabela[indice] = novo;

    printf("\nPalavra inserida com sucesso!\n");
}

void buscar(char palavra[]) {

    int indice = hash(palavra);

    No *aux = tabela[indice];

    while (aux != NULL) {

        if (strcmp(aux->palavra, palavra) == 0) {

            printf("\nPalavra encontrada!");
            printf("\nPalavra: %s", aux->palavra);
            printf("\nDefinicao: %s\n", aux->definicao);

            return;
        }

        aux = aux->prox;
    }

    printf("\nPalavra nao encontrada!\n");
}

void removerPalavra(char palavra[]) {

    int indice = hash(palavra);

    No *atual = tabela[indice];
    No *anterior = NULL;

    while (atual != NULL &&
           strcmp(atual->palavra, palavra) != 0) {

        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("\nPalavra nao encontrada!\n");
        return;
    }

    if (anterior == NULL)
        tabela[indice] = atual->prox;
    else
        anterior->prox = atual->prox;

    free(atual);

    printf("\nPalavra removida com sucesso!\n");
}

void exibirTabela() {

    printf("\n========== TABELA HASH ==========\n");

    for (int i = 0; i < TAM; i++) {

        printf("[%d] -> ", i);

        No *aux = tabela[i];

        while (aux != NULL) {

            printf("(%s) -> ", aux->palavra);
            aux = aux->prox;
        }

        printf("NULL\n");
    }
}

int quantidadeElementos() {

    int total = 0;

    for (int i = 0; i < TAM; i++) {

        No *aux = tabela[i];

        while (aux != NULL) {
            total++;
            aux = aux->prox;
        }
    }

    return total;
}

int contarColisoes() {

    int colisoes = 0;

    for (int i = 0; i < TAM; i++) {

        int contador = 0;

        No *aux = tabela[i];

        while (aux != NULL) {
            contador++;
            aux = aux->prox;
        }

        if (contador > 1)
            colisoes += (contador - 1);
    }

    return colisoes;
}

float fatorCarga() {

    return (float)quantidadeElementos() / TAM;
}

int maiorLista() {

    int maior = 0;

    for (int i = 0; i < TAM; i++) {

        int contador = 0;

        No *aux = tabela[i];

        while (aux != NULL) {
            contador++;
            aux = aux->prox;
        }

        if (contador > maior)
            maior = contador;
    }

    return maior;
}

void exibirEstatisticas() {

    printf("\n========== ESTATISTICAS ==========\n");

    printf("Quantidade de elementos: %d\n",
           quantidadeElementos());

    printf("Quantidade de colisoes: %d\n",
           contarColisoes());

    printf("Fator de carga: %.2f\n",
           fatorCarga());

    printf("Maior lista encadeada: %d\n",
           maiorLista());
}

void liberarMemoria() {

    for (int i = 0; i < TAM; i++) {

        No *aux = tabela[i];

        while (aux != NULL) {

            No *temp = aux;

            aux = aux->prox;

            free(temp);
        }
    }
}

int main() {

    inicializarTabela();

    int opcao;

    char palavra[50];
    char definicao[200];

    do {

        printf("\n=================================");
        printf("\n DICIONARIO - TABELA HASH");
        printf("\n=================================");
        printf("\n1 - Inserir palavra");
        printf("\n2 - Buscar palavra");
        printf("\n3 - Remover palavra");
        printf("\n4 - Exibir tabela hash");
        printf("\n5 - Exibir estatisticas");
        printf("\n0 - Sair");
        printf("\nOpcao: ");
        scanf("%d", &opcao);

        getchar();

        switch (opcao) {

            case 1:

                printf("\nDigite a palavra: ");
                fgets(palavra, sizeof(palavra), stdin);
                palavra[strcspn(palavra, "\n")] = '\0';

                if (strlen(palavra) == 0) { 
                    printf("\nErro: a palavra nao pode estar vazia!\n");
                    break;
                }

                printf("Digite a definicao: ");
                fgets(definicao, sizeof(definicao), stdin);
                definicao[strcspn(definicao, "\n")] = '\0';
                
                if (strlen(definicao) == 0) {
                    printf("\nErro: a definicao nao pode estar vazia!\n");
                    break;
                }
                inserir(palavra, definicao);
                break;

            case 2:

                printf("\nDigite a palavra a buscar: ");
                fgets(palavra, sizeof(palavra), stdin);
                palavra[strcspn(palavra, "\n")] = '\0';

                buscar(palavra);
                break;

            case 3:

                printf("\nDigite a palavra a remover: ");
                fgets(palavra, sizeof(palavra), stdin);
                palavra[strcspn(palavra, "\n")] = '\0';

                removerPalavra(palavra);
                break;

            case 4:
                exibirTabela();
                break;

            case 5:
                exibirEstatisticas();
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    liberarMemoria();

    return 0;
}
