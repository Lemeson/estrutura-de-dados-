#ifndef AVL_H
#define AVL_H


typedef struct {
        int codigo;
        char nome[30];
        int idade;
        char empresa[14];
        char departamento[20];
        float salario;
    }info;
void lerArquivo(info* reg, FILE* arquivo);
void heapSort(info arr[], int n);
void organizeDataFile(const char* inputFile, const char* outputFile);
// variavel 'novo' substituir por info *reg
//
//          Arvore AVL
//-----------------------------------------------------------------

typedef struct NodeAVL {
    info dataAVL;
    struct NodeAVL* leftAVL;
    struct NodeAVL* rightAVL;
    int heightAVL;
} NodeAVL;

typedef struct {
    NodeAVL* rootAVL;
} AVLTree;

AVLTree* createAVLTree();
NodeAVL* createNodeAVL(info dataAVL);
int maxAVL(int a, int b);
int getheightAVL(NodeAVL* NodeAVL);
int getBalanceFactorAVL(NodeAVL* NodeAVL);
NodeAVL* rotaterightAVL(NodeAVL* NodeAVL);
NodeAVL* rotateleftAVL(NodeAVL* NodeAVL);
NodeAVL* insertNodeAVL(NodeAVL* NodeAVL, info dataAVL);
void insertAVL(AVLTree* treeAVL, info dataAVL);
NodeAVL* searchNodeAVL(NodeAVL* NodeAVL, int key);
info* searchAVL(AVLTree* treeAVL, int key);
void printInOrderAVL(NodeAVL* NodeAVL);
void printTreeAVL(AVLTree* treeAVL);
        //Arvore LLRB
// -----------------------------------------------

typedef enum { RED, BLACK } Color;

typedef struct Node {
    info data;
    struct Node* left;
    struct Node* right;
    Color color;
} Node;

typedef struct {
    Node* root;
} LLRBTree;

LLRBTree* createLLRBTree();
Node* createNode(info data);
Node* rotateLeft(Node* node);
Node* rotateRight(Node* node);
void flipColors(Node* node);
Node* insertNode(Node* node, info data);
void insert(LLRBTree* tree, info data);
Node* searchNode(Node* node, int key);
info* search(LLRBTree* tree, int key);
void printInOrder(Node* node);
void printTree(LLRBTree* tree);


        //HEAP SORT
//--------------------------------------
//void heapSort(info *reg, int n);

void heapify(info arr[], int n, int i);
void heapSort(info arr[], int n);
void organizeDataFile(const char* inputFile, const char* outputFile);
void lerArquivo(info* reg, FILE* arquivo);




#endif
