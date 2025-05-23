#ifndef MERCADO_H
#define MERCADO_H

struct Cliente 
{
    char nome[100];
    char cpf[12];  
    int num_itens;
    int prioridade;
    struct Cliente *prox;
};

typedef struct no 
{
    struct Cliente *dado; 
    struct no *prox;
} No;

typedef struct fila 
{
    No *inicio;  
    No *fim;     
} Fila;

typedef struct 
{
    int numero;   
    int estado;   
    Fila *fila;   
} Caixa;

Fila* criar_fila();
struct Cliente* criar_cliente(char *nome, char *cpf, int num_itens, int prioridade);
void enfileirar(Fila *f, struct Cliente *cliente);
struct Cliente* desenfileirar(Fila *f);
void mostrar_fila(Fila *f);
int fila_vazia(Fila *f);
void liberar_fila(Fila *f);


void inicializar_caixas(Caixa caixas[], int num_caixas);
void abrir_fechar_caixa(Caixa *caixa, int estado);
void realocar_clientes(Caixa caixas[], int num_caixas, int caixa_fechar);

#endif


