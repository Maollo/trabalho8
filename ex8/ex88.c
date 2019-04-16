#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUANT_CLASSES 5

typedef struct estruturaArvore{
  struct estruturaClasse *classes[QUANT_CLASSES];
}tipoArvore;

typedef struct estruturaClasse{
  char* nome_classe;
  struct estruturaFamilia *familias;
} tipoClasse;

typedef struct estruturaFamilia{
  char* nome_familia;
  struct estruturaAnimal *animais;
  struct estruturaFamilia *prox;
} tipoFamilia;

typedef struct estruturaAnimal{
  char *nome_animal, *nome_familia, *nome_classe;
  struct estruturaAnimal *prox;
} tipoAnimal;

tipoClasse *alocaClasse(char* nome_classe){
  tipoClasse *novoNo;
  novoNo = (tipoClasse*) malloc (sizeof(tipoClasse));
  novoNo->nome_classe = nome_classe;
  novoNo->familias = NULL;

  return novoNo;
}

void inicializaArvoreBiologica(tipoArvore **arv){
  tipoArvore *novoNo;
  int i;
  char* classes[QUANT_CLASSES] = {"Mamiferos", "Peixe", "Ave", "Reptil", "Anfibio"};
  if(*arv == NULL){
    novoNo = (tipoArvore*) malloc (sizeof(tipoArvore));
    for(i=0;i<QUANT_CLASSES;i++)
      novoNo->classes[i] = alocaClasse(classes[i]);
    *arv = novoNo;
  }
}

tipoClasse **encontraClasse(tipoArvore *arv, char* nome_classe){
  tipoClasse *aux;
  int i;

  for(i=0;i<QUANT_CLASSES;i++)
    if (!strcmp(arv->classes[i]->nome_classe, nome_classe))
      return &(arv->classes[i]);
}

tipoFamilia *encontraFamiliaOuNULL(tipoClasse **classe, char* nome_familia){
  tipoFamilia *familias;
  familias = (*classe)->familias;
  while(familias != NULL){
    if(!strcmp(nome_familia, familias->nome_familia))
      return familias;
    familias = familias->prox;
  }
  return NULL;
}

void insereFamilia(tipoArvore **arv, char* familia, char* classe){
  tipoClasse **classeAdequada;
  tipoFamilia *novoNo, **familias, *aux;

  novoNo = (tipoFamilia*) malloc (sizeof(tipoFamilia));
  novoNo->nome_familia =  familia;
  novoNo->animais = NULL;
  novoNo->prox = NULL;

  classeAdequada = encontraClasse(*arv, classe);
  familias = &((*classeAdequada)->familias);
  if(*familias == NULL)
    *familias = novoNo;
  else{
    aux = *familias;
    while(aux->prox != NULL)
      aux = aux->prox;
    aux->prox = novoNo;
  }
}

void insereAnimal(tipoArvore **arv, char* classe, char* familia, char* nome){
  tipoClasse **classeAdequada;
  tipoFamilia *enderecoFamilia, *auxFamilia;
  tipoAnimal *auxAnimal, *novoNo, **animais;


  classeAdequada = encontraClasse(*arv, classe);
  enderecoFamilia = encontraFamiliaOuNULL(classeAdequada, familia);
  if(enderecoFamilia != NULL){
    novoNo = (tipoAnimal*) malloc (sizeof(tipoAnimal));
    novoNo->nome_animal = nome;
    novoNo->nome_familia = familia;
    novoNo->nome_classe = classe;
    novoNo->prox = NULL;

    animais = &(enderecoFamilia->animais);
    if(*animais == NULL)
      *animais = novoNo;
    else{
      auxAnimal = *animais;
      while(auxAnimal->prox != NULL)
        auxAnimal = auxAnimal->prox;
      auxAnimal->prox = novoNo;
    }
  }else{
    insereFamilia(arv, familia, classe);
    insereAnimal(arv, classe, familia, nome);
  }
}

void sobeArquivoPraArvore(char* nome_arq, tipoArvore **arv){
  FILE *arq;
  char nome[30], classe[30], familia[30];
  int i, j, k;
  arq = fopen(nome_arq, "r");
  char linha[50];

  while(fgets(linha, 50, arq) != NULL){
    // strcpy(copy_linha, linha);
    // strcpy(classe,strtok(copy_linha, ","));
    // strcpy(familia,strtok(NULL, ","));
    // strcpy(nome,strtok(NULL, ","));


    // for(i=0;nome[i] != '\n';i++)
    //   continue;
    // nome[i] = '\0';

    i = 0;
    while(linha[i] != ','){
      classe[i++] = linha[i];
    }
    classe[i+1] = '\0';
    i++;
    j = 0;
    while (linha[i] != ',') {
      familia[j++] = linha[i++];
    }
    familia[j+1] = '\0';
    i++;
    k = 0;
    while (linha[i] != '.') {
      nome[k] = linha[i];
    }
    nome[k+1] = '\0';
    insereAnimal(arv, classe, familia, nome);
  }

  fclose(arq);
}

tipoAnimal *buscaAnimal(tipoArvore *arv, char* nome_animal){
  int i;
  char resultado_busca[100];
  tipoFamilia *familiaAtual;
  tipoAnimal *animalAtual;

  for(i=0;i<QUANT_CLASSES;i++){
    familiaAtual = arv->classes[i]->familias;
    while(familiaAtual != NULL){
      animalAtual = familiaAtual->animais;
      while(animalAtual != NULL){
        if (!strcmp(animalAtual->nome_animal, nome_animal))
          return animalAtual;
        animalAtual = animalAtual->prox;
      }
      familiaAtual = familiaAtual->prox;
    }
  }
  return NULL;
}

void imprimeAnimal(tipoAnimal *animal){
  if(animal == NULL)
    printf("O Animal não foi encontrado!");
  else{
    printf("Classe: %s\n", animal->nome_classe);
    printf("Familia: %s\n", animal->nome_familia);
    printf("Raca: %s\n", animal->nome_animal);
  }
}

int main(int argc, char const *argv[]) {
  tipoArvore *arv;
  arv = NULL;
  inicializaArvoreBiologica(&arv);
  sobeArquivoPraArvore("arq_entrada.txt", &arv);
  insereAnimal(&arv, "Reptil", "Cobra", "Jararaca");
  imprimeAnimal(buscaAnimal(arv, "Jararaca"));
  // Inserção de arquivo não tá funcionando direito :()

  return 0;
}
