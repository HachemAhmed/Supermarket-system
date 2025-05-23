#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mercado.h"

Fila* criar_fila() 
{
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

struct Cliente* criar_cliente(char *nome, char *cpf, int num_itens, int prioridade) 
{
    struct Cliente *p = (struct Cliente*) malloc(sizeof(struct Cliente));
    strncpy(p->nome, nome, 100);
    strncpy(p->cpf, cpf, 12);
    p->num_itens = num_itens;
    p->prioridade = prioridade;
    p->prox = NULL;
    return p;
}

void enfileirar(Fila *f, struct Cliente *cliente) 
{
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = cliente;
    novo->prox = NULL;

    if (f->inicio == NULL) 
    {
        f->inicio = novo;
        f->fim = novo;
    } 
    else if (cliente->prioridade == 1) 
    {
        novo->prox = f->inicio;
        f->inicio = novo;
    } 
    else if (cliente->prioridade == 2) 
    {
        No *atual = f->inicio;
        No *anterior = NULL;
        
        while (atual != NULL && atual->dado->prioridade <= 2) 
        {
            anterior = atual;
            atual = atual->prox;
        }
        
        novo->prox = atual;
        
        if (anterior == NULL) 
        {
            f->inicio = novo;
        } 
        else 
        {
            anterior->prox = novo;
        }
        
        if (atual == NULL) 
        {
            f->fim = novo;
        }
    } 
    else 
    {
        f->fim->prox = novo;
        f->fim = novo;
    }
}


struct Cliente* desenfileirar(Fila *f) 
{ 
    if (fila_vazia(f)) return NULL;

    No *aux = f->inicio;
    struct Cliente *cliente = aux->dado;
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL) f->fim = NULL;
    free(aux);
    return cliente;
}

void mostrar_fila(Fila *f) 
{
    No *aux = f->inicio;
    while (aux != NULL) 
    {
        struct Cliente *c = aux->dado;
        printf("Nome: %s, CPF: %s, Prioridade: %d, Itens: %d\n", c->nome, c->cpf, c->prioridade, c->num_itens);
        aux = aux->prox;
    }
}

int fila_vazia(Fila *f) 
{
    return f->inicio == NULL;
}

void liberar_fila(Fila *f) 
{
    while (!fila_vazia(f)) 
    {
        desenfileirar(f);
    }
    free(f);
}

void inicializar_caixas(Caixa caixas[], int num_caixas) 
{
    for (int i = 0; i < num_caixas; i++) 
    {
        caixas[i].numero = i + 1;
        caixas[i].estado = 1; 
        caixas[i].fila = criar_fila();
    }
}

void abrir_fechar_caixa(Caixa *caixa, int estado) 
{
    caixa->estado = estado;
}

void realocar_clientes(Caixa caixas[], int num_caixas, int caixa_fechar) 
{
    Fila *fila_para_realocar = caixas[caixa_fechar].fila;
    while (!fila_vazia(fila_para_realocar)) 
    {
        struct Cliente *cliente = desenfileirar(fila_para_realocar);
        for (int i = 0; i < num_caixas; i++) 
        {
            if (caixas[i].estado == 1 && i != caixa_fechar) 
            {
                enfileirar(caixas[i].fila, cliente);
                break;
            }
        }
    }
}


