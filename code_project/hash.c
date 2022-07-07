#include<stdio.h>
#include<stdlib.h>

#define M 466547

typedef struct cel{
  int x;
  int y;
  struct cel * prox;
}celula;

int hash(int x, int y){
  return (((x+y)*(x+y+1))/2) + x;
}

void insere_na_tabela(celula **tabela, int x, int y){
  int h = hash(x, y);
  celula *p = tabela[h];
  while(p != NULL && (p->x != x || p->y != y)){
    p = p->prox;
  }
  if(p == NULL){
    //NÃ£o estÃ¡ na tabela, vamos colocar.
    celula * novo = (celula*) malloc(sizeof(celula));
    novo->x = x;
    novo->y = y;
    novo->prox = tabela[h];
    tabela[h] = novo;
  }
}

int conta_ponto(celula * p){
  if(p == NULL) return 0;
  return 1 + conta_ponto(p->prox);
}


int main(int argc, char * argv[]){
  celula **tabela = (celula**) malloc(M * sizeof(celula*));
  for(int i = 0; i < M; i++) tabela[i] = NULL;
  
  int quantidade_pontos; 
  scanf("%d",&quantidade_pontos);
  
  for(int i = 0; i < quantidade_pontos; i++){
    int x = rand() % 10000;
    int y = rand() % 10000;
    insere_na_tabela(tabela, x, y);
  }
  
  for(int h = 0; h < M; h++){
    printf("tb[%d] tem %d pontos\n", h, conta_ponto(tabela[h]));
  }
  
  return 0;
}