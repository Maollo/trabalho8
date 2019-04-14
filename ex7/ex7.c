#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MENSAGENS 2

typedef struct estruturaNoArvBin{
char* mensagem;
struct estruturaNoArvBin *dir, *esq;
} tipoArvBin;

void insereNohDePercurso(tipoArvBin **arv, char* status, int perc_status, char mensagem[]){
  tipoArvBin *novoNo;
  if (*arv == NULL){
    novoNo = (tipoArvBin*) malloc (sizeof(tipoArvBin));
    novoNo->mensagem = (char*) malloc (sizeof(char)*strlen(mensagem));
    strcpy(novoNo->mensagem, mensagem);
    novoNo->dir = NULL;
    novoNo->esq = NULL;
    *arv = novoNo;
  }else{
    if(status[perc_status+1] == 'n')
      insereNohDePercurso(&(*arv)->esq, status, perc_status+1, mensagem);
    else if (status[perc_status+1] == 's')
      insereNohDePercurso(&(*arv)->dir, status, perc_status+1, mensagem);
  }
}

void inicializa_arvore_decisao(tipoArvBin **arv, char* nome_arq){
  FILE *arq;
  int i;
  char linha[40], *status, *str_mensagem, *str_linha;
  arq = fopen(nome_arq, "r");

  // Cria raiz
  insereNohDePercurso(arv, " ", 0, "");

  // Lê arquivo inserindo os valores
  while(!feof(arq)){
    fgets(linha, 40, arq);
    status = strtok(linha, "/");
    str_mensagem = strtok(NULL, "");
    if (str_mensagem != NULL){
      for(i=0;str_mensagem[i]!='\n';i++)
        continue;
      str_mensagem[i] = '\0';
      insereNohDePercurso(arv, status, 0, str_mensagem);
    }
  }
  fclose(arq);
}

tipoArvBin *proxNo(int result_comp, tipoArvBin *noAtual){
  if(!result_comp)
    return (noAtual->esq);
  return (noAtual->dir);
}

char *produzDecisao(tipoArvBin *noAtual, float nota, int freq_pct){
  noAtual = proxNo(nota >= 7.0, noAtual);
  noAtual = proxNo(nota < 5.0, noAtual);
  noAtual = proxNo(freq_pct >= 75, noAtual);
  return noAtual->mensagem;
}

void imprimePreOrdem(tipoArvBin *arv){
  if(arv != NULL){
    printf("%s ", arv->mensagem);
    imprimePreOrdem(arv->esq);
    imprimePreOrdem(arv->dir);
  }
}

int main(int argc, char const *argv[]) {
  tipoArvBin *arv;
  float nota;
  int freq;
  printf("Informe a nota do aluno seguido de sua frequencia (exemplo: 75 para 75%%)\n");
  printf("PS: Separe os valores por espaço ");
  scanf("%f %d", &nota, &freq);
  arv = NULL;
  inicializa_arvore_decisao(&arv, "arq_entrada.txt");

  printf("Status do aluno: %s\n", produzDecisao(arv, nota, freq));
  return 0;
}
