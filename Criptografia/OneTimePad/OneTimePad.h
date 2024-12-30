#ifndef INCLUDE_ONETIMEPAD
#define INCLUDE_ONETIMEPAD

void limpa_tela();
void espera();
char* ler_entrada();
int* char_binario(char *msg, int tamanho);
char* binario_char(int *binario, int tamanho);
int* one_time_pad(char *msg, char **msg_encriptografada);
char *descriptografar(char *msg_encriptografada, int *chave);
int* ler_chave();
void inicia_app();
void imprime_menu(int *opcao);

#endif