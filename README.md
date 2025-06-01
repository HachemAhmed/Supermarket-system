# Sistema de Gerenciamento de Filas de Mercado

## Descrição

Este projeto implementa um sistema de gerenciamento de filas para um mercado, permitindo o controle de clientes em diferentes caixas com sistema de prioridades. Foi desenvolvido como **Trabalho 2** da disciplina **Introdução à Programação de Computadores**.

O sistema simula o funcionamento de um mercado com múltiplos caixas, onde os clientes são organizados em filas com base em suas prioridades (alta, média e baixa), e permite operações como cadastro, atendimento, abertura/fechamento de caixas e realocação automática de clientes.

## Funcionalidades

- **Cadastro de Clientes**: Registro de clientes com nome, CPF, número de itens e prioridade
- **Sistema de Prioridades**: 
  - Prioridade 1 (Alta): Clientes são inseridos no início da fila
  - Prioridade 2 (Média): Clientes são inseridos após outros de prioridade alta
  - Prioridade 3 (Baixa): Clientes são inseridos no final da fila
- **Atendimento**: Remoção do primeiro cliente da fila para atendimento
- **Gerenciamento de Caixas**: Abertura e fechamento de caixas
- **Realocação Automática**: Quando um caixa é fechado, seus clientes são automaticamente redistribuídos para outros caixas abertos
- **Visualização**: Exibição do status dos caixas e clientes em espera

## Estrutura do Projeto

```
mercado/
├── mercado.h          # Definições de estruturas e protótipos das funções
├── mercado.c          # Implementação das funções do sistema
├── mainmercado.c      # Programa principal com interface do usuário
└── README.md          # Este arquivo
```

## Estruturas de Dados

### Cliente
```c
struct Cliente {
    char nome[100];     // Nome do cliente
    char cpf[12];       // CPF do cliente
    int num_itens;      // Número de itens na compra
    int prioridade;     // Prioridade (1-alta, 2-média, 3-baixa)
    struct Cliente *prox; // Ponteiro para próximo cliente
};
```

### Fila
```c
typedef struct fila {
    No *inicio;         // Ponteiro para o início da fila
    No *fim;           // Ponteiro para o fim da fila
} Fila;
```

### Caixa
```c
typedef struct {
    int numero;         // Número do caixa
    int estado;         // Estado (1-aberto, 0-fechado)
    Fila *fila;        // Fila de clientes do caixa
} Caixa;
```

## Compilação

Para compilar o projeto, use o seguinte comando no terminal:

```bash
gcc -o mercado mainmercado.c mercado.c
```

## Execução

Após a compilação, execute o programa:

```bash
./mercado
```

## Menu de Opções

Ao executar o programa, você verá o seguinte menu:

```
Escolha uma opcao:
1 - Cadastrar um Cliente
2 - Atender um Cliente  
3 - Abrir ou Fechar um Caixa
4 - Imprimir a Lista de Clientes em Espera
5 - Imprimir o Status dos Caixas
0 - Sair
```

### Detalhamento das Opções

1. **Cadastrar Cliente**: Solicita nome, CPF, número de itens, prioridade e número do caixa
2. **Atender Cliente**: Remove o primeiro cliente da fila do caixa selecionado
3. **Abrir/Fechar Caixa**: Alterna o estado do caixa e realoca clientes se necessário
4. **Lista de Espera**: Mostra todos os clientes em cada caixa
5. **Status dos Caixas**: Exibe se cada caixa está aberto/fechado e seus clientes

## Algoritmo de Priorização

O sistema implementa uma fila com prioridades onde:

- **Prioridade 1**: Clientes são inseridos no início da fila
- **Prioridade 2**: Clientes são inseridos após todos os de prioridade 1, mas antes dos de prioridade 3
- **Prioridade 3**: Clientes são inseridos no final da fila

## Características Técnicas

- **Linguagem**: C
- **Estruturas**: Listas ligadas para implementação das filas
- **Gerenciamento de Memória**: Alocação dinâmica com liberação adequada
- **Número de Caixas**: 5 (configurável através da constante NUM_CAIXAS)

## Funções Principais

- `criar_fila()`: Cria uma nova fila vazia
- `criar_cliente()`: Cria um novo cliente com os dados fornecidos
- `enfileirar()`: Adiciona cliente na fila respeitando prioridades
- `desenfileirar()`: Remove e retorna o primeiro cliente da fila
- `inicializar_caixas()`: Inicializa todos os caixas do sistema
- `realocar_clientes()`: Redistribui clientes quando um caixa é fechado

## Exemplo de Uso

1. Execute o programa
2. Escolha opção 1 para cadastrar clientes com diferentes prioridades
3. Use opção 4 para visualizar como os clientes são organizados por prioridade
4. Teste opção 2 para atender clientes (sempre o primeiro da fila)
5. Experimente fechar um caixa (opção 3) e observe a realocação automática

## Tratamento de Erros

- Verificação de caixas válidos (1 a 5)
- Validação de estado dos caixas (aberto/fechado)
- Tratamento de filas vazias
- Liberação adequada de memória ao encerrar o programa

## Limitações

- Número fixo de caixas (5)
- Tamanhos fixos para nome (100 caracteres) e CPF (12 caracteres)
- Interface apenas por linha de comando

## Autor

Desenvolvido por Ahmed Hachem como trabalho acadêmico para a disciplina Introdução à Programação de Computadores.
