#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para representar um componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis globais para contagem de comparações
int comparacoes_bubble = 0;
int comparacoes_insertion = 0;
int comparacoes_selection = 0;
int comparacoes_busca = 0;

/**
 * Função para limpar o buffer de entrada
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Função para cadastrar componentes
 * @param componentes: vetor de componentes
 * @param quantidade: ponteiro para quantidade atual
 * @return nova quantidade de componentes
 */
int cadastrarComponentes(Componente componentes[], int *quantidade) {
    int qtd;
    printf("\nQuantos componentes deseja cadastrar? (max %d): ", 20 - *quantidade);
    scanf("%d", &qtd);
    limparBuffer();
    
    if (*quantidade + qtd > 20) {
        printf("Limite maximo de 20 componentes excedido!\n");
        return *quantidade;
    }
    
    for (int i = *quantidade; i < *quantidade + qtd; i++) {
        printf("\n=== Componente %d ===\n", i + 1);
        
        printf("Nome: ");
        fgets(componentes[i].nome, 30, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = 0; // Remove \n
        
        printf("Tipo (controle/suporte/propulsao): ");
        fgets(componentes[i].tipo, 20, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = 0;
        
        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[i].prioridade);
        limparBuffer();
        
        // Valida prioridade
        if (componentes[i].prioridade < 1) componentes[i].prioridade = 1;
        if (componentes[i].prioridade > 10) componentes[i].prioridade = 10;
    }
    
    *quantidade += qtd;
    printf("\n%d componentes cadastrados com sucesso!\n", qtd);
    return *quantidade;
}

/**
 * Bubble Sort para ordenar por nome
 * @param componentes: vetor de componentes
 * @param n: quantidade de componentes
 */
void bubbleSortNome(Componente componentes[], int n) {
    comparacoes_bubble = 0;
    clock_t inicio = clock();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes_bubble++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os componentes
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Bubble Sort concluido! Comparacoes: %d, Tempo: %.6f segundos\n", 
           comparacoes_bubble, tempo);
}

/**
 * Insertion Sort para ordenar por tipo
 * @param componentes: vetor de componentes
 * @param n: quantidade de componentes
 */
void insertionSortTipo(Componente componentes[], int n) {
    comparacoes_insertion = 0;
    clock_t inicio = clock();
    
    for (int i = 1; i < n; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes_insertion++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Insertion Sort concluido! Comparacoes: %d, Tempo: %.6f segundos\n", 
           comparacoes_insertion, tempo);
}

/**
 * Selection Sort para ordenar por prioridade
 * @param componentes: vetor de componentes
 * @param n: quantidade de componentes
 */
void selectionSortPrioridade(Componente componentes[], int n) {
    comparacoes_selection = 0;
    clock_t inicio = clock();
    
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes_selection++;
            if (componentes[j].prioridade < componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }
        // Troca os componentes
        Componente temp = componentes[min_idx];
        componentes[min_idx] = componentes[i];
        componentes[i] = temp;
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Selection Sort concluido! Comparacoes: %d, Tempo: %.6f segundos\n", 
           comparacoes_selection, tempo);
}

/**
 * Busca binária por nome (requer vetor ordenado por nome)
 * @param componentes: vetor de componentes ordenado
 * @param n: quantidade de componentes
 * @param nome: nome a ser buscado
 * @return índice do componente ou -1 se não encontrado
 */
int buscaBinariaPorNome(Componente componentes[], int n, char nome[]) {
    comparacoes_busca = 0;
    clock_t inicio = clock();
    
    int esquerda = 0;
    int direita = n - 1;
    int resultado = -1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoes_busca++;
        
        int comparacao = strcmp(componentes[meio].nome, nome);
        
        if (comparacao == 0) {
            resultado = meio;
            break;
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("Busca Binaria concluida! Comparacoes: %d, Tempo: %.6f segundos\n", 
           comparacoes_busca, tempo);
    
    return resultado;
}

/**
 * Exibe todos os componentes formatados
 * @param componentes: vetor de componentes
 * @param n: quantidade de componentes
 */
void mostrarComponentes(Componente componentes[], int n) {
    if (n == 0) {
        printf("Nenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n=== LISTA DE COMPONENTES (%d) ===\n", n);
    printf("-------------------------------------------------\n");
    printf("| %-20s | %-15s | %-10s |\n", "NOME", "TIPO", "PRIORIDADE");
    printf("-------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("| %-20s | %-15s | %-10d |\n", 
               componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    printf("-------------------------------------------------\n");
}

/**
 * Função para medir tempo de execução de um algoritmo
 * @param algoritmo: ponteiro para função de ordenação
 * @param componentes: vetor de componentes
 * @param n: quantidade de componentes
 */
void medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int n) {
    printf("Medindo tempo de execucao...\n");
    algoritmo(componentes, n);
}

/**
 * Menu principal interativo
 */
void menu() {
    Componente componentes[20];
    int quantidade = 0;
    int opcao;
    int ordenado_por_nome = 0; // Flag para verificar se está ordenado por nome
    
    do {
        printf("\n=== SISTEMA DE MONTAGEM DE TORRE ===\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Mostrar componentes\n");
        printf("3. Ordenar por nome (Bubble Sort)\n");
        printf("4. Ordenar por tipo (Insertion Sort)\n");
        printf("5. Ordenar por prioridade (Selection Sort)\n");
        printf("6. Buscar componente por nome (Busca Binaria)\n");
        printf("7. Iniciar montagem final\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                cadastrarComponentes(componentes, &quantidade);
                ordenado_por_nome = 0; // Reset da flag ao adicionar novos componentes
                break;
                
            case 2:
                mostrarComponentes(componentes, quantidade);
                break;
                
            case 3:
                if (quantidade > 0) {
                    bubbleSortNome(componentes, quantidade);
                    ordenado_por_nome = 1;
                    mostrarComponentes(componentes, quantidade);
                } else {
                    printf("Nenhum componente para ordenar!\n");
                }
                break;
                
            case 4:
                if (quantidade > 0) {
                    insertionSortTipo(componentes, quantidade);
                    mostrarComponentes(componentes, quantidade);
                    ordenado_por_nome = 0;
                } else {
                    printf("Nenhum componente para ordenar!\n");
                }
                break;
                
            case 5:
                if (quantidade > 0) {
                    selectionSortPrioridade(componentes, quantidade);
                    mostrarComponentes(componentes, quantidade);
                    ordenado_por_nome = 0;
                } else {
                    printf("Nenhum componente para ordenar!\n");
                }
                break;
                
            case 6:
                if (quantidade > 0) {
                    if (!ordenado_por_nome) {
                        printf("AVISO: Vetor nao esta ordenado por nome. Ordenando primeiro...\n");
                        bubbleSortNome(componentes, quantidade);
                        ordenado_por_nome = 1;
                    }
                    
                    char nome_busca[30];
                    printf("Digite o nome do componente a buscar: ");
                    fgets(nome_busca, 30, stdin);
                    nome_busca[strcspn(nome_busca, "\n")] = 0;
                    
                    int indice = buscaBinariaPorNome(componentes, quantidade, nome_busca);
                    
                    if (indice != -1) {
                        printf("\n>>> COMPONENTE ENCONTRADO! <<<\n");
                        printf("Nome: %s\n", componentes[indice].nome);
                        printf("Tipo: %s\n", componentes[indice].tipo);
                        printf("Prioridade: %d\n", componentes[indice].prioridade);
                        printf("Este e o componente-chave para iniciar a montagem!\n");
                    } else {
                        printf("Componente '%s' nao encontrado!\n", nome_busca);
                    }
                } else {
                    printf("Nenhum componente para buscar!\n");
                }
                break;
                
            case 7:
                if (quantidade > 0) {
                    printf("\n=== INICIANDO MONTAGEM FINAL ===\n");
                    printf("Sequencia de montagem ordenada por prioridade:\n");
                    
                    // Ordena por prioridade para a montagem final
                    selectionSortPrioridade(componentes, quantidade);
                    
                    printf("\nORDEM DE MONTAGEM:\n");
                    for (int i = 0; i < quantidade; i++) {
                        printf("%d. [P%d] %s (%s)\n", 
                               i + 1, componentes[i].prioridade, 
                               componentes[i].nome, componentes[i].tipo);
                    }
                    
                    printf("\n=== TORRE MONTADA COM SUCESSO! ===\n");
                } else {
                    printf("Nenhum componente para montar!\n");
                }
                break;
                
            case 0:
                printf("Saindo do sistema...\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
        }
        
    } while (opcao != 0);
}

/**
 * Função principal
 */
int main() {
    printf("=== SISTEMA DE MONTAGEM INTELIGENTE ===\n");
    printf("Cadastre ate 20 componentes e organize a montagem da torre\n");
    
    menu();
    
    return 0;
}