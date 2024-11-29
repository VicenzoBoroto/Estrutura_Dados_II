// Vicenzo Boroto Pompermayer

#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } NodeColor;

typedef struct RBNode {
    int data;
    NodeColor color;
    struct RBNode *left, *right, *parent;
} RBNode;

RBNode* createNode(int data) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->data = data;
    node->color = RED; // Novos nós são sempre vermelhos inicialmente
    node->left = node->right = node->parent = NULL;
    return node;
}

void leftRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void rightRotate(RBNode **root, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}

void bstInsert(RBNode **root, RBNode *node) {
    RBNode *parent = NULL;
    RBNode *current = *root;
    
    while (current != NULL) {
        parent = current;
        if (node->data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    
    node->parent = parent;
    if (parent == NULL)
        *root = node;
    else if (node->data < parent->data)
        parent->left = node;
    else
        parent->right = node;
}

void fixInsert(RBNode **root, RBNode *node) {
    RBNode *parent = NULL;
    RBNode *grandparent = NULL;
    
    while ((node != *root) && (node->color != BLACK) && (node->parent->color == RED)) {
        parent = node->parent;
        grandparent = parent->parent;
        
        // Caso A: O pai é filho esquerdo do avô
        if (parent == grandparent->left) {
            RBNode *uncle = grandparent->right;
            
            // Caso 1: O tio é vermelho
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                // Caso 2: O node é filho direito
                if (node == parent->right) {
                    leftRotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                
                // Caso 3: O node é filho esquerdo
                rightRotate(root, grandparent);
                NodeColor tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                node = parent;
            }
        }
        // Caso B: O pai é filho direito do avô
        else {
            RBNode *uncle = grandparent->left;
            
            // Caso 1: O tio é vermelho
            if ((uncle != NULL) && (uncle->color == RED)) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                // Caso 2: O node é filho esquerdo
                if (node == parent->left) {
                    rightRotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                
                // Caso 3: O node é filho direito
                leftRotate(root, grandparent);
                NodeColor tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                node = parent;
            }
        }
    }
    (*root)->color = BLACK;
}

void insert(RBNode **root, int data) {
    RBNode *node = createNode(data);
    bstInsert(root, node);
    fixInsert(root, node);
}

void inorderTraversal(RBNode *root) {
    if (root == NULL) return;
    
    inorderTraversal(root->left);
    printf("%d (%s) ", root->data, root->color == RED ? "RED" : "BLACK");
    inorderTraversal(root->right);
}

void freeTree(RBNode *node) {
    if (node == NULL) return;
    
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    RBNode *root = NULL;
    
    // Inserção de dados na árvore
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);
    insert(&root, 25);
    insert(&root, 5);
    
    // Impressão da árvore Red-Black em ordem
    printf("In-order Traversal da Árvore Red-Black:\n");
    inorderTraversal(root);
    printf("\n");

    // Libera a memória alocada para a árvore
    freeTree(root);
    
    return 0;
}