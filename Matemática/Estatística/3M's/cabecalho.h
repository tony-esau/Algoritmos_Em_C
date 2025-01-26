#ifndef INCLUDE_CABECALHO
#define INCLUDE_CABECALHO

typedef struct ponto{
    float x;
    float y;
    float z;
}Ponto;

//O ponto dos dados é a x: média, y:moda e z:mediana.
typedef struct dados{
    int *vetor;
    int tamanho;
    Ponto *ponto;
}Dados;

void limpa_tela();
void Merge(Dados *dados, int inicio, int meio, int fim);
void MergeRecursive(Dados *dados, int inicio, int fim);
void MergeSort(Dados *dados);
float moda(Dados *dados);
float media(Dados *dados);
float mediana(Dados *dados);
void preencher_dados(Dados *dados);
Dados* inicializa_dados(Dados *dados, int tamanho);
float distancia(Ponto *ponto1, Ponto *ponto2);
void printa_dados(Dados *dados);
#endif
