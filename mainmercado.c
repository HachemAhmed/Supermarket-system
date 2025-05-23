#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mercado.h"

#define NUM_CAIXAS 5

int main() 
{
    Caixa caixas[NUM_CAIXAS];
    inicializar_caixas(caixas, NUM_CAIXAS);
    int opcao, caixa_num;
    char nome[100], cpf[12];
    int prioridade, num_itens;

    do 
    {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Cadastrar um Cliente\n");
        printf("2 - Atender um Cliente\n");
        printf("3 - Abrir ou Fechar um Caixa\n");
        printf("4 - Imprimir a Lista de Clientes em Espera\n");
        printf("5 - Imprimir o Status dos Caixas\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) 
        {
            case 1: 
                getchar();
                printf("Digite o nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite o CPF: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = '\0';

                printf("Numero de itens: ");
                scanf("%d", &num_itens);
                getchar();

                printf("Prioridade (1 - alta, 2 - media, 3 - baixa): ");
                scanf("%d", &prioridade);
                getchar();

                printf("Numero do caixa (1 a %d): ", NUM_CAIXAS);
                scanf("%d", &caixa_num);
                getchar();

                if (caixa_num >= 1 && caixa_num <= NUM_CAIXAS && caixas[caixa_num - 1].estado == 1) 
                {
                    struct Cliente *cliente = criar_cliente(nome, cpf, num_itens, prioridade);
                    enfileirar(caixas[caixa_num - 1].fila, cliente);
                } 
                else 
                {
                    printf("Caixa inexistente ou fechado.\n");
                }
                break;

            case 2: 
                printf("Escolha um caixa para atendimento (1 a %d): ", NUM_CAIXAS);
                scanf("%d", &caixa_num);
                if (caixa_num >= 1 && caixa_num <= NUM_CAIXAS && caixas[caixa_num - 1].estado == 1) 
                {
                    struct Cliente *atendido = desenfileirar(caixas[caixa_num - 1].fila);
                    if (atendido != NULL) 
                    {
                        printf("Cliente atendido: %s\n", atendido->nome);
                        free(atendido);
                    } 
                    else 
                    {
                        printf("Nenhum cliente na fila.\n");
                    }
                } 
                else 
                {
                    printf("Caixa invalido ou fechado.\n");
                }
                break;

            case 3: 
                printf("Numero do caixa para abrir/fechar (1 a %d): ", NUM_CAIXAS);
                scanf("%d", &caixa_num);
                if (caixa_num >= 1 && caixa_num <= NUM_CAIXAS) 
                {
                    if (caixas[caixa_num - 1].estado == 1) 
                    {
                        printf("Fechando o caixa %d.\n", caixa_num);
                        abrir_fechar_caixa(&caixas[caixa_num - 1], 0);
                        realocar_clientes(caixas, NUM_CAIXAS, caixa_num - 1);
                    } 
                    else 
                    {
                        printf("Abrindo o caixa %d.\n", caixa_num);
                        abrir_fechar_caixa(&caixas[caixa_num - 1], 1);
                    }
                }
                break;

            case 4: 
                for (int i = 0; i < NUM_CAIXAS; i++) 
                {
                    printf("\nCaixa %d:\n", caixas[i].numero);
                    mostrar_fila(caixas[i].fila);
                }
                break;

            case 5: 
                for (int i = 0; i < NUM_CAIXAS; i++) 
                {
                    printf("Caixa %d: %s\n", caixas[i].numero, (caixas[i].estado == 1) ? "Aberto" : "Fechado");
                    if (!fila_vazia(caixas[i].fila)) 
                    {
                        printf("Clientes na fila:\n");
                        mostrar_fila(caixas[i].fila);
                    } 
                    else 
                    {
                        printf("Nenhum cliente na fila.\n");
                    }
                }
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    for (int i = 0; i < NUM_CAIXAS; i++) 
    {
        liberar_fila(caixas[i].fila);
    }

    return 0;
}
