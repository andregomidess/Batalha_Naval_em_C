#include <stdio.h>
#include <stdlib.h>
#include <time.h> //clock(), CLOCKS_PER_SEC e clock_t
#define M 999983  

//PROCURE A PALAVRA "TODO" (de TO DO) PARA VER O QUE PRECISA MUDAR
//NAO ALTERE OS PONTOS SORTEADOS PARA OS BARCOS E TIROS
//Procure mexer o minimo possivel na main.
//basicamente voce precisa implementar as funcoes
//"adiciona_ponto" e "busca_ponto"
typedef struct cel{
  int x;
  int y;
  struct cel * prox;
}celula;

int hash(int x, int y){
  if (x==0 && y==0) return 0;
  if (x>y) return ((y%x)+(y%x)%220057)%M;
  else return ((x%y))%M;
  
}

int busca_ponto(celula ** p, int x, int y){
  int ind = hash(x, y);
  celula *tb = p[ind];
  while(tb != NULL && (tb->x != x || tb->y != y)){
    tb = tb->prox;
  }
  if (tb == NULL) return 0;
  else return 1;
}

celula** adiciona_ponto(celula **tabela, int x, int y){
  int h = hash(x, y);
  celula *p = tabela[h];
  while(p != NULL && (p->x != x || p->y != y)){
    p = p->prox;
  }
  if(p == NULL){
    celula * novo = (celula*) malloc(sizeof(celula));
    novo->x = x;
    novo->y = y;
    novo->prox = tabela[h];
    tabela[h] = novo;
  }
  return tabela;
}

void libera_oceano(celula ** oceano){
  for (int i=0; i < M; i++){
    celula* p = oceano[i];
    while(p != NULL){
      celula* aux = p;
      p = p->prox;
      free(aux);
    }
    free(p);
  }

}

int main(int argc, char * argv[]){
  //clock_t t;
 // t = clock();
  int dimensao;
  int num_pontos;
  int num_tiros;
  
  //TODO: GUARDAR OS OCEANOS DE A E B, MUDE PARA A ESTRUTURA
  //DE DADOS QUE VOCE QUISER
  celula **pontosJA = NULL;
  celula **pontosJB = NULL;
  
  
  scanf("%d %d %d", &dimensao, &num_pontos, &num_tiros);
  printf("Campo %d x %d\nCada jogador coloca %d barcos\n\n", dimensao, dimensao, num_pontos);
  
  pontosJA = (celula**) calloc(M, sizeof(celula*));
  pontosJB = (celula**) calloc(M, sizeof(celula*));
  //Definindo uma semente para gerar os mesmos pontos
  srand(dimensao);

  //Jogador A gera pontos para colocar os barcos
  printf("Jogador A coloca barcos:\n");
  for(int i = 0; i < num_pontos; i++){
    int x, y;
    //sorteia um ponto que ja nao tenha um barco
    do{
      x = rand() % dimensao;
      y = rand() % dimensao;
    }while(busca_ponto(pontosJA, x, y) != 0); //TODO: Procura no oceano A se x, y ja tem barco
  
    if(i<5) printf("(%d, %d)\n", x, y);
    
    pontosJA = adiciona_ponto(pontosJA, x, y); //TODO: Adiciona x, y no oceano A
  }
  
  
  //Jogador 2 gera pontos, com a estrategia (duvidosa) de colocar os pontos 
  //em mais ou menos em ordem crescente.
  printf("...\n\nJogador B coloca barcos:\n");
  for(int i = 0; i < num_pontos; i++){
    int x, y;
    //sorteia um ponto que ja nao tenha um barco
    do{
      x = i % dimensao;
      y = rand() % dimensao;
    }while(busca_ponto(pontosJB, x, y) != 0); //TODO: Procura no oceano B se x, y ja tem barco
      
    if(i<5) printf("(%d, %d)\n", x, y);
    
    pontosJB = adiciona_ponto(pontosJB, x, y); //TODO: Adiciona x, y no oceano B
  }
  
  printf("...\n\nCada jogador vai dar %d tiros\n", num_tiros);
  
  
  //Jogador 1 ataca pontos (aleatorios)
  int acertosJA = 0;
  printf("\nJogador A atira:\n");
  for(int i = 0; i < num_tiros; i++){
    int x = rand() % dimensao;
    int y = rand() % dimensao;
    if(i<5) printf("(%d, %d)\n", x, y);
    
    //Jogador A ataca os pontos de B
    if(busca_ponto(pontosJB, x, y) == 1) acertosJA++; //TODO: Procura no oceano B se x, y tem barco
  }
  
  //Jogador B ataca pontos (aleatorios)
  int acertosJB = 0;
  printf("...\n\nJogador B atira:\n");
  for(int i = 0; i < num_tiros; i++){
    int x = rand() % dimensao;
    int y = rand() % dimensao;
    if(i<5) printf("(%d, %d)\n", x, y);

    //Jogador B ataca os pontos de A
    if(busca_ponto(pontosJA, x, y) == 1) acertosJB++;  //TODO: Procura no oceano A se x, y ja tem barco
  }
  
  printf("...\n\nResultado: Jogador A acertou %d e Jogador B %d\n", acertosJA, acertosJB);
  
  libera_oceano(pontosJA); libera_oceano(pontosJB); //TODO: Liberar memorias
  //t = clock() - t;
  //printf("Tempo de execucao: %lf", ((double)t)/((CLOCKS_PER_SEC)));
  return 0;
}
