//Autor: Tony Esaú de Oliveira© CC
//11/02/2025
/*Implementa um algoritmo para resolver o problema das N rainhas e demonstrar as possíveis soluções. 
É um problema NP-Completo.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **tabuleiro; // Matriz alocada para tabuleiro.
    int tamanho;     
} Tabuleiro;

// Inicializa o tabuleiro com zeros, que são posições seguras.
void inicializa_tabuleiro(Tabuleiro *tabuleiro, int N) {
    tabuleiro->tamanho = N;
    tabuleiro->tabuleiro = (int **)malloc(N * sizeof(int *)); 
    for (int i = 0; i < N; i++) {
        tabuleiro->tabuleiro[i] = (int *)malloc(N * sizeof(int)); 
        for (int j = 0; j < N; j++) {
            tabuleiro->tabuleiro[i][j] = 0; // Inicializa com 0.
        }
    }
}

// Libera a memória alocada para o tabuleiro.
void libera_tabuleiro(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->tamanho; i++) {
        free(tabuleiro->tabuleiro[i]); 
    }
    free(tabuleiro->tabuleiro); 
}

// Verifica se é possível colocar uma dama na posição (linha, coluna).
int posicao_segura(Tabuleiro *tabuleiro, int linha, int coluna) {
    int N = tabuleiro->tamanho;

    // Linha à esquerda.
    for (int i = 0; i < coluna; i++) {
        if (tabuleiro->tabuleiro[linha][i] == 2)
            return 0;
    }

    // Diagonal superior à esquerda.
    for (int i = linha, j = coluna; i >= 0 && j >= 0; i--, j--) {
        if (tabuleiro->tabuleiro[i][j] == 2)
            return 0;
    }

    // Diagonal inferior à esquerda.
    for (int i = linha, j = coluna; i < N && j >= 0; i++, j--) {
        if (tabuleiro->tabuleiro[i][j] == 2)
            return 0;
    }

    return 1; // Posição segura.
}

// Função para imprimir o tabuleiro.
void imprimir_tabuleiro(Tabuleiro *tabuleiro) {
    int N = tabuleiro->tamanho;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tabuleiro->tabuleiro[i][j] == 2) {
                printf("D "); // Rainha.
            } else {
                printf(". "); // Vazio.
            }
        }
        printf("\n");
    }
}

// Função de backtracking para resolver o problema das N rainhas.
void resolver_tabuleiro(Tabuleiro *tabuleiro, int coluna, int *contador) {
    int N = tabuleiro->tamanho;

    // Todas as rainhas foram colocadas.
    if (coluna >= N) {
        (*contador)++;
        printf("Solucão %d:\n", *contador);
        imprimir_tabuleiro(tabuleiro);
        printf("\n");
        return;
    }

    // Tenta posicionar uma dama em cada linha.
    for (int i = 0; i < N; i++) {
        if (posicao_segura(tabuleiro, i, coluna)) {
            tabuleiro->tabuleiro[i][coluna] = 2; // Coloca a dama
            
            // Resolver recursivamente para a próxima coluna.
            resolver_tabuleiro(tabuleiro, coluna + 1, contador);

            tabuleiro->tabuleiro[i][coluna] = 0; // Backtrackw, retira uma rainha.
        }
    }
}

// Função principal que resolve o problema para um tabuleiro com Backtrack.
void resolver(int N) {
    Tabuleiro tabuleiro;
    int contador = 0;

    inicializa_tabuleiro(&tabuleiro, N);
    resolver_tabuleiro(&tabuleiro, 0, &contador);
    libera_tabuleiro(&tabuleiro);

    printf("Total de solucões encontradas: %d\n", contador);
}

int main() {
    int N;
    printf("Digite o tamanho do tabuleiro (tempo razoável N=12 no máximo): ");
    scanf("%d", &N);

    resolver(N);

    return 0;
}
