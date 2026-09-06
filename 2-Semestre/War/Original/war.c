#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// =========================
// Struct para representar um território
// =========================
typedef struct {
    char nome[50];    // Nome do território
    char cor[10];     // Cor do exército que domina
    int tropas;       // Quantidade de tropas no território
} Territorio;

// =========================
// Funções relacionadas às missões
// =========================

// Função para sortear a missão do jogador.
// Retorna um número de 1 a 5 para a missão.
int sortearMissao() {
    return (rand() % 5) + 1;
}

// Função para exibir a missão do jogador
// Usa passagem de parâmetros por valor
void exibirMissao(int missao_num) {
    printf("\n--- MISSAO ESTRATEGICA ---\n");
    switch (missao_num) {
        case 1:
            printf("Sua missao e: Conquistar 1 territorio.\n");
            break;
        case 2:
            printf("Sua missao e: Conquistar 2 territorios.\n");
            break;
        case 3:
            printf("Sua missao e: Eliminar um exercito inimigo.\n");
            break;
        case 4:
            printf("Sua missao e: Possuir mais da metade do total de tropas no mapa.\n");
            break;
        case 5:
            printf("Sua missao e: Possuir 15 ou mais tropas.\n");
            break;
    }
    printf("---------------------------\n");
}

// Função para verificar se a missão foi concluída.
// Usa passagem de parâmetros por referência para o mapa.
bool verificarMissao(int missao_num, Territorio* mapa, int n, char* cor_jogador) {
    int cont_territorios_jogador = 0;
    int total_tropas_jogador = 0;
    int total_tropas_mapa = 0;
    int num_exercitos_inimigos = 0;

    // Verifica quantos territórios e tropas o jogador tem
    for (int i = 0; i < n; i++) {
        total_tropas_mapa += mapa[i].tropas;
        if (strcmp(mapa[i].cor, cor_jogador) == 0) {
            cont_territorios_jogador++;
            total_tropas_jogador += mapa[i].tropas;
        }
    }

    // Verifica o número de exércitos inimigos
    for (int i = 0; i < n; i++) {
        if (strcmp(mapa[i].cor, cor_jogador) != 0) {
            bool existe = false;
            for (int j = 0; j < n; j++) {
                if (i != j && strcmp(mapa[i].cor, mapa[j].cor) == 0) {
                    existe = true;
                    break;
                }
            }
            if (!existe) {
                num_exercitos_inimigos++;
            }
        }
    }

    // Lógica de verificação para cada missão
    switch (missao_num) {
        case 1:
            return cont_territorios_jogador >= 1;
        case 2:
            return cont_territorios_jogador >= 2;
        case 3:
            return num_exercitos_inimigos == 0;
        case 4:
            return total_tropas_jogador > (total_tropas_mapa / 2);
        case 5:
            return total_tropas_jogador >= 15;
        default:
            return false;
    }
}

// =========================
// Outras Funções do Jogo
// =========================

// Função para ler dados de um território
void lerTerritorio(Territorio* t) {
    printf("Nome do Territorio: ");
    fgets(t->nome, 50, stdin);
    t->nome[strcspn(t->nome, "\n")] = '\0';

    printf("Cor do Exercito (ex: Azul, Verde...): ");
    fgets(t->cor, 10, stdin);
    t->cor[strcspn(t->cor, "\n")] = '\0';

    printf("Numero de Tropas: ");
    scanf("%d", &t->tropas);
    getchar();
}

// Função para mostrar todos os territórios
void mostrarMapa(Territorio* cadastro, int n) {
    printf("\n--- MAPA ATUAL ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n",
               i + 1, cadastro[i].nome, cadastro[i].cor, cadastro[i].tropas);
    }
}

// Função para validar escolhas de ataque
int validarEscolha(int* escolha, int n, Territorio* mapa) {
    if (escolha[0] == escolha[1]) {
        printf("Atacante nao pode ser o mesmo defensor!!!\n");
        return 0;
    }
    if (escolha[0] < 1 || escolha[0] > n || escolha[1] < 1 || escolha[1] > n) {
        printf("Escolha fora do intervalo valido (1 a %d)!!!\n", n);
        return 0;
    }
    if (strcmp(mapa[escolha[0]-1].cor, mapa[escolha[1]-1].cor) == 0) {
        printf("Atacante nao pode atacar territorio do proprio exercito!\n");
        return 0;
    }
    printf("Escolhas validas, pode prosseguir com o ataque.\n");
    return 1;
}

// Função de ataque entre dois territórios, agora com lógica de conquista
void atacar(Territorio* atacante, Territorio* defensor) {
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;

    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Atacante %s rolou: %d\n", atacante->nome, dado_atacante);
    printf("Defensor %s rolou: %d\n", defensor->nome, dado_defensor);

    if (dado_atacante > dado_defensor) {
        printf("Atacante vence!\n");
        defensor->tropas--;
        if (defensor->tropas <= 0) {
            printf("Territorio %s foi conquistado por %s!\n", defensor->nome, atacante->nome);
            strcpy(defensor->cor, atacante->cor);
            int tropas_transferir = atacante->tropas / 2;
            defensor->tropas = tropas_transferir;
            atacante->tropas -= tropas_transferir;
        }
    } else {
        printf("Defensor vence!\n");
        atacante->tropas--;
        if (atacante->tropas <= 0) {
            printf("O exercito %s nao pode atacar mais, esta esgotado!\n", atacante->cor);
        }
    }
}

// Função para liberar a memória alocada dinamicamente
void liberarMemoria(Territorio* cadastro) {
    free(cadastro);
}

// =========================
// Função principal
// =========================
int main() {
    srand(time(NULL)); // Inicializa a semente apenas uma vez

    int n = 5;
    int escolha[2];
    int opcao;
    int missao_do_jogador;
    char cor_jogador[10];

    Territorio* cadastro = calloc(n, sizeof(Territorio));
    if (cadastro == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    printf("Vamos cadastrar os %d territorios iniciais do nosso mundo.\n", n);
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        lerTerritorio(&cadastro[i]);
    }
    strcpy(cor_jogador, cadastro[0].cor); // Guarda a cor do primeiro território como a do jogador

    printf("\nCadastro concluido com sucesso!!!\n");

    // Sorteia e exibe a missão do jogador
    missao_do_jogador = sortearMissao();
    exibirMissao(missao_do_jogador);

    do {
        printf("\n*** MENU ***\n");
        printf("1. Atacar\n2. Mostrar mapa\n3. Sair\n");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 2) {
            mostrarMapa(cadastro, n);
        } else if (opcao == 3) {
            printf("*** Fechando o jogo ***\n");
            break;
        } else if (opcao == 1) {
            printf("\nEscolha o territorio atacante (1 a %d): ", n);
            scanf("%d", &escolha[0]);
            getchar();

            printf("Escolha o territorio defensor (1 a %d): ", n);
            scanf("%d", &escolha[1]);
            getchar();

            if (validarEscolha(escolha, n, cadastro)) {
                atacar(&cadastro[escolha[0]-1], &cadastro[escolha[1]-1]);
            }

            // Verifica a missão após cada turno de ataque
            if (verificarMissao(missao_do_jogador, cadastro, n, cor_jogador)) {
                printf("\n\nParabens! Voce completou sua missao e venceu o jogo!\n");
                break;
            }
        } else {
            printf("Escolha uma opcao valida!!!\n");
        }

    } while (opcao != 3);

    liberarMemoria(cadastro);
    return 0;
}
