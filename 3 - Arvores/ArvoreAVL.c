#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore AVL
struct No
{
    int valor;
    struct No *esquerda;
    struct No *direita;
    int altura;
};

//Função para criar No
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
    novoNo->altura = 0;
    return novoNo;
  }
};

//Funcao para calcular altura do No
int altura(struct No *no){
    //Verifica se o nó é nula, caso sim retorna 0
    if (no == NULL){
        return -1;
    } else {
        //Caso o nó não for nulo retorna o valor de altura armazenado
        return no->altura;
    };
};

//Funcao para calcular o Fator de Balanceamento
int FB(struct No *no){
    if(no == NULL){
        return 0;
    } else {
        int FB = altura(no->esquerda) - altura(no->direita);
        return FB;
    };
};

struct No *rotacaoDireita(struct No *no)
{
    struct No *novaRaiz = no->esquerda;       
    struct No *subArvore = novaRaiz->direita;

    // Realiza a rotação
    novaRaiz->direita = no;   
    no->esquerda = subArvore; 

    // Atualiza as alturas
    if(altura(no->esquerda) > altura(no->direita)){
        no->altura = 1 + altura(no->esquerda);      
    } else {
        no->altura = 1 + altura(no->direita); 
    }
    if(altura(novaRaiz->esquerda) > altura(novaRaiz->direita)){ 
        novaRaiz->altura = 1 + altura(novaRaiz->esquerda);      
    } else {
        novaRaiz->altura = 1 + altura(novaRaiz->direita); 
    }
    return novaRaiz;
};

struct No *rotacaoEsquerda(struct No *no)
{
    struct No *novaRaiz = no->direita;         
    struct No *subArvore = novaRaiz->esquerda;

    // Realiza a rotação
    novaRaiz->esquerda = no;
    no->direita = subArvore;

    // Atualiza as alturas
    if (altura(no->esquerda) > altura(no->direita)){
        no->altura = 1 + altura(no->esquerda);      
    } else {
        no->altura = 1 + altura(no->direita); 
    }
    if (altura(novaRaiz->esquerda) > altura(novaRaiz->direita)){
        novaRaiz->altura = 1 + altura(novaRaiz->esquerda);      
    } else {
        novaRaiz->altura = 1 + altura(novaRaiz->direita); 
    }
    return novaRaiz; 
}

struct No *balanceamento(struct No *raiz, int dado)
{
    // Atualiza a altura do nó atual
    if (raiz == NULL) // Se a raiz for nula, retorna a raiz
    {
        return raiz;
    }
    if (altura(raiz->esquerda) > altura(raiz->direita)) // Verifica a altura da subárvore esquerda
    {
        raiz->altura = 1 + altura(raiz->esquerda); // Atualiza a altura da raiz
    }
    else
    {
        raiz->altura = 1 + altura(raiz->direita); // Atualiza a altura da raiz
    }

    // Calcula o fator de balanceamento deste nó para verificar se ele se tornou desbalanceado
    int balanceamento = fatorBalanceamento(raiz); // Calcula o fator de balanceamento da raiz

    // Caso de desbalanceamento à esquerda-esquerda
    if (balanceamento > 1 && dado < raiz->esquerda->dado) // Se o fator de balanceamento for maior que 1 e o dado for menor que o dado da subárvore esquerda
        return rotacaoDireita(raiz);                      // Realiza rotação à direita

    // Caso de desbalanceamento à direita-direita
    if (balanceamento < -1 && dado > raiz->direita->dado) // Se o fator de balanceamento for menor que -1 e o dado for maior que o dado da subárvore direita
        return rotacaoEsquerda(raiz);                     // Realiza rotação à esquerda

    // Caso de desbalanceamento à esquerda-direita
    if (balanceamento > 1 && dado > raiz->esquerda->dado) // Se o fator de balanceamento for maior que 1 e o dado for maior que o dado da subárvore esquerda
    {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda); // Realiza rotação à esquerda na subárvore esquerda da raiz
        return rotacaoDireita(raiz);                      // Realiza rotação à direita na raiz
    }

    // Caso de desbalanceamento à direita-esquerda
    if (balanceamento < -1 && dado < raiz->direita->dado) // Se o fator de balanceamento for menor que -1 e o dado for menor que o dado da subárvore direita
    {
        raiz->direita = rotacaoDireita(raiz->direita); // Realiza rotação à direita na subárvore direita da raiz
        return rotacaoEsquerda(raiz);                  // Realiza rotação à esquerda na raiz
    }

    // Retorna a raiz inalterada
    return raiz; // Retorna a raiz após o balanceamento
}
