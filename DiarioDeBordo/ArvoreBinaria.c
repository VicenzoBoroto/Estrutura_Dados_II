//Vicenzo Boroto Pompermayer
// Crie em C a estrutura de uma árvore binária cuja informação seja um inteiro.
// Escreva funções que recebam um ponteiro para a raiz da árvore e façam:
// • Inserção de um elemento na árvore;
// • Pesquisa de um elemento na árvore;
// • Exclusão de um elemento na árvore.

#include <stdio.h>
#include <stdlib.h>

struct No {
  int valor;
  struct No *esquerda;
  struct No *direita;
};

void imprimeNo(int c, int b){
  int i;
  for (i = 0; i < b; i++)
      printf("   ");
  printf("%i\n", c);
};

void mostraArvore(struct No *a, int b){
  if (a == NULL){
    return;
  }
  mostraArvore(a->direita, b + 1);
  imprimeNo(a->valor, b);
  mostraArvore(a->esquerda, b + 1);
};

struct No *criarNo(int valor){
  //Aloca espaço de memória para o novo nó
  struct No *novoNo = (struct No *)malloc(sizeof(struct No));
  //Condicional para verificar se o valor do novo nó é válido
  if(novoNo == NULL) {
    //Caso não seja válido retorna mensagem de erro e finaliza a função
    printf("Falha ao criar nó");
    exit(-1);
  }
  //Se for válido, atribui o valor do novo nó
  else {
    //Por não ter nós filhos, inicializa os ponteiros como NULL
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
  }
};

struct No *inserir(struct No *raiz, int valor){
  if(raiz == NULL){
    //Se a raiz for nula, cria um novo nó com o valor passado
    return criarNo(valor);
  }
  else{
    //Se não for nula, verifica se o valor é menor ou maior que a raiz
    if(valor < raiz->valor){
      //Se for menor, insere na subárvore esquerda
      raiz->esquerda = inserir(raiz->esquerda, valor);
    }if(valor > raiz->valor){
      //Se for maior, insere na subárvore direita
      raiz->direita = inserir(raiz->direita, valor);
    }
  }
  return raiz;
};

struct No *excluir(struct No *raiz, int valor){
  if(raiz == NULL){
    //Se a raiz for nula, retorna nulo
    return NULL;
  }else{
    //Se não for nula, verifica se o valor é menor ou maior que a raiz
    if(valor < raiz->valor){
      //Se for menor, exclui na subárvore esquerda
      raiz->esquerda = excluir(raiz->esquerda, valor);
    }
    if(valor > raiz->valor){
      //Se for maior, exclui na subárvore direita
      raiz->direita = excluir(raiz->direita, valor);
    }
    else {
      if(raiz->esquerda == NULL){
        struct No *temp = raiz->direita;
        free(raiz);
        return temp;
      }
      if(raiz->direita == NULL){
        struct No *temp = raiz->esquerda;
        free(raiz);
        return temp;
      }
    }
  }
  return raiz;
};

struct No *pesquisaNo(struct No *raiz, int valor){
  if(raiz == NULL){
    //Se a raiz for nula, retorna nulo
    return NULL;
  }else{
    //Se não for nula, verifica se o valor é menor ou maior que a raiz
    if(valor < raiz->valor){
      //Se for menor, pesquisa na subárvore esquerda
      return pesquisaNo(raiz->esquerda, valor);
    }
    if(valor > raiz->valor){
      //Se for maior, pesquisa na subárvore direita
      return pesquisaNo(raiz->direita, valor);
    }
    if(valor == raiz->valor){
      imprimeNo(raiz->valor, 1);
      return raiz;
    }
    else{
      printf("Nó não encontrado.");
      exit(-1);
    };
  };
};

int main(void){
  struct No *raiz = NULL;
  raiz = inserir(raiz, 1);
  raiz = inserir(raiz, 2);
  raiz = inserir(raiz, 3);

  mostraArvore(raiz, 1);

  raiz = excluir(raiz, 2);

  mostraArvore(raiz, 1);

  raiz = pesquisaNo(raiz, 1);
}
