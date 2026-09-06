#include <stdio.h>

int main() {
    // Cabeçalho do programa
    // Exibe uma mensagem de boas-vindas e introduz o tema do jogo
    printf("\n*** DESAFIO SUPER TRUNFO ***\n");

    // Declaração das variáveis para as duas cartas
    // Estas variáveis armazenam informações sobre estado, código, nome da cidade, população, área, PIB, pontos turísticos,
    // densidade populacional, PIB per Capita e Super Poder (atributo de jogo)
    char estado_1, estado_2;  
    char codigo_da_carta_1[20], codigo_da_carta_2[20];
    char nome_da_cidade_1[50], nome_da_cidade_2[50];
    int populacao_1, populacao_2;
    float area_1, area_2;
    float pib_1, pib_2;
    int pontos_turisticos_1, pontos_turisticos_2;
    float densidade1, perCapita1;
    float densidade2, perCapita2;

    // Variáveis para o cálculo do Super Poder de cada carta
    float soma_variavel1, soma_variavel2;
    float super_poder1, super_poder2;

    // Variáveis para escolha dos atributos para comparação
    int opcao, opcao1;
    
    // Variáveis para armazenar o resultado das comparações dos atributos
    // Valor 1 significa que a Carta 1 venceu, 0 que a Carta 2 venceu
    int atributo1, atributo2;
    
    
    /*---------------------------------------------------------
      Entrada de dados para a Carta 1
      Requisito de usabilidade: Mensagens claras para o usuário inserir os dados.
    ---------------------------------------------------------*/
    printf("\n*** Digite os dados da Carta 1 ***\n");

    // Leitura do estado (uma letra de 'A' a 'H')
    printf("\nUma letra de 'A' a 'H': \n");
    scanf(" %c", &estado_1);

    // Leitura do código da carta (formado pela letra do estado seguida de um número de 01 a 04)
    printf("A letra do estado seguida de um número de 01 a 04: \n");
    scanf("%s", codigo_da_carta_1);

    // Leitura do nome da cidade
    printf("Digite o nome da cidade: \n");
    scanf(" %[^\n]", nome_da_cidade_1);

    // Leitura da população da cidade
    printf("Digite a população: \n");
    scanf("%d", &populacao_1);

    // Leitura da área da cidade
    printf("Digite a área: \n");
    scanf("%f", &area_1);

    // Leitura do PIB (em bilhões de reais)
    printf("Digite o PIB: \n");
    scanf("%f", &pib_1);

    // Leitura do número de pontos turísticos
    printf("Digite o número de pontos turísticos: \n");
    scanf("%d", &pontos_turisticos_1);

    // Cálculo da densidade populacional e PIB per Capita para Carta 1
    densidade1 = populacao_1 / area_1;
    perCapita1 = pib_1 / populacao_1;

    
    /*---------------------------------------------------------
      Entrada de dados para a Carta 2
      Requisito de usabilidade: Mensagens claras para o usuário.
    ---------------------------------------------------------*/
    printf("\n*** Digite os dados da Carta 2 ***\n");

    // Leitura do estado para a carta 2
    printf("\nUma letra de 'A' a 'H': \n");
    scanf(" %c", &estado_2);

    // Leitura do código da carta 2
    printf("A letra do estado seguida de um número de 01 a 04: \n");
    scanf("%s", codigo_da_carta_2);

    // Leitura do nome da cidade para a carta 2
    printf("Digite o nome da cidade: \n");
    scanf(" %[^\n]", nome_da_cidade_2);

    // Leitura da população da cidade da carta 2
    printf("Digite a população: \n");
    scanf("%d", &populacao_2);

    // Leitura da área da cidade da carta 2
    printf("Digite a área: \n");
    scanf("%f", &area_2);

    // Leitura do PIB para a carta 2
    printf("Digite o PIB: \n");
    scanf("%f", &pib_2);

    // Leitura do número de pontos turísticos da carta 2
    printf("Digite o número de pontos turísticos: \n");
    scanf("%d", &pontos_turisticos_2);

    // Cálculo da densidade populacional e PIB per Capita para Carta 2
    densidade2 = populacao_2 / area_2;
    perCapita2 = pib_2 / populacao_2;

    
    /*---------------------------------------------------------
      Exibição dos dados coletados para as Cartas
      Requisito de usabilidade: Informar de forma clara os dados inseridos.
    ---------------------------------------------------------*/
    printf("\n=== Dados da Carta 1 ===\n");
    printf("Código: %s\n", codigo_da_carta_1);
    printf("Estado: %c\n", estado_1);
    printf("Cidade: %s\n", nome_da_cidade_1);
    printf("População: %d habitantes\n", populacao_1);
    printf("Área: %.2f km²\n", area_1);
    printf("PIB: R$ %.2f bilhões de reais\n", pib_1);
    printf("Pontos turísticos: %d\n", pontos_turisticos_1);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade1);
    printf("PIB per Capita: %.2f Reais\n", perCapita1);

    printf("\n=== Dados da Carta 2 ===\n");
    printf("Código: %s\n", codigo_da_carta_2);
    printf("Estado: %c\n", estado_2);
    printf("Cidade: %s\n", nome_da_cidade_2);
    printf("População: %d habitantes\n", populacao_2);
    printf("Área: %.2f km²\n", area_2);
    printf("PIB: R$ %.2f bilhões de reais\n", pib_2);
    printf("Pontos turísticos: %d\n", pontos_turisticos_2);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade2);
    printf("PIB per Capita: %.2f Reais\n", perCapita2);

    
    /*---------------------------------------------------------
      Cálculo do Super Poder para cada carta
      Fórmula: Super Poder = (população + área + PIB + pontos turísticos)
                            + PIB per Capita + (1 / densidade)
      Requisito de performance: Cálculo rápido dos atributos.
    ---------------------------------------------------------*/
    soma_variavel1 = populacao_1 + area_1 + pib_1 + pontos_turisticos_1;
    soma_variavel2 = populacao_2 + area_2 + pib_2 + pontos_turisticos_2;

    super_poder1 = soma_variavel1 + perCapita1 + (1.0f / densidade1);
    super_poder2 = soma_variavel2 + perCapita2 + (1.0f / densidade2);

    
    /*---------------------------------------------------------
      Escolha do primeiro atributo para comparação entre as cartas
      Requisito de usabilidade: Interface intuitiva com instruções claras.
    ---------------------------------------------------------*/
    printf("\n=== Bem vindo ao jogo!!! ===\n");
    printf("1. População \n");
    printf("2. Área \n");
    printf("3. PIB \n");
    printf("4. Número de pontos turísticos \n");
    printf("5. Densidade demográfica \n");
    printf("6. PIB per Capita \n");
    
    printf("\nEscolha o primeiro atributo: \n");
    scanf("%d", &opcao);

    // Switch para tratar a opção do primeiro atributo e garantir confiabilidade (tratamento de opção inválida)
    switch(opcao) {
        case 1:
            printf("\nVocê escolheu a opção População! \n");
            // Operador ternário para comparação: se Carta 1 > Carta 2, atribui 1, caso contrário, 0
            atributo1 = populacao_1 > populacao_2 ? 1 : 0;
            break;

        case 2:
            printf("\nVocê escolheu a opção Área! \n");
            atributo1 = area_1 > area_2 ? 1 : 0;
            break;

        case 3:
            printf("\nVocê escolheu a opção PIB! \n");
            atributo1 = pib_1 > pib_2 ? 1 : 0;
            break;

        case 4:
            printf("\nVocê escolheu a opção Pontos turísticos! \n");
            atributo1 = pontos_turisticos_1 > pontos_turisticos_2 ? 1 : 0;
            break;

        case 5:
            printf("\nVocê escolheu a opção Densidade demográfica! \n");
            // Para densidade, a carta com menor valor vence (maior qualidade)
            atributo1 = densidade1 < densidade2 ? 1 : 0;
            break;

        case 6:
            printf("\nVocê escolheu a opção PIB per Capita! \n");
            atributo1 = perCapita1 > perCapita2 ? 1 : 0;
            break;

        default:
            // Trata opção inválida de forma robusta, exibindo mensagem de erro
            printf("\nOpção inválida!\n");
    }
    
    /*---------------------------------------------------------
      Escolha do segundo atributo para comparação
      Requisito de usabilidade: Mensagem alerta para não repetir atributo
    ---------------------------------------------------------*/
    printf("Escolha o segundo atributo. \n");
    printf("Atenção: Você deve escolher um atributo diferente do primeiro \n");
    printf("1. População \n");
    printf("2. Área \n");
    printf("3. PIB \n");
    printf("4. Número de pontos turísticos \n");
    printf("5. Densidade demográfica \n");
    printf("6. PIB per Capita \n");
    scanf("%d", &opcao1);

    // Verifica se o mesmo atributo foi escolhido para ambas as comparações
    if(atributo1 == atributo2) {
        printf("Você escolheu o mesmo atributo! \n");
    } else {
        // Switch para tratar a opção do segundo atributo com o mesmo mecanismo do primeiro
        switch(opcao1) {
            case 1:
                printf("\nVocê escolheu a opção População! \n");
                atributo2 = populacao_1 > populacao_2 ? 1 : 0;
                break;
    
            case 2:
                printf("\nVocê escolheu a opção Área! \n");
                atributo2 = area_1 > area_2 ? 1 : 0;
                break;
    
            case 3:
                printf("\nVocê escolheu a opção PIB! \n");
                atributo2 = pib_1 > pib_2 ? 1 : 0;
                break;
    
            case 4:
                printf("\nVocê escolheu a opção Pontos turísticos! \n");
                atributo2 = pontos_turisticos_1 > pontos_turisticos_2 ? 1 : 0;
                break;
    
            case 5:
                printf("\nVocê escolheu a opção Densidade demográfica! \n");
                atributo2 = densidade1 < densidade2 ? 1 : 0;
                break;
    
            case 6:
                printf("\nVocê escolheu a opção PIB per Capita! \n");
                atributo2 = perCapita1 > perCapita2 ? 1 : 0;
                break;
    
            default:
                printf("\nOpção inválida!\n");
        }	
    }
	
    /*---------------------------------------------------------
      Resultado da comparação dos atributos escolhidos
      Exibe mensagem de vitória, empate ou derrota
      Requisito de usabilidade e confiabilidade: Mensagens claras com tratamento de erros.
    ---------------------------------------------------------*/
    if (atributo1 && atributo2) {
        printf("Parabéns, Você venceu!!! \n");
    } else if (atributo1 != atributo2) {
        printf("Empatou!!! \n");
    } else {
        printf("Infelizmente você perdeu!!! \n");
    }
	
    /*---------------------------------------------------------
      Comparação adicional: PIB per Capita
      Exibe os valores para cada carta e o resultado da comparação.
    ---------------------------------------------------------*/
    if (perCapita1 > perCapita2) {
        printf("\nCarta 1 - %s : %.2f \n", nome_da_cidade_1, perCapita1);
        printf("Carta 2 - %s : %.2f \n", nome_da_cidade_2, perCapita2);
        printf("PIB per Capita: Carta 1 venceu \n");
    } else {
        printf("\nCarta 1 - %s : %.2f \n", nome_da_cidade_1, perCapita1);
        printf("Carta 2 - %s : %.2f \n", nome_da_cidade_2, perCapita2);
        printf("PIB per Capita: Carta 2 venceu \n");
    }

    /*---------------------------------------------------------
      Comparação adicional: Super Poder
      Exibe os valores para cada carta e o resultado da comparação.
    ---------------------------------------------------------*/
    if (super_poder1 > super_poder2) {
        printf("\nCarta 1 - %s : %.2f \n", nome_da_cidade_1, super_poder1);
        printf("Carta 2 - %s : %.2f \n", nome_da_cidade_2, super_poder2);
        printf("Super Poder: Carta 1 venceu \n");
    } else {
        printf("\nCarta 1 - %s : %.2f \n", nome_da_cidade_1, super_poder1);
        printf("Carta 2 - %s : %.2f \n", nome_da_cidade_2, super_poder2);
        printf("Super Poder: Carta 2 venceu \n");
    }

    return 0;
}


