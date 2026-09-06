#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5         // Tamanho da fila
#define MAX_PILHA 3   // Tamanho da pilha

// ---------- Estrutura da peça ----------
typedef struct {
    char peca;
    int id;
} Struct_peca;

// ---------- Estrutura da fila circular ----------
typedef struct {
    Struct_peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// ---------- Estrutura da pilha ----------
typedef struct {
    Struct_peca itens[MAX_PILHA];
    int topo;
} Pilha;

// ---------- Fila: Funções ----------
void inicializar_fila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int fila_vazia(Fila *f) {
    return f->total == 0;
}

int fila_cheia(Fila *f) {
    return f->total == MAX;
}

void inserir(Fila *f, Struct_peca p) {
    if (fila_cheia(f)) return;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(Fila *f, Struct_peca *p) {
    if (fila_vazia(f)) return;
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

Struct_peca* acessar_inicio(Fila *f) {
    if (fila_vazia(f)) return NULL;
    return &f->itens[f->inicio];
}

void mostrarFila(Fila *f) {
    printf("Fila de peças\t");
    if (fila_vazia(f)) {
        printf("[vazia]\n");
        return;
    }

    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        Struct_peca p = f->itens[idx];
        printf("[%c %d] ", p.peca, p.id);
        idx = (idx + 1) % MAX;
    }
    printf("\n");
}

// ---------- Pilha: Funções ----------
void inicializar_pilha(Pilha *p) {
    p->topo = -1;
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

int pilha_cheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

void push(Pilha *p, Struct_peca x) {
    if (pilha_cheia(p)) return;
    p->itens[++p->topo] = x;
}

void pop(Pilha *p, Struct_peca *x) {
    if (pilha_vazia(p)) return;
    *x = p->itens[p->topo--];
}

Struct_peca* topo_pilha(Pilha *p) {
    if (pilha_vazia(p)) return NULL;
    return &p->itens[p->topo];
}

void mostrar_pilha(Pilha *p) {
    printf("Pilha de reserva\t");
    if (pilha_vazia(p)) {
        printf("[vazia]\n");
        return;
    }

    printf("(Topo -> base): ");
    for (int i = p->topo; i >= 0; i--) {
        Struct_peca x = p->itens[i];
        printf("[%c %d] ", x.peca, x.id);
    }
    printf("\n");
}

// ---------- Geração de peças ----------
Struct_peca gerar_peca(int id) {
    const char tipos[] = {'I', 'O', 'T', 'L'};
    Struct_peca nova;
    nova.peca = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// ---------- Troca total entre fila e pilha ----------
void troca_multipla(Fila *f, Pilha *p) {
    if (f->total < 3 || p->topo < 2) {
        printf("Troca múltipla não permitida: estruturas não têm 3 peças.\n");
        return;
    }

    // Troca os 3 primeiros da fila com os 3 da pilha
    for (int i = 0; i < 3; i++) {
        int idx_fila = (f->inicio + i) % MAX;
        int idx_pilha = p->topo - i;

        Struct_peca temp = f->itens[idx_fila];
        f->itens[idx_fila] = p->itens[idx_pilha];
        p->itens[idx_pilha] = temp;
    }

    printf("Troca múltipla realizada entre fila e pilha.\n");
}

// ---------- Função principal ----------
int main() {
    Fila f;
    Pilha pilha;
    Struct_peca removida;
    int proximo_id = 0;
    int opcao = -1;

    srand((unsigned)time(NULL));
    inicializar_fila(&f);
    inicializar_pilha(&pilha);

    // Preencher a fila inicialmente
    while (!fila_cheia(&f)) {
        inserir(&f, gerar_peca(proximo_id++));
    }

    do {
        printf("\n=== Estado Atual ===\n");
        mostrarFila(&f);
        mostrar_pilha(&pilha);
        printf("\nMenu:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Reservar peça (enviar da fila para a pilha)\n");
        printf("3 - Usar peça da reserva (pilha)\n");
        printf("4 - Trocar peça da fila com topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com os 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Opção escolhida: ");

        if (scanf("%d", &opcao) != 1) {
            // entrada inválida: descartar até newline
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1; // força mensagem de opção inválida
        }

        switch (opcao) {
            case 1: // Jogar peça
                if (!fila_vazia(&f)) {
                    remover(&f, &removida);
                    printf("Peça jogada: [%c %d]\n", removida.peca, removida.id);
                    inserir(&f, gerar_peca(proximo_id++));
                } else {
                    printf("Fila vazia.\n");
                }
                break;

            case 2: // Reservar peça
                if (!fila_vazia(&f) && !pilha_cheia(&pilha)) {
                    remover(&f, &removida);
                    push(&pilha, removida);
                    printf("Peça [%c %d] reservada.\n", removida.peca, removida.id);
                    inserir(&f, gerar_peca(proximo_id++));
                } else {
                    printf("Não é possível reservar (fila vazia ou pilha cheia).\n");
                }
                break;

            case 3: // Usar peça da pilha
                if (!pilha_vazia(&pilha)) {
                    pop(&pilha, &removida);
                    printf("Peça da reserva usada: [%c %d]\n", removida.peca, removida.id);
                    inserir(&f, gerar_peca(proximo_id++));
                } else {
                    printf("Pilha vazia.\n");
                }
                break;

            case 4: // Trocar peça da frente com topo da pilha
                if (!fila_vazia(&f) && !pilha_vazia(&pilha)) {
                    Struct_peca* p_fila = acessar_inicio(&f);
                    Struct_peca* p_pilha = topo_pilha(&pilha);

                    if (p_fila && p_pilha) {
                        Struct_peca temp = *p_fila;
                        *p_fila = *p_pilha;
                        *p_pilha = temp;
                        printf("Peças trocadas entre frente da fila e topo da pilha.\n");
                    }
                } else {
                    printf("Não é possível trocar: fila ou pilha vazia.\n");
                }
                break;

            case 5: // Troca múltipla
                troca_multipla(&f, &pilha);
                break;

            case 0:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
