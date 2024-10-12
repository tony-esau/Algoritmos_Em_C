//Autor: Tony Esaú de Oliveira© CC
//11/10/2024
//Implementa um algoritmo que simula a encriptação de uma mensagem em caracteres ASCII feita por um método OTP (One Time Tap).

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Transforma um vetor de caracteres em um vetor de inteiros com a mensagem binária correspondente.
int* char_binario(char *msg, int tamanho) {
    int *binario = (int*)malloc(tamanho * 8 * sizeof(int));
    if (binario == NULL) { return NULL; }

    //Para cada caractere, transforma-o no seu binário correspondente, armazenando no vetor;
    for (int i = 0; i < tamanho; i++) {
        //Laço começa do 7 para atribuir bits começando do menos significativo;
        for (int j = 7; j >= 0; j--) {
            binario[i * 8 + (7 - j)] = (msg[i] >> j) & 1;
            /*
                - i * 8 calcula o endereço do próximo caractere;
                - +(7-j) calcula o endereço do bit atual;
                - msg[i] >> j, desloca os bits do caractere atual do bit menos significativo até o mais significativo.
                - & 1 : uma máscara, se após o deslocamento, o último bit deslocado = 1, então atribui, senão 0;
            */
        }
    }

    return binario;
}

//Transforma um vetor de inteiro com a mensagem binária em um vetor de char com a mensagem correspondente.
char* binario_char(int *binario, int tamanho) {
    //Número de caracteres;
    int tamanho_msg = tamanho / 8;
    // +1 para caractere nulo.
    char *msg = (char *)malloc((tamanho_msg + 1) * sizeof(char));
    if (msg == NULL) { return NULL; }

    //Para cada caractere que será gerado.
    for (int i = 0; i < tamanho_msg; i++) {
        char auxiliar = 0;
        for (int j = 0; j < 8; j++) {
            /*
                - << 1, desloca sempre um bit para a esquerda para que ao final os bits significativos estejam na posição correta.
                - | binario[i * 8 + j], faz um or caso o bit atual seja 1, garantindo que os significativos sejam inseridos.
            */
            auxiliar = auxiliar << 1;
            if(binario[i * 8 + j] == 1){
                auxiliar = auxiliar | binario[i * 8 + j];
            }
        }
        msg[i] = auxiliar;
    }
    msg[tamanho_msg] = '\0';

    return msg;
}

//Encriptografa com o método OTP.
int* one_time_pad(char *msg, char **msg_encriptografada) {
    int tamanho = 0;
    while (msg[tamanho] != '\0') {
        tamanho++;
    }

    int *msg_binario = char_binario(msg, tamanho);
    int *chave = (int*)malloc(tamanho * 8 * sizeof(int));
    int *binario_encriptografado = (int*)malloc(tamanho * 8 * sizeof(int));
    if (!binario_encriptografado) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    //A chave está sendo gerada e tratada para que somente caracteres ASCII printáveis sejam usados.
    for (int i = 0; i < tamanho; i++) {
        char auxiliar;
        do {
            for (int j = 0; j < 8; j++) {
                chave[i * 8 + j] = rand() % 2;
                binario_encriptografado[i * 8 + j] = msg_binario[i * 8 + j] ^ chave[i * 8 + j];
            }

            auxiliar = 0;
            for (int j = 0; j < 8; j++) {
                auxiliar = (auxiliar << 1) | binario_encriptografado[i * 8 + j];
            }
        } while (auxiliar < 33 || auxiliar > 126);
    }

    *msg_encriptografada = binario_char(binario_encriptografado, tamanho * 8);

    free(msg_binario);
    free(binario_encriptografado);

    FILE *arquivo = fopen("chave.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
    }else{
        //Salva chave para distribuição particular;
        for(int i = 0; i < 8 * tamanho;i++){
        fprintf(arquivo, "%d", chave[i]);
        }
    }

    return chave;
}

//Descriptografa aplicando a chave;
char *descriptografar(char *msg_encriptografada, int *chave){
    if(chave == NULL){return NULL;}
    int tamanho = 0;
    while (msg_encriptografada[tamanho] != '\0') {
        tamanho++;
    }

    int *binario_encriptografado = char_binario(msg_encriptografada,tamanho);
    int *binario_descriptografado = (int *)malloc(8 * tamanho * sizeof(int));

    for(int i = 0; i < 8 * tamanho; i++){
        binario_descriptografado[i] = binario_encriptografado[i] ^ chave[i];
    }

    char *msg_descriptografada = binario_char(binario_descriptografado,8 * tamanho);

    free(binario_encriptografado);
    free(binario_descriptografado);

    //Destrói a chave após o uso.
    free(chave);
    
    return msg_descriptografada;
}

/*Essa função lê uma chave binária guardada num arquivo e faz o retorno de uma chave válida utilizável.
É útil caso o usuário tenho uma mensagem encriptografada e a chave correspondente num arquivo.*/
int* ler_chave() {
    FILE *arquivo = fopen("chave.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo chave.txt.\n");
        return NULL;
    }

    int tamanho = 0;
    // Conta a quantidade de caracteres no arquivo.
    while (fgetc(arquivo) != EOF) {
        tamanho++;
    }

    // Aloca memória para a chave.
    int *chave = (int*)malloc(tamanho * sizeof(int));
    if (chave == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return NULL;
    }

    // Volta ao início do arquivo para ler os valores.
    rewind(arquivo); 

    for (int i = 0; i < tamanho; i++) {
        if (fscanf(arquivo, "%1d", &chave[i]) != 1) { 
            printf("Erro ao ler o arquivo.\n");
            free(chave);
            fclose(arquivo);
            return NULL;
        }
    }

    fclose(arquivo);
    return chave;
}

int main() {
    srand(time(NULL)); // Inicialização da seed para função rand.
    char msg[] = "This is a message encrypted with a OTP.";
    char *msg_encriptografada;
    char *msg_descriptografada;
    int *chave;

    chave = one_time_pad(msg, &msg_encriptografada);
    printf("Mensagem encriptografada: %s\n", msg_encriptografada);
    msg_descriptografada = descriptografar(msg_encriptografada,chave);
    printf("Mensagem decriptografada: %s\n", msg_descriptografada);

    free(msg_encriptografada);

    return 0;
}
