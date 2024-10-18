//Vicenzo Boroto Pompermayer

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura do Nó
typedef struct Node {
    int valor;
    int prioridade;
    struct Node *left;
    struct Node *right;
} Node;

// Função para criar um novo nó
Node* novoNo(int valor) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->valor = valor;
    node->prioridade = rand(); // Coloca uma prioridade aleatória
    node->left = node->right = NULL;
    return node;
}

// Função para realizar a rotação à direita
Node* rotacaoDireita(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realiza rotação
    x->right = y;
    y->left = T2;

    // Atualiza altura
    return x;
}

// Função para realizar a rotação à esquerda
Node* rotacionaEsquerda(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realiza rotação
    y->left = x;
    x->right = T2;

    // Atualiza altura
    return y;
}

// Função para inserir um nó na árvore
Node* insert(Node* raiz, int valor) {
    if (raiz == NULL) {
        return novoNo(valor);
    }

    if (valor < raiz->valor) {
        raiz->left = insert(raiz->left, valor);
        if (raiz->left->prioridade > raiz->prioridade) {
            raiz = rotacaoDireita(raiz);
        }
    } else if (valor > raiz->valor) {
        raiz->right = insert(raiz->right, valor);
        if (raiz->right->prioridade > raiz->prioridade) {
            raiz = rotacionaEsquerda(raiz);
        }
    }

    return raiz;
}

// Função para encontrar o nó com valor mínimo
Node* findMin(Node* raiz) {
    while (raiz->left != NULL) {
        raiz = raiz->left;
    }
    return raiz;
}

// Função para deletaro Nó
Node* delete(Node* raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }

    if (valor < raiz->valor) {
        raiz->left = delete(raiz->left, valor);
    } else if (valor > raiz->valor) {
        raiz->right = delete(raiz->right, valor);
    } else {
        if (raiz->left == NULL && raiz->right == NULL) {
            free(raiz);
            raiz = NULL;
        } else if (raiz->left == NULL) {
            Node* temp = raiz->right;
            free(raiz);
            return temp;
        } else if (raiz->right == NULL) {
            Node* temp = raiz->left;
            free(raiz);
            return temp;
        } else {
            Node* temp = findMin(raiz->right);
            raiz->valor = temp->valor;
            raiz->right = delete(raiz->right, temp->valor);
        }
    }

    return raiz;
}

// Função para imprimir a árvore in-order
void inorder(Node* raiz) {
    if (raiz != NULL) {
        inorder(raiz->left);
        printf("%d ", raiz->valor);
        inorder(raiz->right);
    }
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    Node* raiz = NULL;

    raiz = insert(raiz, 50);
    raiz = insert(raiz, 30);
    raiz = insert(raiz, 20);
    raiz = insert(raiz, 40);
    raiz = insert(raiz, 70);
    raiz = insert(raiz, 60);
    raiz = insert(raiz, 80);

    printf("Inorder: ");
    inorder(raiz);
}