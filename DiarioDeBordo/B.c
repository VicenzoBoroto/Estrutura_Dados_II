// Vicenzo Boroto Pompermayer

#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

// Estrutura de um nó da árvore B
struct BTreeNode {
    int val[MAX + 1], count;
    struct BTreeNode *link[MAX + 1];
};

struct BTreeNode *root = NULL;

// Função para criar um novo nó
struct BTreeNode *createNode(int val, struct BTreeNode *child) {
    struct BTreeNode *newNode;
    newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode->val[1] = val;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

// Função para adicionar valor a um nó
void insertNode(int val, int pos, struct BTreeNode *node, struct BTreeNode *child) {
    int j = node->count;
    while (j > pos) {
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->count++;
}

// Função para dividir um nó
void splitNode(int val, int *pval, int pos, struct BTreeNode *node, struct BTreeNode *child, struct BTreeNode **newNode) {
    int median, j;
    if (pos > MIN) {
        median = MIN + 1;
    } else {
        median = MIN;
    }
    *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    j = median + 1;
    while (j <= MAX) {
        (*newNode)->val[j - median] = node->val[j];
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN) {
        insertNode(val, pos, node, child);
    } else {
        insertNode(val, pos - median, *newNode, child);
    }
    *pval = node->val[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

// Função para definir o valor no nó
int setValue(int val, int *pval, struct BTreeNode *node, struct BTreeNode **child) {
    int pos;
    if (!node) {
        *pval = val;
        *child = NULL;
        return 1;
    }
    if (val < node->val[1]) {
        pos = 0;
    } else {
        for (pos = node->count; (val < node->val[pos] && pos > 1); pos--);
        if (val == node->val[pos]) {
            printf("Duplicatas não são permitidas\n");
            return 0;
        }
    }
    if (setValue(val, pval, node->link[pos], child)) {
        if (node->count < MAX) {
            insertNode(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

// Função para inserir um valor na árvore
void insert(int val) {
    int flag, i;
    struct BTreeNode *child;
    flag = setValue(val, &i, root, &child);
    if (flag) {
        root = createNode(i, child);
    }
}

// Função para copiar o sucessor durante a exclusão
void copySuccessor(struct BTreeNode *myNode, int pos) {
    struct BTreeNode *dummy;
    dummy = myNode->link[pos];
    while (dummy->link[0] != NULL) {
        dummy = dummy->link[0];
    }
    myNode->val[pos] = dummy->val[1];
}

// Função para remover o valor de um nó
void removeVal(struct BTreeNode *myNode, int pos) {
    int i = pos + 1;
    while (i <= myNode->count) {
        myNode->val[i - 1] = myNode->val[i];
        myNode->link[i - 1] = myNode->link[i];
        i++;
    }
    myNode->count--;
}

// Função para ajustar o nó após a remoção
void adjustNode(struct BTreeNode *myNode, int pos) {
    if (!pos) {
        if (myNode->link[1]->count > MIN) {
            // Rotacionar ou mesclar, se necessário
        } else {
            // Mesclar, se necessário
        }
    } else {
        if (myNode->count != pos) {
            if (myNode->link[pos - 1]->count > MIN) {
                // Rotacionar à direita
            } else {
                if (myNode->link[pos + 1]->count > MIN) {
                    // Rotacionar à esquerda
                } else {
                    // Mesclar os nós
                }
            }
        } else {
            if (myNode->link[pos - 1]->count > MIN) {
                // Rotacionar à direita
            } else {
                // Mesclar os nós
            }
        }
    }
}

// Função para excluir um valor de um nó
int delValFromNode(int val, struct BTreeNode *myNode) {
    int pos, flag = 0;
    if (myNode) {
        if (val < myNode->val[1]) {
            pos = 0;
            flag = 0;
        } else {
            for (pos = myNode->count; (val < myNode->val[pos] && pos > 1); pos--);
            if (val == myNode->val[pos]) {
                flag = 1;
            } else {
                flag = 0;
            }
        }
        if (flag) {
            if (myNode->link[pos - 1]) {
                copySuccessor(myNode, pos);
                flag = delValFromNode(myNode->val[pos], myNode->link[pos]);
                if (flag == 0) {
                    printf("Dado não presente na Árvore B\n");
                }
            } else {
                removeVal(myNode, pos);
            }
        } else {
            flag = delValFromNode(val, myNode->link[pos]);
        }
        if (myNode->link[pos]) {
            if (myNode->link[pos]->count < MIN) {
                adjustNode(myNode, pos);
            }
        }
    }
    return flag;
}

// Função de exclusão de um valor na árvore B
void delete(int val, struct BTreeNode *myNode) {
    struct BTreeNode *tmp;
    if (!delValFromNode(val, myNode)) {
        printf("Não encontrado\n");
        return;
    } else {
        if (myNode->count == 0) {
            tmp = myNode;
            myNode = myNode->link[0];
            free(tmp);
        }
    }
    root = myNode;
    return;
}

// Função para imprimir a árvore B em níveis
void printTree(struct BTreeNode *node, int level) {
    if (node != NULL) {
        int i;

        // Imprime os filhos da direita primeiro
        for (i = node->count; i > 0; i--) {
            if (node->link[i] != NULL) {
                printTree(node->link[i], level + 1);
            }
        }

        // Imprime o nó atual com todas as suas chaves
        for (i = 0; i < node->count; i++) {
            printf("%*s%d ", level * 5, "", node->val[i + 1]);
        }
        printf("\n");

        // Imprime os filhos da esquerda
        if (node->link[0] != NULL) {
            printTree(node->link[0], level + 1);
        }
    }
}

// Função de busca de um valor na árvore B
void search(int val, struct BTreeNode *node) {
    if (node == NULL) {
        printf("%d não encontrado\n", val);
        return;
    }
    int i = 1;
    while (i <= node->count && val > node->val[i]) {
        i++;
    }
    if (i <= node->count && val == node->val[i]) {
        printf("%d encontrado\n", val);
        return;
    }
    search(val, node->link[i - 1]);
}

// Função principal
int main() {
    // Inserções iniciais
    insert(8);
    insert(9);
    insert(10);
    insert(11);
    insert(15);
    insert(16);
    insert(17);
    insert(18);
    insert(20);
    insert(23);

    // Impressão da árvore após inserções
    printf("Árvore B após inserções:\n");
    printTree(root, 0);
    printf("\n");

    // Exclusão de valor
    delete(20, root);
    printf("Árvore B após excluir 20:\n");
    printTree(root, 0);
    printf("\n");

    // Busca de valores
    search(10, root);
    search(18, root);

    return 0;
}