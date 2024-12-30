#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <termios.h> 
#include <time.h>
#include "OneTimePad.h"

void limpa_tela(){
    #ifdef _WIN64
        system("cls");
    #else
        system("clear");
    #endif
}

void espera() {
    struct termios config_atual, config_nova;
    char buffer[8];

    // Salva as configurações antigas do terminal.
    tcgetattr(STDIN_FILENO, &config_atual);
    config_nova = config_atual;

    // Desativa o eco e as configurações de entrada.
    config_nova.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &config_nova);

    printf("Pressione qualquer tecla para continuar...\n");

    // Espera por uma entrada de tecla.
    read(STDIN_FILENO, buffer, sizeof(buffer));

    // Restaura as configurações antigas do terminal.
    tcsetattr(STDIN_FILENO, TCSANOW, &config_atual);
}

char* ler_entrada() {
    char *mensagem = NULL;
    int tamanho = 0;        // Tamanho total alocado
    int comprimento = 0;    // Número de caracteres lidos
    int c;                  // Caractere atual

    getchar();
    // Leitura efetiva
    while ((c = getchar()) != '\n' && c != EOF) {
        if (comprimento + 1 >= tamanho) {
            // Realoca em blocos maiores para reduzir realocações frequentes
            tamanho = tamanho == 0 ? 16 : tamanho * 2;
            char *aux = realloc(mensagem, tamanho);
            if (!aux) {
                free(mensagem);
                fprintf(stderr, "Erro ao alocar memória.\n");
                exit(EXIT_FAILURE);
            }
            mensagem = aux;
        }

        mensagem[comprimento++] = c; // Adiciona o caractere ao buffer
    }

    if (mensagem) {
        mensagem[comprimento] = '\0'; // Finaliza a string com '\0'
    } else {
        // Caso mensagem seja NULL (entrada vazia)
        mensagem = malloc(1);
        if (!mensagem) {
            fprintf(stderr, "Erro ao alocar memória.\n");
            exit(EXIT_FAILURE);
        }
        mensagem[0] = '\0'; // Inicializa com string vazia
    }

    return mensagem;
}


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
	srand(time(NULL)); // Inicialização da seed para função rand.
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

    char nome_arquivo[1000];

    printf("Digite o nome do arquivo o qual deseja salvar a chave: ");
    fgets(nome_arquivo, 999, stdin);

	// Remove o \n se ele existir
	for(int i = 0; nome_arquivo[i] != '\0';i++){
	    if(nome_arquivo[i]=='\n'){
	        nome_arquivo[i]='\0';
	    }
	 }

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        free(chave);
        return NULL;
    }else{
        //Salva chave para distribuição particular;
        for(int i = 0; i < 8 * tamanho;i++){
        fprintf(arquivo, "%d", chave[i]);
        }
    }
    fclose(arquivo);
    printf("Chave salva com sucesso.\n");

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
	char nome_arquivo[1000];
	printf("Digite o nome do arquivo o qual deseja abrir a chave:");
    fgets(nome_arquivo, 999, stdin);

	// Remove o \n se ele existir
	for(int i = 0; nome_arquivo[i] != '\0';i++){
	    if(nome_arquivo[i]=='\n'){
	        nome_arquivo[i]='\0';
	    }
	}

    FILE *arquivo = fopen(nome_arquivo, "r");
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

void inicia_app(){
	int opcao;
	int *ptr = &opcao;
	printf("    _____________________________________\n");
    printf("   /                                     \\\n");
    printf("  |         Encriptografador OTP          |\n");
    printf("   \\_____________________________________/\n");
    printf("          \\\n");
    printf("           \\   .--.\n");
    printf("              |o_o |\n");
    printf("              |:_/ |\n");
    printf("             //   \\ \\\n");
    printf("            (|     | )\n");
    printf("           /'\\_   _/`\\\n");
    printf("           \\___)=(___/\n\n");
	printf("....................versão 1.2...tony_esau©\n");
	espera();
	limpa_tela();
	do{
		imprime_menu(ptr);
	}while(opcao != 4);
	printf("--Obrigado por utilizar =)--\n");
}

void imprime_menu(int *opcao){
	limpa_tela();
	char *mensagem;
	printf("--------------------Menu-------------------\n");
	printf("- 1. Encriptografar Mensagem do Teclado...-\n");
	printf("- 2. Descriptografar a partir de Chave....-\n");
	printf("- 3. Sobre................................-\n");
    printf("- 4. Sair.................................-\n");
	printf("- Digite a sua opção:                     -\n");
	printf("-------------------------------------------\n");
	scanf("%d", opcao);
	limpa_tela();
	if(*opcao == 1){
		char *msg_retorno;
		printf("    _____________________________________\n");
	    printf("   /                                     \\\n");
	    printf("  |         Digite sua Mensagem           |\n");
	    printf("   \\_____________________________________/\n");
	    printf("          \\\n");
	    printf("           \\   .--.\n");
	    printf("              |o_o |\n");
	    printf("              |:_/ |\n");
	    printf("             //   \\ \\\n");
	    printf("            (|     | )\n");
	    printf("           /'\\_   _/`\\\n");
	    printf("           \\___)=(___/\n\n");
	    printf("Mensagem: ");
		mensagem = ler_entrada();
		one_time_pad(mensagem, &msg_retorno);
		limpa_tela();
		printf("    _____________________________________\n");
	    printf("   /                                     \\\n");
	    printf("  |         Mensagem Encriptografada:     |\n");
	    printf("           %s                 \n", msg_retorno);
	    printf("   \\_____________________________________/\n");
	    printf("          \\\n");
	    printf("           \\   .--.\n");
	    printf("              |o_o |\n");
	    printf("              |:_/ |\n");
	    printf("             //   \\ \\\n");
	    printf("            (|     | )\n");
	    printf("           /'\\_   _/`\\\n");
	    printf("           \\___)=(___/\n\n");
		espera();
	}else if(*opcao == 2){
		printf("    _____________________________________\n");
	    printf("   /                                     \\\n");
	    printf("  |         Digite sua Mensagem           |\n");
	    printf("   \\_____________________________________/\n");
	    printf("          \\\n");
	    printf("           \\   .--.\n");
	    printf("              |o_o |\n");
	    printf("              |:_/ |\n");
	    printf("             //   \\ \\\n");
	    printf("            (|     | )\n");
	    printf("           /'\\_   _/`\\\n");
	    printf("           \\___)=(___/\n\n");
	    printf("Mensagem: ");
		mensagem = ler_entrada();
		int *chave = ler_chave();
		limpa_tela();
		mensagem = descriptografar(mensagem, chave);
		if(mensagem != NULL){
			printf("    _____________________________________\n");
		    printf("   /                                     \\\n");
		    printf("  |         Mensagem Descriptografada:    |\n");
		    printf("           %s                     \n", mensagem);
		    printf("   \\_____________________________________/\n");
		    printf("          \\\n");
		    printf("           \\   .--.\n");
		    printf("              |o_o |\n");
		    printf("              |:_/ |\n");
		    printf("             //   \\ \\\n");
		    printf("            (|     | )\n");
		    printf("           /'\\_   _/`\\\n");
		    printf("           \\___)=(___/\n\n");
		}else{
			printf("    ______________________________________________\n");
		    printf("   /                                              \\\n");
		    printf("  |  Arquivo Não Encontrado! Digitou corretamente? |\n");
		    printf("   \\______________________________________________/\n");
		    printf("          \\\n");
		    printf("           \\   .--.\n");
		    printf("              |o_o |\n");
		    printf("              |:_/ |\n");
		    printf("             //   \\ \\\n");
		    printf("            (|     | )\n");
		    printf("           /'\\_   _/`\\\n");
		    printf("           \\___)=(___/\n\n");
		}
		espera();
	}else if(*opcao == 3){
        printf("+++++++++++++++++++++++OTP+++++++++++++++++++++\n");
        printf("+ O One-Time Pad é uma cifra de uso único. Se +\n");
        printf("+ usada corretamente, é inquebrável! Consiste +\n");
        printf("+ numa cifra em que o purotexto é combinado   +\n");
        printf("+ caractere a caractere com uma chave secreta +\n");
        printf("+ aleatória de tamanho no mínimo da mensagem  +\n");
        printf("+ do purotexto. Para que seja imperscrutável, +\n");
        printf("+ é necessário que a chave seja movida por    +\n");
        printf("+ ambientes seguros e que seja utilizada so-  +\n");
        printf("+ mente uma única vez.                        +\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
        espera();
    }else if(*opcao != 4){
		printf("    _____________________________________\n");
	    printf("   /                                     \\\n");
	    printf("  |              Opção Inválida           |\n");
	    printf("   \\_____________________________________/\n");
	    printf("          \\\n");
	    printf("           \\   .--.\n");
	    printf("              .\\ /.    \n");
	    printf("              |o_o |\n");
	    printf("              |:_/ |\n");
	    printf("             //   \\ \\\n");
	    printf("            (|     | )\n");
	    printf("           /'\\_   _/`\\\n");
	    printf("           \\___)=(___/\n\n");
	    espera();
		imprime_menu(opcao);
	}
}
