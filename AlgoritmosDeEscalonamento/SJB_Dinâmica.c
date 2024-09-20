//Autor: Tony Esaú de Oliveira© CC
//20/09/2024
//Simula um Algoritmo de Escalonamento SJB
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para usar sleep.
#include <termios.h> //Cabeçalho de manipulação de terminal, usada para fazer função espera.
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

//Apelido para ponteiro de No_Processo, ponteiro de ponteiro
typedef struct no* Sentinela;


Sentinela* criar_lista() {
    Sentinela *Lista_processos;
    Lista_processos = (Sentinela*)malloc(sizeof(Sentinela));
    if (Lista_processos != NULL) {
        *Lista_processos = NULL;
    }
    return Lista_processos;
}

void destruir(Sentinela *Lista_Processos) {
    if (Lista_Processos != NULL) {
        No_Processo *Temporario;
        while (*Lista_Processos != NULL) {
            Temporario = *Lista_Processos;
            *Lista_Processos = (*Lista_Processos)->Ptr_Proximo;
            free(Temporario);
        }
    }
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

//Insere um processo de forma ordenada em relação ao tempo de execução.
int inserir_processo(Sentinela *Lista_Processos) {
    if (Lista_Processos == NULL) {
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
        if ((*Lista_Processos) == NULL || ((*Lista_Processos)->processo.Tamanho > Novo_Processo->processo.Tamanho)) {
            Novo_Processo->Ptr_Proximo = *Lista_Processos;
            *Lista_Processos = Novo_Processo;
        }
        else {
            No_Processo *Anterior = *Lista_Processos;
            No_Processo *Temporario = Anterior->Ptr_Proximo;
            while (Temporario != NULL && Temporario->processo.Tamanho < Novo_Processo->processo.Tamanho) {
                Anterior = Temporario;
                Temporario = Temporario->Ptr_Proximo;
            }
            Anterior->Ptr_Proximo = Novo_Processo;
            Novo_Processo->Ptr_Proximo = Temporario;
        }
        return 1;
    }
}

//Remove o processo de menor tamanho.
int remover_processo(Sentinela *Lista_Processos) {
    if (*Lista_Processos == NULL) {
            printf("Lista vazia!");
        return 0;
    }else {
        No_Processo *Temporario = *Lista_Processos;
        *Lista_Processos = Temporario->Ptr_Proximo;
        free(Temporario);
        return 1;
    }
}

void imprimir_lista(Sentinela *Lista_Processos){
    if(*Lista_Processos != NULL){
        No_Processo *Ptr_Navegante = *Lista_Processos;
        while(Ptr_Navegante != NULL){
            printf("[\nId:%d, \n Tamanho:%d Bytes, \n Tempo de Execução :%d s\n]\n",
            Ptr_Navegante->processo.Id,
            Ptr_Navegante->processo.Tamanho,
            Ptr_Navegante->processo.Tempo
            );
            Ptr_Navegante = Ptr_Navegante->Ptr_Proximo;
        }
    }else{
        printf("Lista vazia!");
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

void limpa_tela(){
    #ifdef _WIN64
        system("cls");
    #else
        system("clear");
    #endif
}

void espera() {
    struct termios config_atual, config_nova;
    char c;

    // Salva as configurações antigas do terminal.
    tcgetattr(STDIN_FILENO, &config_atual);
    config_nova = config_atual;

    // Desativa o eco e as configurações de entrada.
    config_nova.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &config_nova);

    printf("Pressione qualquer tecla para continuar...\n");

    // Espera por uma entrada de tecla.
    read(STDIN_FILENO, &c, 1);

    // Restaura as configurações antigas do terminal.
    tcsetattr(STDIN_FILENO, TCSANOW, &config_atual);
}


//Faz uma simulação sobre a remoção sucessiva dos processos da Fila.
void simulacao(Sentinela *Lista_Processos){
    limpa_tela();
    if((*Lista_Processos) == NULL){
        printf("Impossível realizar simulação. Fila Vazia!");
    }else{
        No_Processo *Ptr_Navegante = (*Lista_Processos);
        printf("-Iniciando simulação-");
        sleep(2);
        while(Ptr_Navegante != NULL){
            printf("\n-----------------------------\n");
            printf("\nConfiguração atual da fila é:\n");
            sleep(2);
            imprimir_lista(Lista_Processos);
            sleep(3);
            printf("Removendo processo de Id: %d\n",Ptr_Navegante->processo.Id);
            sleep(2);
            int tempo_execucao = Ptr_Navegante->processo.Tempo;
            Ptr_Navegante = Ptr_Navegante->Ptr_Proximo;
            remover_processo(Lista_Processos);
            printf("<Processo removido com sucesso!>\n");
            printf("Executando processo");
            simula_execucao(tempo_execucao);
            printf("<Processo executado com sucesso!>\n");
        }
        printf("<Simulação encerrada>\n");
        espera();
    }
}

void imprime_menu(){
    printf("\n----------Opções----------\n");
    printf("1-Inserir Processo..........\n");
    printf("2-Remover Processo..........\n");
    printf("3-Imprimir Processo(s)......\n");
    printf("4-Limpar Tela...............\n");
    printf("5-Iniciar Simulação.........\n");
    printf("6-Sair......................\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");//Define caracteres em Português.
    Sentinela *Lista_Processos;
    Lista_Processos = NULL;
    Lista_Processos = criar_lista();
    int verificador;

    while(verificador != 6){
        imprime_menu();
        scanf("%d",&verificador);
        getchar();

        if(verificador == 1){
            inserir_processo(Lista_Processos);
        }else if(verificador == 2){
            remover_processo(Lista_Processos);
        }else if(verificador == 3){
            system("cls");
            imprimir_lista(Lista_Processos);
        }else if(verificador == 4){
            limpa_tela();
        }else if(verificador == 5){
            simulacao(Lista_Processos);
        }else if(verificador == 6){
            exit(1);
        }else{
           printf("Comando inexistente.");
        }
    }
   return 0;
}


