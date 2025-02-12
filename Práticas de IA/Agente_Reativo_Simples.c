//Autor: Tony Esaú de Oliveira© CC
//08/02/2025
/*Implementa um algoritmo que simula um Agente Reativo Simples de Aspirador de Pó
em dois pisos, baseado no livro do Russel e Norvig*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TEMPO_LIMITE 60
#define MINIMO 0.1

typedef struct piso {
    float piso[2];
    int posicao;
} Piso;

void limpa_tela(){
    #ifdef _WIN64
        system("cls");
    #else
        system("clear");
    #endif
}

void desenha_esquerda(Piso *piso) {
    if(piso->piso[0] <  MINIMO){
        printf("+-----------------+-----------------+\n");
        printf("|                 |                 |\n");
        printf("|                 |                 |\n");
        printf("|  _____          |                 |\n");
        printf("| /     \\         |                 |\n");
        printf("|/  ( )  \\        |                 |\n");
        printf("|\\       /        |                 |\n");
        printf("| \\_____/         |                 |\n");
        printf("|     (limpo)      |                 |\n");
        printf("+-----------------+-----------------+\n\n");
    }else{
        printf("+-----------------+-----------------+\n");
        printf("|                 |                 |\n");
        printf("|                 |                 |\n");
        printf("|  _____          |                 |\n");
        printf("| /     \\         |                 |\n");
        printf("|/  ( )  \\        |                 |\n");
        printf("|\\       /        |                 |\n");
        printf("| \\_____/         |                 |\n");
        printf("|     (%.2f)      |                 |\n", piso->piso[0]);
        printf("+-----------------+-----------------+\n\n");
    }
}

void desenha_direita(Piso *piso) {
    if(piso->piso[1] < MINIMO){
                printf("+-----------------+-----------------+\n");
        printf("|                 |                 |\n");
        printf("|                 |                 |\n");
        printf("|                 |         _____   |\n");
        printf("|                 |        /     \\  |\n");
        printf("|                 |       /  ( )  \\ |\n");
        printf("|                 |       \\       / |\n");
        printf("|                 |        \\_____/  |\n");
        printf("|                 |     (limpo)      |\n");
        printf("+-----------------+-----------------+\n");
    }else{
        printf("+-----------------+-----------------+\n");
        printf("|                 |                 |\n");
        printf("|                 |                 |\n");
        printf("|                 |         _____   |\n");
        printf("|                 |        /     \\  |\n");
        printf("|                 |       /  ( )  \\ |\n");
        printf("|                 |       \\       / |\n");
        printf("|                 |        \\_____/  |\n");
        printf("|                 |     (%.2f)      |\n", piso->piso[1]);
        printf("+-----------------+-----------------+\n");
    }
}

void direita(Piso *piso) {
    printf("Foi para a direita...\n");
    piso->posicao = 1;
    desenha_direita(piso);
}

void esquerda(Piso *piso) {
    printf("Foi para a esquerda...\n");
    piso->posicao = 0;
    desenha_esquerda(piso);
}

void aspirar(Piso *piso) {
    printf("Limpando...\n");
    while (piso->piso[piso->posicao] > 0) {
        piso->piso[piso->posicao] -= 0.24;
        if (piso->posicao == 0) {
            desenha_esquerda(piso);
        } else {
            desenha_direita(piso);
        }
        sleep(1);
        limpa_tela();
    }
}

int ambiente_limpo(Piso *piso) {
    return (piso->piso[0] <= MINIMO && piso->piso[1] <= MINIMO);
}

void gerar_sujeira(Piso *piso) {
    int chance = rand() % 100;
    if (chance < 20) {
        int lado = rand() % 2;
        piso->piso[lado] += (rand() % 3 + 1);
        printf("Apareceu mais sujeira no lado %s!\n", lado == 0 ? "esquerdo" : "direito");
    }
}

void programa_agente(Piso *piso) {
    time_t inicio, agora;
    time(&inicio);

    while (1) {
        gerar_sujeira(piso);

        if (piso->piso[piso->posicao] > 0.1) {
            aspirar(piso);
        } else if (piso->posicao == 0) {
            direita(piso);
        } else {
            esquerda(piso);
        }

        time(&agora);
        if (difftime(agora, inicio) >= TEMPO_LIMITE) {
            break;
        }

        sleep(2);
    }
}

void estado_final(Piso *piso){
        printf("+------------Estado-Final-----------+\n");
        printf("|                 |                 |\n");
        printf("|                 |                 |\n");
        printf("|                 |                 |\n");
        printf("|                 |                  |\n");
        printf("|                 |                  |\n");
        printf("|                 |                  |\n");
        printf("|                 |                  |\n");
        printf("|      (%.2f)  |      (%.2f)         |\n", piso->piso[0],piso->piso[1]);
        printf("+-----------------+-----------------+\n");
}

// Inicializa o ambiente
void inicializar_ambiente() {
    srand(time(NULL));
    Piso *piso = (Piso *)malloc(sizeof(Piso));
    piso->posicao = rand() % 2;
    piso->piso[0] = (rand() % 4);
    piso->piso[1] = (rand() % 4);

    printf("Estado Inicial:\n");
    estado_final(piso);
    sleep(5);
    programa_agente(piso);
    estado_final(piso);
    free(piso);
    printf("Simulação terminada.\n");
}


int main() {
    inicializar_ambiente();
    return 0;
}
