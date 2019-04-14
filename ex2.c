#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_STRING 100

typedef struct estruturaNo{
  char caractere_especial;
  struct estruturaNo *prox;
} tipoPilha;

void empilha(tipoPilha **pilha, char caractere){
  tipoPilha *novoNo, *aux;

  novoNo = (tipoPilha*) malloc (sizeof(tipoPilha));
  novoNo->prox = NULL;
  novoNo->caractere_especial = caractere;

  if (*pilha == NULL)
    *pilha = novoNo;
  else{
    aux = *pilha;
    *pilha = novoNo;
    novoNo->prox = aux;
  }
}

char desempilha(tipoPilha **pilha){
  tipoPilha *NoDesempilhado;
  char valorDesempilhado;

  if(*pilha != NULL){
    NoDesempilhado = *pilha;
    valorDesempilhado = NoDesempilhado->caractere_especial;
    *pilha = NoDesempilhado->prox;
    free(NoDesempilhado);
    return valorDesempilhado;
  }
}

char *verificaBalancoCaractere(char* string, char caractere_aberto, char caractere_fechado){
  int i, correspondencias_caractere;
  tipoPilha *pilhaBalanceadora;

  pilhaBalanceadora = NULL;
  correspondencias_caractere = 0;

  for(i=0; i<strlen(string);i++){
    if(string[i] == caractere_aberto){
      empilha(&pilhaBalanceadora, caractere_aberto);
      correspondencias_caractere++;
    }else if(string[i] == caractere_fechado){
      desempilha(&pilhaBalanceadora);
      correspondencias_caractere++;
    }
  }

  if(!correspondencias_caractere) // Se não tiver acontecido correspondência, char não existe
    return "(ND)";

  if (pilhaBalanceadora == NULL)
    return "OK";
  return "ERRADO";
}


int main(int argc, char const *argv[]) {
  tipoPilha *pilha;
  char string_entrada[TAM_MAX_STRING], *parenteses, *chaves, *colchetes;

  pilha = NULL;
  fgets(string_entrada, TAM_MAX_STRING, stdin);
  // string_entrada = "O cachorro (preto) muito bonito {e grande} saiu correndo [feito louco] pela rua!";

  parenteses = verificaBalancoCaractere(string_entrada, '(', ')');
  chaves = verificaBalancoCaractere(string_entrada, '{', '}');
  colchetes = verificaBalancoCaractere(string_entrada, '[', ']');

  printf("Balanceamento de Parênteses=%s, Chaves=%s, Colchetes=%s.", parenteses,
          chaves, colchetes);
  return 0;
}
