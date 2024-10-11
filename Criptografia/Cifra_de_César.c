//Autor: Tony Esaú de Oliveira© CC
//11/10/2024
//Implementa um algoritmo que encriptografa uma mensagem com caracteres ASCII com a Cifra de César.
#include <stdio.h>

void cifra_de_Cesar(char *msg, int modo, int chave){
	int i = 0;
	while(msg[i] != '\0'){
		if(msg[i] >= 'a' && msg[i] <= 'z'){
			msg[i] = ((msg[i] - 'a' + (modo ? chave : - chave)) + 26)%26 + 'a';
		}else if( msg[i] >= 'A' && msg[i] <= 'Z'){
			msg[i] = ((msg[i] - 'A' + (modo ? chave : - chave)) + 26)%26 + 'A';
		}
		i++;
	}
}

int main(){
	char mensagem[] = "abcdefghijklmnopqrstuvwxyz";
	int chave = 13;
	cifra_de_Cesar(mensagem, 1, chave);
	printf("%s \n",mensagem);
	cifra_de_Cesar(mensagem, 0, chave);
	printf("%s \n",mensagem);
}
