#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 101

typedef struct Sala {
    char *nome;
    char *pista;
    struct Sala *esq;
    struct Sala *dir;
} Sala;

typedef struct PistaNode {
    char *pista;
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;

typedef struct HashEntry {
    char *pista;
    char *suspeito;
    struct HashEntry *next;
} HashEntry;

typedef struct HashTable {
    HashEntry *buckets[HASH_SIZE];
} HashTable;

/* criarSala - cria dinamicamente um cômodo com nome e pista (pista pode ser NULL) */
Sala *criarSala(const char *nome, const char *pista) {
    if (!nome) return NULL;
    Sala *s = malloc(sizeof(Sala));
    if (!s) return NULL;
    s->nome = malloc(strlen(nome) + 1);
    strcpy(s->nome, nome);
    if (pista) {
        s->pista = malloc(strlen(pista) + 1);
        strcpy(s->pista, pista);
    } else s->pista = NULL;
    s->esq = s->dir = NULL;
    return s;
}

/* inserirPista - insere uma pista na BST (sem duplicatas); retorna nova raiz */
PistaNode *inserirPista(PistaNode *raiz, const char *pista) {
    if (!pista) return raiz;
    if (!raiz) {
        PistaNode *n = malloc(sizeof(PistaNode));
        n->pista = malloc(strlen(pista) + 1);
        strcpy(n->pista, pista);
        n->esq = n->dir = NULL;
        return n;
    }
    int cmp = strcmp(pista, raiz->pista);
    if (cmp == 0) return raiz;
    if (cmp < 0) raiz->esq = inserirPista(raiz->esq, pista);
    else raiz->dir = inserirPista(raiz->dir, pista);
    return raiz;
}

/* adicionarPista - insere pista e retorna 1 se foi efetivamente adicionada, 0 se já existia */
int adicionarPista(PistaNode **rootRef, const char *pista) {
    if (!pista || !rootRef) return 0;
    PistaNode *cur = *rootRef;
    while (cur) {
        int cmp = strcmp(pista, cur->pista);
        if (cmp == 0) return 0;
        if (cmp < 0) cur = cur->esq;
        else cur = cur->dir;
    }
    *rootRef = inserirPista(*rootRef, pista);
    return 1;
}

/* djb2 */
static unsigned long hash_str(const char *s) {
    unsigned long h = 5381;
    int c;
    while ((c = (unsigned char)*s++)) h = ((h << 5) + h) + c;
    return h;
}

/* inserirNaHash - associa uma pista a um suspeito na tabela hash */
void inserirNaHash(HashTable *ht, const char *pista, const char *suspeito) {
    if (!ht || !pista || !suspeito) return;
    unsigned long h = hash_str(pista) % HASH_SIZE;
    HashEntry *e = malloc(sizeof(HashEntry));
    e->pista = malloc(strlen(pista) + 1);
    strcpy(e->pista, pista);
    e->suspeito = malloc(strlen(suspeito) + 1);
    strcpy(e->suspeito, suspeito);
    e->next = ht->buckets[h];
    ht->buckets[h] = e;
}

/* encontrarSuspeito - retorna o nome do suspeito associado à pista (ou NULL) */
const char *encontrarSuspeito(HashTable *ht, const char *pista) {
    if (!ht || !pista) return NULL;
    unsigned long h = hash_str(pista) % HASH_SIZE;
    for (HashEntry *e = ht->buckets[h]; e; e = e->next) {
        if (strcmp(e->pista, pista) == 0) return e->suspeito;
    }
    return NULL;
}

/* verificarSuspeitoFinal - conta quantas pistas coletadas apontam para suspeito */
int verificarSuspeitoFinal(PistaNode *raiz, HashTable *ht, const char *suspeito) {
    if (!raiz || !ht || !suspeito) return 0;
    int count = 0;
    // in-order traversal iterative via recursion
    if (raiz->esq) count += verificarSuspeitoFinal(raiz->esq, ht, suspeito);
    const char *s = encontrarSuspeito(ht, raiz->pista);
    if (s && strcmp(s, suspeito) == 0) count++;
    if (raiz->dir) count += verificarSuspeitoFinal(raiz->dir, ht, suspeito);
    return count;
}

/* limpar estruturas */
void liberarPistas(PistaNode *r) {
    if (!r) return;
    liberarPistas(r->esq);
    liberarPistas(r->dir);
    free(r->pista);
    free(r);
}
void liberarHash(HashTable *ht) {
    if (!ht) return;
    for (int i = 0; i < HASH_SIZE; ++i) {
        HashEntry *e = ht->buckets[i];
        while (e) {
            HashEntry *n = e->next;
            free(e->pista);
            free(e->suspeito);
            free(e);
            e = n;
        }
    }
}
void liberarSalas(Sala *r) {
    if (!r) return;
    liberarSalas(r->esq);
    liberarSalas(r->dir);
    free(r->nome);
    if (r->pista) free(r->pista);
    free(r);
}
void exibirPistas(PistaNode *r) {
    if (!r) return;
    exibirPistas(r->esq);
    printf("- %s\n", r->pista);
    exibirPistas(r->dir);
}

/* explorarSalas - navega pela árvore, coleta pistas e insere na BST */
void explorarSalas(Sala *inicio, PistaNode **pistasRoot, HashTable *ht) {
    if (!inicio || !pistasRoot || !ht) return;
    Sala *atual = inicio;
    char buf[128];
    if (atual->pista) {
        if (adicionarPista(pistasRoot, atual->pista))
            printf("Pista coletada em \"%s\": %s\n", atual->nome, atual->pista);
    }
    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);
        printf("Opções:");
        if (atual->esq) printf(" [e] esquerda");
        if (atual->dir) printf(" [d] direita");
        printf(" [s] sair\n");
        printf("Escolha: ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        char opc = '\0';
        for (size_t i = 0; buf[i]; ++i) {
            if (!isspace((unsigned char)buf[i])) { opc = tolower((unsigned char)buf[i]); break; }
        }
        if (opc == 's') {
            printf("Exploração encerrada.\n");
            break;
        } else if (opc == 'e') {
            if (!atual->esq) { printf("Caminho à esquerda inexistente.\n"); continue; }
            atual = atual->esq;
        } else if (opc == 'd') {
            if (!atual->dir) { printf("Caminho à direita inexistente.\n"); continue; }
            atual = atual->dir;
        } else { printf("Opção inválida.\n"); continue; }
        if (atual->pista) {
            if (adicionarPista(pistasRoot, atual->pista))
                printf("Pista coletada em \"%s\": %s\n", atual->nome, atual->pista);
        } else {
            printf("Nenhuma pista nesta sala.\n");
        }
    }
}

int main(void) {
    HashTable ht = {0};
    PistaNode *pistasRoot = NULL;

    Sala *hall = criarSala("Hall de Entrada", "Pegadas molhadas");
    Sala *salaEstar = criarSala("Sala de Estar", NULL);
    Sala *cozinha = criarSala("Cozinha", "Faca com manchas");
    Sala *biblioteca = criarSala("Biblioteca", "Livro rasgado");
    Sala *escritorio = criarSala("Escritório", "Bilhete ameaçador");
    Sala *jardim = criarSala("Jardim", "Pó de flor exótico");
    Sala *porao = criarSala("Porão", "Carta rasurada");
    Sala *armario = criarSala("Armário", "Chave velha");

    hall->esq = salaEstar; hall->dir = cozinha;
    salaEstar->esq = biblioteca; salaEstar->dir = escritorio;
    biblioteca->esq = armario; biblioteca->dir = NULL;
    armario->esq = armario->dir = NULL;
    escritorio->esq = escritorio->dir = NULL;
    cozinha->esq = jardim; cozinha->dir = porao;
    jardim->esq = jardim->dir = NULL;
    porao->esq = porao->dir = NULL;

    inserirNaHash(&ht, "Pegadas molhadas", "Suspeito A");
    inserirNaHash(&ht, "Faca com manchas", "Suspeito B");
    inserirNaHash(&ht, "Livro rasgado", "Suspeito C");
    inserirNaHash(&ht, "Bilhete ameaçador", "Suspeito B");
    inserirNaHash(&ht, "Pó de flor exótico", "Suspeito A");
    inserirNaHash(&ht, "Carta rasurada", "Suspeito D");
    inserirNaHash(&ht, "Chave velha", "Suspeito C");

    explorarSalas(hall, &pistasRoot, &ht);

    printf("\nPistas coletadas (ordenadas):\n");
    if (!pistasRoot) printf("Nenhuma pista coletada.\n");
    else exibirPistas(pistasRoot);

    char acusacao[128];
    printf("\nIndique o nome do suspeito para acusar (ex: Suspeito A): ");
    if (!fgets(acusacao, sizeof(acusacao), stdin)) acusacao[0] = '\0';
    size_t len = strlen(acusacao);
    if (len && acusacao[len-1] == '\n') acusacao[len-1] = '\0';

    int cont = verificarSuspeitoFinal(pistasRoot, &ht, acusacao);
    if (cont >= 2) {
        printf("Acusação confirmada: %s possui %d pistas apontando para ele(a).\n", acusacao, cont);
    } else {
        printf("Acusação não confirmada: %s possui apenas %d pista(s) coletada(s) apontando para ele(a).\n", acusacao, cont);
    }

    liberarPistas(pistasRoot);
    liberarHash(&ht);
    liberarSalas(hall);
    return 0;
}
