#include <stdio.h>
#include <stdlib.h>

// Defini��o da estrutura do n� da �rvore AVL
struct No
{
    int valor;
    struct No *esquerda;
    struct No *direita;
    int altura;
};

//Fun��o para criar No
struct No *criarNo(int valor){
  //Aloca espa�o de mem�ria para o novo n�
  struct No *novoNo = (struct No *)malloc(sizeof(struct No));
  //Condicional para verificar se o valor do novo n� � v�lido
  if(novoNo == NULL) {
    //Caso n�o seja v�lido retorna mensagem de erro e finaliza a fun��o
    printf("Falha ao criar n�");
    exit(-1);
  }
  //Se for v�lido, atribui o valor do novo n�
  else {
    //Por n�o ter n�s filhos, inicializa os ponteiros como NULL
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->altura = 0;
    return novoNo;
  }
};

//Funcao para calcular altura do No
int altura(struct No *no){
    //Verifica se o n� � nula, caso sim retorna 0
    if (no == NULL){
        return -1;
    } else {
        //Caso o n� n�o for nulo retorna o valor de altura armazenado
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

    // Realiza a rota��o
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

    // Realiza a rota��o
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
    // Atualiza a altura do n� atual
    if (raiz == NULL) // Se a raiz for nula, retorna a raiz
    {
        return raiz;
    }
    if (altura(raiz->esquerda) > altura(raiz->direita)) // Verifica a altura da sub�rvore esquerda
    {
        raiz->altura = 1 + altura(raiz->esquerda); // Atualiza a altura da raiz
    }
    else
    {
        raiz->altura = 1 + altura(raiz->direita); // Atualiza a altura da raiz
    }

    // Calcula o fator de balanceamento deste n� para verificar se ele se tornou desbalanceado
    int balanceamento = fatorBalanceamento(raiz); // Calcula o fator de balanceamento da raiz

    // Caso de desbalanceamento � esquerda-esquerda
    if (balanceamento > 1 && dado < raiz->esquerda->dado) // Se o fator de balanceamento for maior que 1 e o dado for menor que o dado da sub�rvore esquerda
        return rotacaoDireita(raiz);                      // Realiza rota��o � direita

    // Caso de desbalanceamento � direita-direita
    if (balanceamento < -1 && dado > raiz->direita->dado) // Se o fator de balanceamento for menor que -1 e o dado for maior que o dado da sub�rvore direita
        return rotacaoEsquerda(raiz);                     // Realiza rota��o � esquerda

    // Caso de desbalanceamento � esquerda-direita
    if (balanceamento > 1 && dado > raiz->esquerda->dado) // Se o fator de balanceamento for maior que 1 e o dado for maior que o dado da sub�rvore esquerda
    {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda); // Realiza rota��o � esquerda na sub�rvore esquerda da raiz
        return rotacaoDireita(raiz);                      // Realiza rota��o � direita na raiz
    }

    // Caso de desbalanceamento � direita-esquerda
    if (balanceamento < -1 && dado < raiz->direita->dado) // Se o fator de balanceamento for menor que -1 e o dado for menor que o dado da sub�rvore direita
    {
        raiz->direita = rotacaoDireita(raiz->direita); // Realiza rota��o � direita na sub�rvore direita da raiz
        return rotacaoEsquerda(raiz);                  // Realiza rota��o � esquerda na raiz
    }

    // Retorna a raiz inalterada
    return raiz; // Retorna a raiz ap�s o balanceamento
}
