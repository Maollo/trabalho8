#include <stdio.h>
#include <stdlib.h>


void inicializaVet(int *vet,int tam);
int funcPos(int valor,int tam);
void guardavetor(int *vetVal, int *vetqtd,int num, int tam);
void SelectionSort(int *vetVal,int *vetQtd,int tam);


int main(int argc, char const *argv[]) {
  FILE *arq;
  int tam, num, *vetnumeros, *vetqtd, a, b;
  arq = fopen("entrada4.txt", "r");
  fscanf(arq,"%d",&a);
  fscanf(arq,"%d",&b);
  tam = (b-a+1);
  vetnumeros = (int*) malloc (sizeof(int) * tam);
  vetqtd = (int*) malloc (sizeof(int) * tam);
  inicializaVet(vetnumeros, tam);
  inicializaVet(vetqtd, tam);
  while(!feof(arq)){
    fscanf(arq,"%d",&num);
    guardavetor(vetnumeros, vetqtd, num, tam);
  }
  return 0;
}



void inicializaVet(int vet[],int tam){
    int i;
    for(i=0; i < tam; i++){
        vet[i] = 0;
    }
}


void guardavetor(int *vetVal, int *vetQtd,int num, int tam){
  int pos;
  pos = funcPos(num, tam);
  vetVal[pos] = num;
  vetQtd[pos]++;
}


int funcPos(int valor,int tam){
    int indice;
    indice = valor%tam;
    return indice;

}

void SelectionSort(int *vetQtd,int *vetVal,int tam){
    int i,j,aux,aux1;

    int menorPos;
    for (i = 0; i < tam-1; i++){
        menor = i;
        for (j = i+1; j < tam; j++){

            if (vetCont[j] > vetCont[menor]){
                menor = j;
            }
        }

        aux1 = vetComp[i];
        aux = vetCont[i];
        vetComp[i] = vetComp[menor];
        vetCont[i] = vetCont[menor];
        vetCont[menor] = aux;
        vetComp[menor] = aux1;
	}
}
