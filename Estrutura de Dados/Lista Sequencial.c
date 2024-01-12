#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <io.h>
#include <fcntl.h>

//Define uma função defensiva  que só aceita espaços ou caracteres alfabéticos (acentuadas ou não).
void leitor_caractere(wchar_t *string, int tamanho){
    int verificador = 0;
    do{
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
    }while(verificador == 0);
}

//Define uma função defensiva  que só aceita inteiros.
void leitor_inteiro(int *numero){
    int verificador = 0;
    wchar_t auxiliar[100];
    do
    {
        fgetws(auxiliar,100,stdin);
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
	if(lista->dados == NULL){
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

//Imprime os dados da lista
void imprime_lista(Lista *lista){
    if(lista->n_nos != 0){
        for(int i=0;i<(lista->n_nos);i++){
		printf("----------*----------\n");
		wprintf(L"[Nome:%ls.\n",lista->dados[i].nome);
		wprintf(L"Chave:%d]\n",lista->dados[i].chave);
        }
    }else{
        wprintf(L"Ainda não há nós na lista!\n");
    }
}	

//Insere um elemento na lista
Lista* insere_lista(Lista *lista, int chave){
	if((lista->n_nos)<(lista->memoria)){
		if((busca_lista(lista,chave))>=0){
			wprintf(L"O elemento de chave %d já está na lista!\n",chave);
		}else{
			lista->dados[lista->n_nos] = ler_no(chave);
			lista->n_nos++;
            wprintf(L"Nó alocado com sucesso!\n");
			return lista;
		}
	}else{
		wprintf(L"Não há mais espaço na lista!\n");
        wprintf(L"Número de espaços atual: %d.\n",lista->memoria);
	}
    return lista;
}

//Remove um nó da lista pela chave
Lista* remove_lista(Lista *lista, int chave){
    int auxiliar = busca_lista(lista, chave);
    Lista *lista_aux;
    if(auxiliar == -1){
        wprintf(L"Ainda não há nós na Lista.\n");
        return lista;
    }else if (auxiliar == -2){
        wprintf(L"Nó com essa chave não está na lista.\n");
        return lista;
    }else{
        lista_aux = criar_lista(lista->memoria);
        for(int i = auxiliar; i < lista->n_nos-1; i++){
            lista->dados[i] = lista->dados[i+1];
        }  
        if(((auxiliar == 0) && (lista->n_nos!=1))||(auxiliar!=0)){
            for(int i = 0; i < lista->n_nos-1; i++){
            lista_aux->dados[i] = lista->dados[i];
            lista_aux->n_nos++;
            }
        }
        destruir_lista(lista);
        wprintf(L"Nó removido com sucesso!\n");
    }
    return lista_aux;
}

//Edita um nó da lista pela chave
Lista* editar_no(Lista *lista, int chave){
    int auxiliar = busca_lista(lista, chave);
    if(auxiliar==-1){
        wprintf(L"Ainda não há nós na Lista.\n");
        return lista;
    }else if (auxiliar==-2){
        wprintf(L"Nó com essa chave não está na lista.\n");
        return lista;
    }else{
        lista->dados[auxiliar] = ler_no(chave);
        wprintf(L"Nó editado com sucesso!\n");
    }
    return lista;
}

void imprime_menu(){
    wprintf(L"----------*OPÇÕES*-----------\n");
    wprintf(L"-1: Inserir nó da Lista .....\n");
    wprintf(L"-2: Remover nó da Lista......\n");
    wprintf(L"-3: Editar nó da Lista.......\n");
    wprintf(L"-4: Busca por Chave .........\n");
    wprintf(L"-5: Realocar a Lista ........\n");
    wprintf(L"-6: Imprimir Lista ..........\n");
    wprintf(L"-7: Destruir Lista ..........\n");
    wprintf(L"-8: Limpar tela .............\n");
    wprintf(L"-9: Sair do Programa ........\n");
}

Lista *lista;

int main(){
    _setmode(_fileno(stdin),_O_U16TEXT);
    _setmode(_fileno(stdout),_O_U16TEXT);
    _setmode(_fileno(stderr),_O_U16TEXT);

    int opcao;
    int *ptr_opcao = &opcao;
    int chave;
    int *ptr_chave = &chave;
    int tamanho;
    int *ptr_tamanho = &tamanho;

    wprintf(L"Deseja criar uma Lista? (1:Sim|0:Não)\n");
    leitor_inteiro(ptr_opcao);
    if (opcao == 1){
        wprintf(L"Digite o tamanho da lista:\n");
        leitor_inteiro(ptr_tamanho);
        lista = criar_lista(tamanho);
    }else{
        wprintf(L"Obrigado por utilizar o programa :)...");
        exit(1);
    }

    while (opcao != 9)
    {
        imprime_menu();
        wprintf(L"Digite a opção:");
        leitor_inteiro(ptr_opcao);

        if(opcao == 1){
            wprintf(L"Digite a chave do nó que deseja inserir:\n");
            leitor_inteiro(ptr_chave);
            lista = insere_lista(lista,chave);
        }else if(opcao == 2){
            wprintf(L"Digite a chave do nó que deseja remover:\n");
            leitor_inteiro(ptr_chave);
            lista = remove_lista(lista,chave);
        }else if(opcao == 3){
            wprintf(L"Digite a chave do nó que deseja editar:\n");
            leitor_inteiro(ptr_chave);
            editar_no(lista,chave);
        }
        else if(opcao == 4){
            int auxiliar;
            wprintf(L"Digite a chave do nó:");
            leitor_inteiro(ptr_chave);
            auxiliar = busca_lista(lista,chave);
            if(auxiliar==-1){
                wprintf(L"Ainda não há nós na Lista.\n");
            }else if (auxiliar==-2){
                wprintf(L"Nó com esse elemento não está na lista\n");
            }else{
                 wprintf(L"Elemento com chave %d está no índice %d.\n",chave,auxiliar);
            }
        }else if(opcao == 5){
            int espaco;
            int *ptr_espaco = &espaco;
            wprintf(L"Digite quantos espaços novos deseja alocar:");
            leitor_inteiro(ptr_espaco);
            lista = realoca_lista(lista,espaco);
            wprintf(L"Lista realocada com sucesso!\n");
        }else if(opcao == 6){
            imprime_lista(lista);
        }else if(opcao == 7){
            destruir_lista(lista);
            wprintf(L"Lista destruída com sucesso!\n");
            wprintf(L"Deseja criar uma nova Lista? (1:Sim|0:Não)\n");
            leitor_inteiro(ptr_opcao);
            if (opcao == 1){
              wprintf(L"Digite o tamanho da lista:\n");
              leitor_inteiro(ptr_tamanho);
            lista = criar_lista(tamanho);
             }else{
                wprintf(L"Obrigado por utilizar o programa :)...");
              exit(1);
            }
        }else if(opcao == 8){
            system("cls");
        }else if(opcao == 9){
            wprintf(L"Obrigado por utilizar o programa :)...");
        }else{
            wprintf(L"Opção inválida!\n");
        }
    }

	return 0;
}

