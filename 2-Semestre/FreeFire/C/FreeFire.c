/* mochila_mestre.c
   Mescla: MOCHILA (vetor + lista encadeada) + MÓDULO MESTRE (ordenacoes, busca binaria)
   Compile: gcc -o jogo mochila_mestre.c -std=c99
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
static void Sleep(unsigned int ms) { usleep(ms * 1000); }
#endif

/* ===========================
   1) MOCHILA - tipos & dados
   =========================== */

/* Representação de um item no inventário */
typedef struct {
    char tipo[20];
    char nome[30];
    int quantidade;
} Item;

/* Nó para lista encadeada */
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

#define CAPACIDADE_VETOR 10

/* Listas de nomes válidos por categoria (dados do jogo) */
const char* submetralhadora[5]    = { "MP40", "P90", "UMP", "Thompson", "MP5" };
const char* rifles_assalto[5]     = { "AK-47", "M4A1", "SCAR", "FAMAS", "XM8" };
const char* rifles_de_precisao[5] = { "AWM", "Kar98K", "M24", "Treatment Sniper", "VSK94" };
const char* escopetas[5]          = { "M1887", "M1014", "SPAS12", "Charge Buster", "MAG-7" };
const char* pistolas[5]           = { "Desert Eagle", "M500", "G18", "USP", "Treatment Gun" };
const char* armas_brancas[5]      = { "Katana", "Panela", "Bastão", "Machado", "Foice" };
const char* consumiveis[4]        = { "Kit Médico", "Inalador", "Cogumelos", "Kit de Reparar" };

/* Contadores de busca (vetor/lista) */
long long comparacoes_busca_sequencial_vetor = 0;
long long comparacoes_busca_binaria_vetor = 0;
long long comparacoes_busca_sequencial_lista = 0;

/* Protótipos - Mochila */
void listar_opcoes(const char* lista[], int tamanho);
int nome_igual_ci(const char *a, const char *b);
void limpar_buffer();

void escolher_item_por_categoria(int opcao, char* destino_nome, char* destino_tipo);

/* Vetor */
void inserirItemVetor(Item* vetor, int* num);
int removerItemVetorPorNome(Item* vetor, int* num, const char* nome);
void listarItensVetor(Item* vetor, int num);
int buscarSequencialVetor(Item* vetor, int num, const char* nome);
void ordenarVetor(Item* vetor, int num);
int buscarBinariaVetor(Item* vetor, int num, const char* nome);

/* Lista */
void inserirItemLista(No** cabeça);
int removerItemListaPorNome(No** cabeça, const char* nome);
void listarItensLista(No* cabeça);
No* buscarSequencialLista(No* cabeça, const char* nome);
void liberarLista(No** cabeça);

void menu_mochila(); /* função que inicia a interface da mochila */

/* ---------------------------
   Implementação - mochilas
   --------------------------- */

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void listar_opcoes(const char* lista[], int tamanho) {
    int i;
    printf("\n------------------------------\n");
    for (i = 0; i < tamanho; i++) {
        printf(" %2d) %s\n", i, lista[i]);
    }
    printf("------------------------------\n");
}

int nome_igual_ci(const char *a, const char *b) {
    while (*a && *b) {
        char ca = tolower((unsigned char)*a);
        char cb = tolower((unsigned char)*b);
        if (ca != cb) return 0;
        a++; b++;
    }
    return tolower((unsigned char)*a) == tolower((unsigned char)*b);
}

/* Encapsula seleção de item por categoria */
void escolher_item_por_categoria(int opcao, char* destino_nome, char* destino_tipo) {
    int escolha = -1;
    switch (opcao) {
        case 0:
            strncpy(destino_tipo, "Item Extra", 19); destino_tipo[19] = '\0';
            printf("Digite o nome do item: ");
            scanf(" %29[^\n]", destino_nome);
            limpar_buffer();
            return;
        case 1:
            strcpy(destino_tipo, "Submetralhadora");
            do {
                listar_opcoes(submetralhadora, 5);
                printf("Escolha o número do item: ");
                if (scanf("%d", &escolha) != 1) escolha = -1;
                limpar_buffer();
                if (escolha < 0 || escolha >= 5) printf("Opção inválida! Tente novamente.\n");
            } while (escolha < 0 || escolha >= 5);
            strncpy(destino_nome, submetralhadora[escolha], 29);
            destino_nome[29] = '\0';
            return;
        case 2:
            strcpy(destino_tipo, "Rifle Assalto");
            do {
                listar_opcoes(rifles_assalto, 5);
                printf("Escolha o número do item: ");
                if (scanf("%d", &escolha) != 1) escolha = -1;
                limpar_buffer();
                if (escolha < 0 || escolha >= 5) printf("Opção inválida! Tente novamente.\n");
            } while (escolha < 0 || escolha >= 5);
            strncpy(destino_nome, rifles_assalto[escolha], 29);
            destino_nome[29] = '\0';
            return;
        case 3:
            strcpy(destino_tipo, "Rifle Precisao");
            do {
                listar_opcoes(rifles_de_precisao, 5);
                printf("Escolha o número do item: ");
                if (scanf("%d", &escolha) != 1) escolha = -1;
                limpar_buffer();
                if (escolha < 0 || escolha >= 5) printf("Opção inválida! Tente novamente.\n");
            } while (escolha < 0 || escolha >= 5);
            strncpy(destino_nome, rifles_de_precisao[escolha], 29);
            destino_nome[29] = '\0';
            return;
        case 4:
            strcpy(destino_tipo, "Escopeta");
            do {
                listar_opcoes(escopetas, 5);
                printf("Escolha o número do item: ");
                if (scanf("%d", &escolha) != 1) escolha = -1;
                limpar_buffer();
                if (escolha < 0 || escolha >= 5) printf("Opção inválida! Tente novamente.\n");
            } while (escolha < 0 || escolha >= 5);
            strncpy(destino_nome, escopetas[escolha], 29);
            destino_nome[29] = '\0';
            return;
        case 5:
            strcpy(destino_tipo, "Pistola");
            do {
                listar_opcoes(pistolas, 5);
                printf("Escolha o número do item: ");
                if (scanf("%d", &escolha) != 1) escolha = -1;
                limpar_buffer();
                if (escolha < 0 || escolha >= 5) printf("Opção inválida! Tente novamente.\n");
            } while (escolha < 0 || escolha >= 5);
            strncpy(destino_nome, pistolas[escolha], 29);
            destino_nome[29] = '\0';
            return;
        case 6:
            strcpy(destino_tipo, "Arma Branca");
            do {
                listar_opcoes(armas_brancas, 5);
                printf("Escolha o número do item: ");
                if (scanf("%d", &escolha) != 1) escolha = -1;
                limpar_buffer();
                if (escolha < 0 || escolha >= 5) printf("Opção inválida! Tente novamente.\n");
            } while (escolha < 0 || escolha >= 5);
            strncpy(destino_nome, armas_brancas[escolha], 29);
            destino_nome[29] = '\0';
            return;
        case 7:
            strcpy(destino_tipo, "Consumível");
            do {
                listar_opcoes(consumiveis, 4);
                printf("Escolha o número do item: ");
                if (scanf("%d", &escolha) != 1) escolha = -1;
                limpar_buffer();
                if (escolha < 0 || escolha >= 4) printf("Opção inválida! Tente novamente.\n");
            } while (escolha < 0 || escolha >= 4);
            strncpy(destino_nome, consumiveis[escolha], 29);
            destino_nome[29] = '\0';
            return;
        default:
            strcpy(destino_tipo, "Desconhecido");
            destino_nome[0] = '\0';
            return;
    }
}

/* ===== VETOR ===== */

void inserirItemVetor(Item* vetor, int* num) {
    if (*num >= CAPACIDADE_VETOR) {
        printf("\n>>> Inventário cheio (%d itens). Não é possível inserir mais.\n", CAPACIDADE_VETOR);
        listarItensVetor(vetor, *num);
        return;
    }

    int opcao = -1;
    char nome_temp[30];
    char tipo_temp[20];
    int quantidade = 0;

    while (opcao < 0 || opcao > 7) {
        printf("\n--- Categoria de item ---\n");
        printf(" 0) Item Extra\n 1) Submetralhadora\n 2) Rifle de Assalto\n 3) Rifle de Precisão\n");
        printf(" 4) Escopeta\n 5) Pistola\n 6) Arma Branca\n 7) Consumível\n");
        printf("Escolha a opção (0-7): ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            limpar_buffer();
            printf("Valor inválido! Tente novamente.\n");
            continue;
        }
        limpar_buffer();
        if (opcao < 0 || opcao > 7) {
            printf("Valor inválido! Tente novamente.\n");
        }
    }

    escolher_item_por_categoria(opcao, nome_temp, tipo_temp);

    do {
        printf("Quantidade (deve ser > 0): ");
        if (scanf("%d", &quantidade) != 1) {
            quantidade = 0;
            limpar_buffer();
        } else {
            limpar_buffer();
        }
        if (quantidade <= 0) {
            printf("Quantidade inválida! Informe um valor positivo.\n");
        }
    } while (quantidade <= 0);

    int pos = *num;
    strncpy(vetor[pos].tipo, tipo_temp, sizeof(vetor[pos].tipo)-1);
    vetor[pos].tipo[sizeof(vetor[pos].tipo)-1] = '\0';
    strncpy(vetor[pos].nome, nome_temp, sizeof(vetor[pos].nome)-1);
    vetor[pos].nome[sizeof(vetor[pos].nome)-1] = '\0';
    vetor[pos].quantidade = quantidade;
    (*num)++;

    printf("\n--- Item inserido ---\n");
    printf(" Tipo     : %s\n", vetor[pos].tipo);
    printf(" Nome     : %s\n", vetor[pos].nome);
    printf(" Quantidade: %d\n", vetor[pos].quantidade);
    printf("---------------------\n");

    listarItensVetor(vetor, *num);
}

int removerItemVetorPorNome(Item* vetor, int* num, const char* nome) {
    if (*num == 0) {
        printf("\n>>> Inventário vazio! Nada a remover.\n");
        return 0;
    }

    int i, encontrado = -1;
    for (i = 0; i < *num; i++) {
        if (nome_igual_ci(vetor[i].nome, nome)) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item '%s' não encontrado no inventário.\n", nome);
        return 0;
    }

    for (i = encontrado; i < (*num) - 1; i++) {
        vetor[i] = vetor[i + 1];
    }
    memset(&vetor[*num - 1], 0, sizeof(Item));
    (*num)--;

    printf("\n--- Item '%s' removido com sucesso ---\n", nome);
    listarItensVetor(vetor, *num);
    return 1;
}

void listarItensVetor(Item* vetor, int num) {
    int i;
    if (num == 0) {
        printf("\n-- Inventário vazio --\n");
        return;
    }
    printf("\n--- Itens na mochila (VETOR) ---\n");
    printf("Idx  Tipo         | Nome                 | Qty\n");
    printf("---- -------------+----------------------+-----\n");
    for (i = 0; i < num; i++) {
        printf(" %2d) %-12s | %-20s |  %2d\n", i, vetor[i].tipo, vetor[i].nome, vetor[i].quantidade);
    }
    printf("-------------------------------\n");
}

int buscarSequencialVetor(Item* vetor, int num, const char* nome) {
    comparacoes_busca_sequencial_vetor = 0;
    int i;
    for (i = 0; i < num; i++) {
        comparacoes_busca_sequencial_vetor++;
        if (nome_igual_ci(vetor[i].nome, nome)) {
            return i;
        }
    }
    return -1;
}

void ordenarVetor(Item* vetor, int num) {
    if (num <= 1) return;
    int i, j;
    Item tmp;
    for (i = 0; i < num - 1; i++) {
        for (j = 0; j < num - 1 - i; j++) {
            if (strcasecmp(vetor[j].nome, vetor[j+1].nome) > 0) {
                tmp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = tmp;
            }
        }
    }
}

/* Busca binária no vetor ordenado. Retorna índice ou -1. */
int buscarBinariaVetor(Item* vetor, int num, const char* nome) {
    comparacoes_busca_binaria_vetor = 0;
    int left = 0, right = num - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        comparacoes_busca_binaria_vetor++;
        int cmp = strcasecmp(vetor[mid].nome, nome);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

/* ===== LISTA ENCADEADA ===== */

void inserirItemLista(No** cabeça) {
    if (!cabeça) return;

    char nome_temp[30];
    char tipo_temp[20];
    int opcao = -1;
    int quantidade = 0;

    while (opcao < 0 || opcao > 7) {
        printf("\n--- Categoria de item ---\n");
        printf(" 0) Item Extra\n 1) Submetralhadora\n 2) Rifle de Assalto\n 3) Rifle de Precisão\n");
        printf(" 4) Escopeta\n 5) Pistola\n 6) Arma Branca\n 7) Consumível\n");
        printf("Escolha a opção (0-7): ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            limpar_buffer();
            printf("Valor inválido! Tente novamente.\n");
            continue;
        }
        limpar_buffer();
        if (opcao < 0 || opcao > 7) {
            printf("Valor inválido! Tente novamente.\n");
        }
    }

    escolher_item_por_categoria(opcao, nome_temp, tipo_temp);

    do {
        printf("Quantidade (deve ser > 0): ");
        if (scanf("%d", &quantidade) != 1) {
            quantidade = 0;
            limpar_buffer();
        } else {
            limpar_buffer();
        }
        if (quantidade <= 0) {
            printf("Quantidade inválida! Informe um valor positivo.\n");
        }
    } while (quantidade <= 0);

    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro de memória ao inserir item.\n");
        return;
    }
    strncpy(novo->dados.nome, nome_temp, sizeof(novo->dados.nome)-1);
    novo->dados.nome[sizeof(novo->dados.nome)-1] = '\0';
    strncpy(novo->dados.tipo, tipo_temp, sizeof(novo->dados.tipo)-1);
    novo->dados.tipo[sizeof(novo->dados.tipo)-1] = '\0';
    novo->dados.quantidade = quantidade;
    novo->proximo = NULL;

    if (*cabeça == NULL) {
        *cabeça = novo;
    } else {
        No* atual = *cabeça;
        while (atual->proximo) atual = atual->proximo;
        atual->proximo = novo;
    }

    printf("\n--- Item inserido na LISTA ---\n");
    printf(" Tipo     : %s\n", novo->dados.tipo);
    printf(" Nome     : %s\n", novo->dados.nome);
    printf(" Quantidade: %d\n", novo->dados.quantidade);
    printf("-------------------------------\n");
}

int removerItemListaPorNome(No** cabeça, const char* nome) {
    if (!cabeça || !*cabeça) {
        printf("\n>>> Lista vazia! Nada a remover.\n");
        return 0;
    }

    No* atual = *cabeça;
    No* anterior = NULL;

    while (atual) {
        if (nome_igual_ci(atual->dados.nome, nome)) {
            if (anterior == NULL) {
                *cabeça = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("\n--- Item '%s' removido da LISTA com sucesso ---\n", nome);
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item '%s' não encontrado na LISTA.\n", nome);
    return 0;
}

void listarItensLista(No* cabeça) {
    if (!cabeça) {
        printf("\n-- Lista vazia --\n");
        return;
    }
    printf("\n--- Itens na mochila (LISTA) ---\n");
    printf("Idx  Tipo         | Nome                 | Qty\n");
    printf("---- -------------+----------------------+-----\n");
    int idx = 0;
    No* atual = cabeça;
    while (atual) {
        printf(" %2d) %-12s | %-20s |  %2d\n", idx, atual->dados.tipo, atual->dados.nome, atual->dados.quantidade);
        atual = atual->proximo;
        idx++;
    }
    printf("-------------------------------\n");
}

No* buscarSequencialLista(No* cabeça, const char* nome) {
    comparacoes_busca_sequencial_lista = 0;
    No* atual = cabeça;
    while (atual) {
        comparacoes_busca_sequencial_lista++;
        if (nome_igual_ci(atual->dados.nome, nome)) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void liberarLista(No** cabeça) {
    if (!cabeça) return;
    No* atual = *cabeça;
    while (atual) {
        No* prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    *cabeça = NULL;
}

/* Menu da mochila (vetor + lista) */
void menu_mochila() {
    Item vetor[CAPACIDADE_VETOR];
    int contador_vetor = 0;
    memset(vetor, 0, sizeof(vetor));
    No* lista_cabeca = NULL;

    int estrutura = 0; // 0 = vetor, 1 = lista
    int opcao = -1;

    printf("\n=====================================\n");
    printf("       MOCHILA DE SOBREVIVÊNCIA       \n");
    printf("=====================================\n\n");

    while (1) {
        printf("Escolha a estrutura a usar:\n 1) Vetor (lista sequencial)\n 2) Lista encadeada\n 0) Voltar\nEscolha (1-2 ou 0): ");
        if (scanf("%d", &estrutura) != 1) {
            limpar_buffer();
            printf("Valor inválido!\n");
            continue;
        }
        limpar_buffer();
        if (estrutura == 0) { return; } /* volta ao menu principal */
        if (estrutura == 1) { estrutura = 0; break; } // vetor
        if (estrutura == 2) { estrutura = 1; break; } // lista
        printf("Escolha inválida! Escolha 1 ou 2.\n");
    }

    do {
        if (estrutura == 0) {
            printf("\n--- MODO: VETOR ---\n");
        } else {
            printf("\n--- MODO: LISTA ---\n");
        }
        printf("Itens na Mochila (Vetor): %d/%d\n", contador_vetor, CAPACIDADE_VETOR);
        printf(" 1) Adicionar Item (Loot)\n");
        printf(" 2) Remover Item por NOME\n");
        printf(" 3) Listar Itens na Mochila\n");
        printf(" 4) Buscar Item (busca sequencial)\n");
        if (estrutura == 0) {
            printf(" 5) Ordenar Vetor (por nome)\n");
            printf(" 6) Buscar Binária (vetor ordenado)\n");
            printf(" 7) Mostrar contadores de comparações\n");
        } else {
            printf(" 5) Mostrar contadores de comparações (lista)\n");
        }
        printf(" 8) Alternar estrutura (vetor/lista)\n");
        printf(" 0) Voltar\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            limpar_buffer();
        } else {
            limpar_buffer();
        }

        switch(opcao) {
            case 1:
                if (estrutura == 0) {
                    inserirItemVetor(vetor, &contador_vetor);
                } else {
                    inserirItemLista(&lista_cabeca);
                }
                break;

            case 2: {
                char nome_remover[30];
                printf("Digite o NOME do item a remover: ");
                scanf(" %29[^\n]", nome_remover);
                limpar_buffer();
                if (estrutura == 0) {
                    removerItemVetorPorNome(vetor, &contador_vetor, nome_remover);
                } else {
                    removerItemListaPorNome(&lista_cabeca, nome_remover);
                }
                break;
            }

            case 3:
                if (estrutura == 0) listarItensVetor(vetor, contador_vetor);
                else listarItensLista(lista_cabeca);
                break;

            case 4: {
                char nome_busca[30];
                printf("Digite o NOME do item a buscar: ");
                scanf(" %29[^\n]", nome_busca);
                limpar_buffer();
                if (estrutura == 0) {
                    clock_t t0 = clock();
                    int idx = buscarSequencialVetor(vetor, contador_vetor, nome_busca);
                    clock_t t1 = clock();
                    double ms = (double)(t1 - t0) / CLOCKS_PER_SEC * 1000.0;
                    if (idx >= 0) {
                        printf("Item encontrado (vetor):\n Tipo: %s\n Nome: %s\n Quantidade: %d\n", vetor[idx].tipo, vetor[idx].nome, vetor[idx].quantidade);
                    } else {
                        printf("Item '%s' não encontrado no vetor.\n", nome_busca);
                    }
                    printf("Comparações (busca sequencial - vetor): %lld. Tempo: %.3f ms\n", comparacoes_busca_sequencial_vetor, ms);
                } else {
                    clock_t t0 = clock();
                    No* no = buscarSequencialLista(lista_cabeca, nome_busca);
                    clock_t t1 = clock();
                    double ms = (double)(t1 - t0) / CLOCKS_PER_SEC * 1000.0;
                    if (no) {
                        printf("Item encontrado (lista):\n Tipo: %s\n Nome: %s\n Quantidade: %d\n", no->dados.tipo, no->dados.nome, no->dados.quantidade);
                    } else {
                        printf("Item '%s' não encontrado na lista.\n", nome_busca);
                    }
                    printf("Comparações (busca sequencial - lista): %lld. Tempo: %.3f ms\n", comparacoes_busca_sequencial_lista, ms);
                }
                break;
            }

            case 5:
                if (estrutura == 0) {
                    ordenarVetor(vetor, contador_vetor);
                    printf("Vetor ordenado por nome.\n");
                    listarItensVetor(vetor, contador_vetor);
                } else {
                    printf("Contadores (lista):\n Comparações - busca sequencial: %lld\n", comparacoes_busca_sequencial_lista);
                }
                break;

            case 6:
                if (estrutura == 0) {
                    char nome_bin[30];
                    printf("Digite o NOME do item para busca binária (vetor deve estar ordenado): ");
                    scanf(" %29[^\n]", nome_bin);
                    limpar_buffer();
                    clock_t t0 = clock();
                    int idx = buscarBinariaVetor(vetor, contador_vetor, nome_bin);
                    clock_t t1 = clock();
                    double ms = (double)(t1 - t0) / CLOCKS_PER_SEC * 1000.0;
                    if (idx >= 0) {
                        printf("Item encontrado (busca binária):\n Tipo: %s\n Nome: %s\n Quantidade: %d\n", vetor[idx].tipo, vetor[idx].nome, vetor[idx].quantidade);
                    } else {
                        printf("Item '%s' não encontrado (busca binária).\n", nome_bin);
                    }
                    printf("Comparações (busca binária - vetor): %lld. Tempo: %.3f ms\n", comparacoes_busca_binaria_vetor, ms);
                } else {
                    printf("Opção inválida: busca binária só está disponível para vetor.\n");
                }
                break;

            case 7:
                if (estrutura == 0) {
                    printf("Contadores (VETOR):\n Comparações - busca sequencial: %lld\n Comparações - busca binária: %lld\n", comparacoes_busca_sequencial_vetor, comparacoes_busca_binaria_vetor);
                } else {
                    printf("Opção inválida neste modo. Use opção 5 para mostrar contadores da lista.\n");
                }
                break;

            case 8:
                estrutura = 1 - estrutura;
                printf("Estrutura alterada. Agora em modo %s.\n", estrutura == 0 ? "VETOR" : "LISTA");
                break;

            case 0:
                liberarLista(&lista_cabeca);
                return;

            default:
                if (opcao != 0)
                    printf("Opção inválida! Tente novamente.\n");
                break;
        }

    } while(opcao != 0);
}

/* ===========================
   2) MESTRE - tipos & funcs
   =========================== */

#define MAX_COMPONENTES 20
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
} Componente;

/* utilitárias mestre */
static void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n == 0) return;
    if (s[n-1] == '\n') s[n-1] = '\0';
}

/* comparação case-insensitive entre strings; retorna <0,0,>0 */
static int str_casecmp_c(const char *a, const char *b) {
    while (*a && *b) {
        unsigned char ca = (unsigned char) tolower((unsigned char)*a);
        unsigned char cb = (unsigned char) tolower((unsigned char)*b);
        if (ca != cb) return (ca < cb) ? -1 : 1;
        a++; b++;
    }
    if (*a) return 1;
    if (*b) return -1;
    return 0;
}

/* mostra vetor de componentes */
void mostrarComponentesMestre(Componente v[], int n) {
    if (n == 0) {
        printf("-- Nenhum componente cadastrado --\n");
        return;
    }
    printf("\nIdx | Nome                          | Tipo               | Pri\n");
    printf("----+-------------------------------+--------------------+----\n");
    for (int i = 0; i < n; ++i) {
        printf("%3d | %-29s | %-18s | %2d\n", i, v[i].nome, v[i].tipo, v[i].prioridade);
    }
    printf("----+-------------------------------+--------------------+----\n");
}

/* Bubble sort por nome (string). Conta comparações entre elementos (não chars). */
void bubbleSortNome(Componente v[], int n, long long *comparacoes, double *tempo_ms) {
    *comparacoes = 0;
    clock_t t0 = clock();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            (*comparacoes)++;
            if (str_casecmp_c(v[j].nome, v[j+1].nome) > 0) {
                Componente tmp = v[j]; v[j] = v[j+1]; v[j+1] = tmp;
            }
        }
    }

    clock_t t1 = clock();
    *tempo_ms = (double)(t1 - t0) / CLOCKS_PER_SEC * 1000.0;
}

/* Insertion sort por tipo (string). */
void insertionSortTipo(Componente v[], int n, long long *comparacoes, double *tempo_ms) {
    *comparacoes = 0;
    clock_t t0 = clock();

    for (int i = 1; i < n; ++i) {
        Componente key = v[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (str_casecmp_c(v[j].tipo, key.tipo) > 0) {
                v[j+1] = v[j];
                j--;
            } else break;
        }
        v[j+1] = key;
    }

    clock_t t1 = clock();
    *tempo_ms = (double)(t1 - t0) / CLOCKS_PER_SEC * 1000.0;
}

/* Selection sort por prioridade (int). */
void selectionSortPrioridade(Componente v[], int n, long long *comparacoes, double *tempo_ms) {
    *comparacoes = 0;
    clock_t t0 = clock();

    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            (*comparacoes)++;
            if (v[j].prioridade < v[min_idx].prioridade) min_idx = j;
        }
        if (min_idx != i) {
            Componente tmp = v[i]; v[i] = v[min_idx]; v[min_idx] = tmp;
        }
    }

    clock_t t1 = clock();
    *tempo_ms = (double)(t1 - t0) / CLOCKS_PER_SEC * 1000.0;
}

/* Busca binária por nome - requer vetor previamente ordenado por nome.
   Retorna índice ou -1. Conta comparações entre elementos. */
int buscaBinariaPorNome(Componente v[], int n, const char *nome, long long *comparacoes) {
    *comparacoes = 0;
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        (*comparacoes)++;
        int cmp = str_casecmp_c(v[mid].nome, nome);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

/* Menu do módulo mestre */
void menu_mestre() {
    Componente componentes[MAX_COMPONENTES];
    int n = 0;
    int opcao;

    memset(componentes, 0, sizeof(componentes));

    while (1) {
        printf("\n=== Módulo Mestre: preparação da torre de resgate ===\n");
        printf("1) Cadastrar componente (até %d)\n", MAX_COMPONENTES);
        printf("2) Listar componentes\n");
        printf("3) Ordenar com Bubble Sort (por NOME)\n");
        printf("4) Ordenar com Insertion Sort (por TIPO)\n");
        printf("5) Ordenar com Selection Sort (por PRIORIDADE)\n");
        printf("6) Busca binária por NOME (requer ordenação por NOME)\n");
        printf("0) Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            printf("Entrada inválida.\n");
            continue;
        }
        while (getchar() != '\n'); /* limpar linha restante */

        if (opcao == 0) break;

        if (opcao == 1) {
            if (n >= MAX_COMPONENTES) {
                printf("Limite atingido (%d). Remova componentes antes de adicionar.\n", MAX_COMPONENTES);
                continue;
            }
            char buffer[MAX_NOME+4];
            printf("Nome do componente: ");
            if (!fgets(buffer, sizeof(buffer), stdin)) { printf("Erro de entrada.\n"); continue; }
            trim_newline(buffer);
            strncpy(componentes[n].nome, buffer, MAX_NOME-1);
            componentes[n].nome[MAX_NOME-1] = '\0';

            printf("Tipo do componente: ");
            if (!fgets(buffer, sizeof(buffer), stdin)) { printf("Erro de entrada.\n"); continue; }
            trim_newline(buffer);
            strncpy(componentes[n].tipo, buffer, MAX_TIPO-1);
            componentes[n].tipo[MAX_TIPO-1] = '\0';

            int pri = 0;
            do {
                printf("Prioridade (1-10): ");
                if (scanf("%d", &pri) != 1) {
                    while (getchar() != '\n');
                    pri = 0;
                } else while (getchar() != '\n');
                if (pri < 1 || pri > 10) printf("Valor inválido. Informe 1..10.\n");
            } while (pri < 1 || pri > 10);
            componentes[n].prioridade = pri;
            n++;
            printf("Componente cadastrado.\n");
            continue;
        }

        if (opcao == 2) {
            mostrarComponentesMestre(componentes, n);
            continue;
        }

        if (opcao == 3) {
            long long comps = 0; double tempo = 0.0;
            bubbleSortNome(componentes, n, &comps, &tempo);
            printf("Bubble Sort (por NOME) concluído. Comparações: %lld | Tempo: %.3f ms\n", comps, tempo);
            mostrarComponentesMestre(componentes, n);
            continue;
        }

        if (opcao == 4) {
            long long comps = 0; double tempo = 0.0;
            insertionSortTipo(componentes, n, &comps, &tempo);
            printf("Insertion Sort (por TIPO) concluído. Comparações: %lld | Tempo: %.3f ms\n", comps, tempo);
            mostrarComponentesMestre(componentes, n);
            continue;
        }

        if (opcao == 5) {
            long long comps = 0; double tempo = 0.0;
            selectionSortPrioridade(componentes, n, &comps, &tempo);
            printf("Selection Sort (por PRIORIDADE) concluído. Comparações: %lld | Tempo: %.3f ms\n", comps, tempo);
            mostrarComponentesMestre(componentes, n);
            continue;
        }

        if (opcao == 6) {
            if (n == 0) { printf("Nenhum componente cadastrado.\n"); continue; }
            char chave[MAX_NOME];
            printf("Informe o NOME do componente-chave a buscar (busca binária): ");
            if (!fgets(chave, sizeof(chave), stdin)) { printf("Erro de entrada.\n"); continue; }
            trim_newline(chave);
            long long comps = 0;
            int idx = buscaBinariaPorNome(componentes, n, chave, &comps);
            if (idx >= 0) {
                printf("Componente encontrado no índice %d:\n  Nome: %s\n  Tipo: %s\n  Prioridade: %d\n", idx, componentes[idx].nome, componentes[idx].tipo, componentes[idx].prioridade);
            } else {
                printf("Componente '%s' não encontrado (binária).\n", chave);
            }
            printf("Comparações na busca binária: %lld\n", comps);
            continue;
        }

        printf("Opção inválida.\n");
    }

    printf("Retornando ao menu principal.\n");
}

/* ===========================
   3) MAIN - menu principal
   =========================== */

int main() {
    int escolha;
    do {
        printf("\n==============================\n");
        printf("  JOGO: Mochila & Módulo Mestre\n");
        printf("==============================\n");
        printf("1) Abrir MOCHILA (vetor / lista)\n");
        printf("2) Abrir MÓDULO MESTRE (ordenações / busca)\n");
        printf("0) Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &escolha) != 1) {
            limpar_buffer();
            escolha = -1;
        } else limpar_buffer();

        switch (escolha) {
            case 1:
                menu_mochila();
                break;
            case 2:
                menu_mestre();
                break;
            case 0:
                printf("Encerrando aplicação.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 0);

    return 0;
}
