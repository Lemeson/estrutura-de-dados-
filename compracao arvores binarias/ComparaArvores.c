#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include "comparaArvores.h"
#define RED 1
#define BLACK 0


    //ARVORE AVL
//---------------------------------------------------------------
AVLTree* createAVLTree() {
    AVLTree* treeAVL = (AVLTree*)malloc(sizeof(AVLTree));
    if (treeAVL != NULL) {
        treeAVL->rootAVL = NULL;
    }
    return treeAVL;
}

NodeAVL* createNodeAVL(info dataAVL) {
    NodeAVL* newNodeAVL = (NodeAVL*)malloc(sizeof(NodeAVL));
    if (newNodeAVL != NULL) {
        newNodeAVL->dataAVL = dataAVL;
        newNodeAVL->leftAVL = NULL;
        newNodeAVL->rightAVL = NULL;
        newNodeAVL->heightAVL = 1;
    }
    return newNodeAVL;
}

int maxAVL(int a, int b) {
    return (a > b) ? a : b;
}

int getheightAVL(NodeAVL* NodeAVL) {
    if (NodeAVL == NULL) {
        return 0;
    }
    return NodeAVL->heightAVL;
}

int getBalanceFactorAVL(NodeAVL* NodeAVL) {
    if (NodeAVL == NULL) {
        return 0;
    }
    return getheightAVL(NodeAVL->leftAVL) - getheightAVL(NodeAVL->rightAVL);
}

NodeAVL* xAVL;
NodeAVL* T2AVL;
NodeAVL* rotaterightAVL(NodeAVL* NodeAVL) {
    xAVL = NodeAVL->leftAVL;
    T2AVL = xAVL->rightAVL;

    // Realiza a rotação
    xAVL->rightAVL = NodeAVL;
    NodeAVL->leftAVL = T2AVL;

    // Atualiza as alturas
    NodeAVL->heightAVL = maxAVL(getheightAVL(NodeAVL->leftAVL), getheightAVL(NodeAVL->rightAVL)) + 1;
    xAVL->heightAVL = maxAVL(getheightAVL(xAVL->leftAVL), getheightAVL(xAVL->rightAVL)) + 1;

    return xAVL;
}

NodeAVL* yAVL;
NodeAVL* rotateleftAVL(NodeAVL* NodeAVL) {
    yAVL = NodeAVL->rightAVL;
    //NodeAVL* T2AVL = yAVL->leftAVL;

    // Realiza a rotação
    yAVL->leftAVL = NodeAVL;
    NodeAVL->rightAVL = T2AVL;

    // Atualiza as alturas
    NodeAVL->heightAVL = maxAVL(getheightAVL(NodeAVL->leftAVL), getheightAVL(NodeAVL->rightAVL)) + 1;
    yAVL->heightAVL = maxAVL(getheightAVL(yAVL->leftAVL), getheightAVL(yAVL->rightAVL)) + 1;

    return yAVL;
}

NodeAVL* insertNodeAVL(NodeAVL* NodeAVL, info dataAVL) {
    if (NodeAVL == NULL) {
        return createNodeAVL(dataAVL);
    }

    if (dataAVL.codigo < NodeAVL->dataAVL.codigo) {
        NodeAVL->leftAVL = insertNodeAVL(NodeAVL->leftAVL, dataAVL);
    } else if (dataAVL.codigo > NodeAVL->dataAVL.codigo) {
        NodeAVL->rightAVL = insertNodeAVL(NodeAVL->rightAVL, dataAVL);
    } else {
        return NodeAVL;
    }

    // Atualiza a altura do nó atual
    NodeAVL->heightAVL = maxAVL(getheightAVL(NodeAVL->leftAVL), getheightAVL(NodeAVL->rightAVL)) + 1;

    // Verifica o fator de balanceamento do nó atual
    int balanceFactor = getBalanceFactorAVL(NodeAVL);

    // Caso o nó esteja desbalanceado, realiza as rotações apropriadas
    if (balanceFactor > 1 && dataAVL.codigo < NodeAVL->leftAVL->dataAVL.codigo) {
        return rotaterightAVL(NodeAVL);
    }
    if (balanceFactor < -1 && dataAVL.codigo > NodeAVL->rightAVL->dataAVL.codigo) {
        return rotateleftAVL(NodeAVL);
    }
    if (balanceFactor > 1 && dataAVL.codigo > NodeAVL->leftAVL->dataAVL.codigo) {
        NodeAVL->leftAVL = rotateleftAVL(NodeAVL->leftAVL);
        return rotaterightAVL(NodeAVL);
    }
    if (balanceFactor < -1 && dataAVL.codigo < NodeAVL->rightAVL->dataAVL.codigo) {
        NodeAVL->rightAVL = rotaterightAVL(NodeAVL->rightAVL);
        return rotateleftAVL(NodeAVL);
    }

    return NodeAVL;
}

void insertAVL(AVLTree* treeAVL, info dataAVL) {
    if (treeAVL == NULL) {
        return;
    }

    treeAVL->rootAVL = insertNodeAVL(treeAVL->rootAVL, dataAVL);
}

NodeAVL* searchNodeAVL(NodeAVL* NodeAVL, int key) {
    if (NodeAVL == NULL || NodeAVL->dataAVL.codigo == key) {
        return NodeAVL;
    }

    if (key < NodeAVL->dataAVL.codigo) {
        return searchNodeAVL(NodeAVL->leftAVL, key);
    }

    return searchNodeAVL(NodeAVL->rightAVL, key);
}

info* searchAVL(AVLTree* treeAVL, int key) {
    if (treeAVL == NULL) {
        return NULL;
    }

    NodeAVL* result = searchNodeAVL(treeAVL->rootAVL, key);
    if (result == NULL) {
        return NULL;
    }

    return &(result->dataAVL);
}

void printInOrderAVL(NodeAVL* NodeAVL) {
    if (NodeAVL != NULL) {
        printInOrderAVL(NodeAVL->leftAVL);
        printf("Código: %d, Nome: %s, Idade: %d, Empresa: %s, Departamento: %s, Salário: %.2f\n",
               NodeAVL->dataAVL.codigo, NodeAVL->dataAVL.nome, NodeAVL->dataAVL.idade,
               NodeAVL->dataAVL.empresa, NodeAVL->dataAVL.departamento, NodeAVL->dataAVL.salario);
        printInOrderAVL(NodeAVL->rightAVL);
    }
}

void printTreeAVL(AVLTree* treeAVL) {
    if (treeAVL == NULL || treeAVL->rootAVL == NULL) {
        printf("A árvore AVL está vazia.\n");
        return;
    }

    printf("Conteúdo da árvore AVL:\n");
    printInOrderAVL(treeAVL->rootAVL);
}
        //ARVORE LLBR
// ----------------------------------------------------------------

LLRBTree* createLLRBTree() {
    LLRBTree* tree = (LLRBTree*)malloc(sizeof(LLRBTree));
    if (tree != NULL) {
        tree->root = NULL;
    }
    return tree;
}

Node* createNode(info data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->color = RED;
    }
    return newNode;
}

Node* rotateLeft(Node* node) {
    Node* x = node->right;
    node->right = x->left;
    x->left = node;
    x->color = node->color;
    node->color = RED;
    return x;
}

Node* rotateRight(Node* node) {
    Node* x = node->left;
    node->left = x->right;
    x->right = node;
    x->color = node->color;
    node->color = RED;
    return x;
}

void flipColors(Node* node) {
    node->color = RED;
    node->left->color = BLACK;
    node->right->color = BLACK;
}

Node* insertNode(Node* node, info data) {
    if (node == NULL) {
        return createNode(data);
    }

    if (strcmp(data.nome, node->data.nome) < 0) {
        node->left = insertNode(node->left, data);
    } else if (strcmp(data.nome, node->data.nome) > 0) {
        node->right = insertNode(node->right, data);
    } else {
        return node;
    }

    if (node->right != NULL && node->right->color == RED && (node->left == NULL || node->left->color == BLACK)) {
        node = rotateLeft(node);
    }

    if (node->left != NULL && node->left->color == RED && node->left->left != NULL && node->left->left->color == RED) {
        node = rotateRight(node);
    }

    if (node->left != NULL && node->left->color == RED && node->right != NULL && node->right->color == RED) {
        flipColors(node);
    }

    return node;
}

void insert(LLRBTree* tree, info data) {
    if (tree != NULL) {
        tree->root = insertNode(tree->root, data);
        tree->root->color = BLACK;
    }
}

Node* searchNode(Node* node, int key) {
    if (node == NULL || node->data.codigo == key) {
        return node;
    }

    if (key < node->data.codigo) {
        return searchNode(node->left, key);
    } else {
        return searchNode(node->right, key);
    }
}

info* search(LLRBTree* tree, int key) {
    if (tree != NULL) {
        Node* result = searchNode(tree->root, key);
        if (result != NULL) {
            return &(result->data);
        }
    }
    return NULL;
}

void printInOrder(Node* node) {
    if (node != NULL) {
        printInOrder(node->left);
        printf("Código: %d\n", node->data.codigo);
        printf("Nome: %s\n", node->data.nome);
        printf("Idade: %d\n", node->data.idade);
        printf("Empresa: %s\n", node->data.empresa);
        printf("Departamento: %s\n", node->data.departamento);
        printf("Salário: %.2f\n", node->data.salario);
        printf("\n");
        printInOrder(node->right);
    }
}

void printTree(LLRBTree* tree) {
    if (tree != NULL && tree->root != NULL) {
        printInOrder(tree->root);
    }
}

            //HEAP SORT
//---------------------------------------------------------------------------

void heapify(info arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l].codigo > arr[largest].codigo)
        largest = l;

    if (r < n && arr[r].codigo > arr[largest].codigo)
        largest = r;

    if (largest != i) {
        info temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(info arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        info temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

void organizeDataFile(const char* inputFile, const char* outputFile) {
    FILE* fileIn = fopen(inputFile, "r");
    FILE* fileOut = fopen(outputFile, "w");

    if (fileIn == NULL || fileOut == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    char line[400];
    fgets(line, sizeof(line), fileIn); // Lê a primeira linha (cabeçalho) e descarta

    info* data = malloc(15000 * sizeof(info));
    int i = 0;

    while (fgets(line, sizeof(line), fileIn) != NULL && i < 15000) {
        sscanf(line, "%d;%[^;];%d;%[^;];%[^;];%f",
               &(data[i].codigo), data[i].nome, &(data[i].idade),
               data[i].empresa, data[i].departamento, &(data[i].salario));

        i++;
    }

    fclose(fileIn);

    heapSort(data, i);

    for (int j = 0; j < i; j++) {

        char salarioStr[15]; // Aumentar o tamanho do buffer para acomodar o valor do salário
        snprintf(salarioStr, sizeof(salarioStr), "%.2f", data[j].salario);

        fprintf(fileOut, "%d;%s;%d;%s;%s;%s\n",
                data[j].codigo, data[j].nome, data[j].idade,
                data[j].empresa, data[j].departamento, salarioStr);
    }

    fclose(fileOut);
    free(data);

    printf("Dados organizados e gravados no arquivo %s.\n", outputFile);
}

void lerArquivo(info* reg, FILE* arquivo) {
    char li[400];
    //char delimitador[] = ";";

    int i = 0;
    while (fgets(li, 400, arquivo) != NULL) {
        reg[i].codigo = atoi(strtok(li, ";"));
        strcpy(reg[i].nome, strtok(NULL, ";"));
        reg[i].idade = atoi(strtok(NULL, ";"));
        strcpy(reg[i].empresa, strtok(NULL, ";"));
        strcpy(reg[i].departamento, strtok(NULL, ";"));
        reg[i].salario = atof(strtok(NULL, "\n"));
        i++;
    }
}


