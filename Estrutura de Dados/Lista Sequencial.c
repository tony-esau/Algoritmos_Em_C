#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <io.h>
#include <fcntl.h>

//Define uma função defensiva  que só aceita espaços ou caracteres alfabéticos (acentuadas ou não).
void leitor_caractere(wchar_t *string, int tamanho){
    int verificador = 0;
    do
    {
        fgetws(string,tamanho,stdin);
        //Retira o \n vindo do teclado.
        for(int i = 0; string[i] != L'\0'; i++){
            if(string[i] == L'\n'){
                string[i] = '\0'; 
            }
        }

        for(int i = 0;  string[i] != L'\0'; i++){
            if( (iswalpha(string[i]) != 0) || (iswspace(string[i]) != 0) ){
                verificador = 1;
            }else{
                wprintf(L"Digite somente letras ou espaços.\n");
                verificador = 0;
                break;
            }
        }  
    }while(verificador==0);
}

//Define uma função defensiva  que só aceita inteiros.
void leitor_inteiro(int *numero){
    int verificador = 0;
    wchar_t auxiliar[1000];
    do
    {
        fgetws(auxiliar,1000,stdin);
        //Retira o \n vindo do teclado.
        for(int i = 0; auxiliar[i] != L'\0'; i++){
            if(auxiliar[i] == L'\n'){
                auxiliar[i] = '\0'; 
            }
        }

        for(int i = 0;  auxiliar[i] != L'\0'; i++){
            if( iswdigit(auxiliar[i]) != 0){
                verificador = 1;
            }else{
                wprintf(L"Digite uma sequência numérica válida.\n");
                verificador = 0;
                break;
            }
        }  
    }while(verificador==0);
    *numero = (int) wcstol(auxiliar,NULL,10);
}

//São os dados da Lista Sequencial
typedef struct dados {
	wchar_t nome[100];
	int chave;
} Dados;

//É um Sentinela da lista de Dados
typedef struct lista {
	Dados *dados;
	int n_nos;
	int memoria;
} Lista;

//Função de criar lista
Lista* criar_lista(int tamanho){
	Lista *sentinela = (Lista*) malloc(sizeof(Lista));
	if(sentinela == NULL){
		wprintf(L"Falha de memória! Encerrando programa...");
		exit(1);
	}
	sentinela->dados = (Dados*)malloc(tamanho * (sizeof(Dados)));
	if(sentinela->dados == NULL){
		wprintf(L"Falha de memória! Encerrando programa...");
		exit(1);
	}
	sentinela->n_nos = 0;
	sentinela->memoria = tamanho;
	return sentinela;
}

//Destrói a lista liberando a memória alocada
void destruir_lista(Lista *lista){
	free(lista->dados);
	free(lista);
}

//Realoca uma nova posição na memória da lista
Lista* realoca_lista(Lista *lista, int n){
	lista->dados = (Dados*) realloc(lista->dados,(lista->memoria+n)*sizeof(Dados));
	if(lista->dados==NULL){
		wprintf(L"Falha de memória! Encerrando programa...");
		exit(1);
	}
	lista->memoria+=n;
	return lista;
}

//Busca um elemento nos dados da lista pela chave
int busca_lista(Lista *lista, int chave){
	if(lista->n_nos==0){
		return -1;
	}else{
		for(int i=0;i<(lista->n_nos);i++){
			if(lista->dados[i].chave==chave){
				return i;
			}
		}
	}
	return -2;
}

//Ler um nó de um tipo Dados
Dados ler_no(int chave){
	Dados auxiliar;
	wprintf(L"Digite o nome:");
	wchar_t *p_nome = &auxiliar.nome[0];
	leitor_caractere(p_nome,100);
	auxiliar.chave=chave;
	return auxiliar;
}

//Insere um elemento na lista
Lista* insere_lista(Lista *lista, int chave){
	if((lista->n_nos)<(lista->memoria)){
		if((busca_lista(lista,chave))>=0){
			wprintf(L"O elemento de chave %d já está na lista!",chave);
		}else{
			lista->dados[lista->n_nos] = ler_no(chave);
			lista->n_nos+=1;
			return lista;
		}
	}else{
		wprintf(L"Não há mais espaço na lista!");
	}
	return NULL;
}

//Imprime os dados da lista
void imprime_lista(Lista *lista){
	for(int i=0;i<(lista->n_nos);i++){
		printf("----------*----------\n");
		wprintf(L"[Nome:%ls.\n",lista->dados[i].nome);
		wprintf(L"Chave:%d]\n",lista->dados[i].chave);
	}
}

void imprime_menu(){
    wprintf(L"----------*OPÇÕES*-----------\n");
    wprintf(L"-1: Criar Lista -------------\n");
    wprintf(L"-2: Inserer na Lista --------\n");
    wprintf(L"-3: Busca por Chave ---------\n");
    wprintf(L"-4: Realocar a Lista --------\n");
    wprintf(L"-5: Imprimir Lista ----------\n");
    wprintf(L"-6: Destruir Lista ----------\n");
}

int main(){
    _setmode(_fileno(stdin),_O_U16TEXT);
    _setmode(_fileno(stdout),_O_U16TEXT);
    _setmode(_fileno(stderr),_O_U16TEXT);

    imprime_menu();
	return 0;
}