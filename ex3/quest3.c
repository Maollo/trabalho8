#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct estruturaALuno{
  char nome[30];
  int idade;
};

typedef struct estruturaALuno tipoAluno;

void Quick(tipoAluno *alunos, int inicio, int fim);



int main(){
  tipoAluno alunos[50];
  FILE *arq;
  int i,j, qtd;
  char entrada[50],idade[4], nome[50],espaco[2], *frase;
  arq = fopen("entrada3.txt", "r");
  strcpy(espaco, " ");
  j = 0;
  qtd = 0;
  while (fgets(entrada, 50, arq) != NULL){
    // fgets(entrada, 50, arq);
    for(i = 0; i < strlen(entrada); i++){
      nome[i] = entrada[i];
      if(entrada[i] == espaco[0]){
        idade[0] = entrada[i+1];
        idade[1] = entrada[i+2];
        idade[2] = '\0';
        nome[i] = '\0';
        qtd++;
        break;
      }
    }
    strcpy(alunos[j].nome , nome);
    alunos[j++].idade = atoi(idade);
  }
  fclose(arq);

  Quick(alunos,0,qtd);
  qtd--;
  arq = fopen("saidada3.txt", "w");
  for(i = 0;i< (qtd /2);i++){
    fputs(alunos[i].nome, arq);
    sprintf(idade, "%d ", alunos[i].idade);
    fputs(idade, arq);
    fputs(alunos[qtd-i].nome, arq);
    sprintf(idade, "%d \n", alunos[qtd-i].idade);
    fputs(idade, arq);
  }
  fclose(arq);
  return 0;
}


void Quick(tipoAluno *alunos, int inicio, int fim){
  char auxnome[50];
  int pivo, aux, i, j, meio;

   i = inicio;
   j = fim;

   meio = (int) ((i + j) / 2);
   pivo = (alunos[meio]).idade;

   do{
      while ((alunos[i]).idade < pivo)
       i = i + 1;
      while ((alunos[j]).idade > pivo)
      j = j - 1;

      if(i <= j){
         aux = (alunos[i]).idade;
         strcpy(auxnome, (alunos[i]).nome);
         strcpy((alunos[i]).nome,(alunos[j]).nome);
         (alunos[i]).idade = (alunos[j]).idade;
         strcpy((alunos[j]).nome,auxnome);
         (alunos[j]).idade = aux;
         i = i + 1;
         j = j - 1;
      }
   }while(j > i);

   if(inicio < j)
    Quick(alunos, inicio, j);
   if(i < fim)
    Quick(alunos, i, fim);
}
