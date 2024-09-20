//Autor: Tony Esaú de Oliveira© CC
//19/09/2024
//Simula uma fila de Escalonamento(FCFS)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para usar sleep.
#include <locale.h> //Para permitir printar caracteres em português.
#define Velocidade_Processamento 1000 //Bytes/s, por didática.

//Define processo, com seu ID, tamanho e Tempo de execução.
typedef struct processo{
    int Tamanho;
    int Tempo;
    int Id;
}Processo;

//Nó com o processo respectivo e o ponteiro para o próximo.
typedef struct no {
    Processo processo;
    struct no *Ptr_Proximo;
}No_Processo;

//Estrutura Especial que representa a Fila.
typedef struct sentinela{
    No_Processo *Ptr_Inicio;
    No_Processo *Ptr_Fim;
}Sentinela;

//Cria a fila alocando-a dinamicamente.
Sentinela* criar_fila() {
    Sentinela *Inicializador;
    Inicializador = (Sentinela*)malloc(sizeof(Sentinela));
    if (Inicializador != NULL) {
        Inicializador->Ptr_Inicio = NULL;
        Inicializador->Ptr_Fim = NULL;
    }else{
        printf("Erro de Memoria. Abortando...");
        exit(1);
    }
    return Inicializador;
}

//Destrói a fila percorrendo-a e liberando a memória alocada.
void destruir(Sentinela *Fila_Processos) {
    if (Fila_Processos != NULL) {
        No_Processo *Temporario;
        while (Fila_Processos->Ptr_Inicio != NULL) {
            Temporario = Fila_Processos->Ptr_Inicio;
            Fila_Processos->Ptr_Inicio = Fila_Processos->Ptr_Inicio->Ptr_Proximo;
            free(Temporario);
        }
        Fila_Processos->Ptr_Fim = NULL;
        free(Temporario);
    }
}

//Retorna o tamanho da fila, função auxiliar;
int tamanho(Sentinela *Fila_Processos) {
    if (Fila_Processos->Ptr_Inicio == Fila_Processos->Ptr_Fim) {
        return 0;
    }
    int contador = 0;
    No_Processo *Ptr_Navegante = Fila_Processos->Ptr_Inicio;
    while (Ptr_Navegante != NULL) {
        contador++;
        Ptr_Navegante = Ptr_Navegante->Ptr_Proximo;
    }
    return contador;
}

//Inicializa um processo tomando seus valores.
Processo Inicializar_Processo(){
    Processo Auxiliar;
    int tamanho;
    int id;
    printf("Digite o tamanho de processamento em Bytes:");
    scanf("%d",&tamanho);
    getchar();
    int tempo;
    tempo = (int)tamanho/Velocidade_Processamento;
    printf("Digite o Id do processo:");
    scanf("%d",&id);
    Auxiliar.Tamanho = tamanho;
    Auxiliar.Tempo= tempo;
    Auxiliar.Id = id;

    return Auxiliar;
}

//Insere um processo no final da Fila.
int inserir_processo(Sentinela *Fila_Processos) {
    if (Fila_Processos == NULL) {
        printf("Erro de Memória...");
        return 0;
    }else {
        No_Processo *Novo_Processo = (No_Processo*)malloc(sizeof(No_Processo));
        if (Novo_Processo == NULL){
            printf("Erro de Memória...");
            return 0;
        }
        Processo processo = Inicializar_Processo();
        Novo_Processo->processo = processo;
        Novo_Processo->Ptr_Proximo = NULL;
        if (Fila_Processos->Ptr_Fim == NULL) {
            Fila_Processos->Ptr_Inicio = Novo_Processo;
        }else {
            Fila_Processos->Ptr_Fim->Ptr_Proximo = Novo_Processo;
        }
        Fila_Processos->Ptr_Fim = Novo_Processo;
        return 1;
    }
}

//Remove um processo do começo da fila (FIFO).
int remover_processo(Sentinela *Fila_Processos) {
    if (Fila_Processos->Ptr_Inicio == NULL) {
        printf("Fila vazia!");
        return 0;
    }else {
        No_Processo *Temporario = Fila_Processos->Ptr_Inicio;
        Fila_Processos->Ptr_Inicio = Fila_Processos->Ptr_Inicio->Ptr_Proximo;
        if (Fila_Processos->Ptr_Inicio == NULL) {
            Fila_Processos->Ptr_Fim = NULL;
        }
        free(Temporario);
        return 1;
    }
}

//Imprime a fila percorrendo-a.
void imprimir_fila(Sentinela *Fila_Processos){
    if(Fila_Processos->Ptr_Inicio != NULL){
        No_Processo *Ptr_Navegante = Fila_Processos->Ptr_Inicio;
        while(Ptr_Navegante != NULL){
            printf("[\nId:%d, \n Tamanho:%d Bytes, \n Tempo de Execução:%d s\n]\n",
            Ptr_Navegante->processo.Id,
            Ptr_Navegante->processo.Tamanho,
            Ptr_Navegante->processo.Tempo
            );
            Ptr_Navegante = Ptr_Navegante->Ptr_Proximo;
        }
    }else{
        printf("Fila vazia!");
    }
}

//Simula o tempo de execução printando um ponto a cada 2 segundos decorrido.
void simula_execucao(int tempo_total){
    int tempo_por_ponto = 2; //
    int tempo_restante = tempo_total;
    while (tempo_restante > 0) {
        putchar('.');
        fflush(stdout);
        sleep(tempo_por_ponto);
        tempo_restante -= tempo_por_ponto;
    }
    printf("\n");
}

//Faz uma simulação sobre a remoção sucessiva dos processos da Fila.
void simulacao(Sentinela *Fila_Processos){
    system("cls");
    if(Fila_Processos->Ptr_Inicio == NULL){
        printf("Impossível realizar simulação. Fila Vazia!");
    }else{
        No_Processo *Ptr_Navegante = Fila_Processos->Ptr_Inicio;
        printf("-Iniciando simulação-");
        sleep(2);
        while(Ptr_Navegante != NULL){
            printf("\n-----------------------------\n");
            printf("\nConfiguração atual da fila é:\n");
            sleep(2);
            imprimir_fila(Fila_Processos);
            sleep(3);
            printf("Removendo processo de Id: %d\n",Ptr_Navegante->processo.Id);
            sleep(2);
            int tempo_execucao = Ptr_Navegante->processo.Tempo;
            Ptr_Navegante = Ptr_Navegante->Ptr_Proximo;
            remover_processo(Fila_Processos);
            printf("<Processo removido com sucesso!>\n");
            printf("Executando processo");
            simula_execucao(tempo_execucao);
            printf("<Processo executado com sucesso!>\n");
        }
        printf("Simulação encerrada.");
    }
}

//Imprime o Menu de Escolha
void imprime_menu(){
    printf("\n----------Opções----------\n");
    printf("1-Inserir Processo..........\n");
    printf("2-Remover Processo..........\n");
    printf("3-Imprimir Processo(s)......\n");
    printf("4-Limpar Tela...............\n");
    printf("5-Iniciar Simulação.........\n");
    printf("6-Sair......................\n");
}

void limpa_tela(){
    #ifdef _WIN64
    system("cls");
    #else
    system("clear");
    #endif
}

int main() {
    setlocale(LC_ALL, "Portuguese");//Define caracteres em Português.
    Sentinela *Fila_Processos;
    Fila_Processos = NULL;
    Fila_Processos = criar_fila();
    int verificador;

    while(verificador != 6){
        imprime_menu();
        scanf("%d",&verificador);
        fflush(stdin);

        if(verificador == 1){
            inserir_processo(Fila_Processos);
        }else if(verificador == 2){
            remover_processo(Fila_Processos);
        }else if(verificador == 3){
            system("cls");
            imprimir_fila(Fila_Processos);
        }else if(verificador == 4){
            limpa_tela();
        }else if(verificador == 5){
            simulacao(Fila_Processos);
        }else if(verificador == 6){
            exit(1);
        }else{
           printf("Comando inexistente.");
        }
    }
   return 0;
}



