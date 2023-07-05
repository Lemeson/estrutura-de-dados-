#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include "comparaArvores.h"
#define RED 1
#define BLACK 0

int main(){
    AVLTree* treeAVL = createAVLTree();
    LLRBTree* tree = createLLRBTree();

    int opcao; //opção para o menu
    clock_t inicio, fim; //usados para medir o tempo
    double tempoExecucao; // guarda temopo de execução
    //int Forma_ordena, opcao; //
    setlocale(LC_ALL, "pt-br"); //para ler utf-8
    int opcaoArvore, opcaoOrdenado;
    info* ordenado;
    info* desordenado;
    FILE* arquivo_ordenado;
    FILE* arquivo_desordenado;
    FILE* arquivo;

    char linha[200]; //string que vai ler a linha da massa de dados

    char* delimitador = ";"; // para ser usado no strtok para tratamento dos dados
    int i = 0;

   organizeDataFile("massaDados.csv", "massaDadosOrdenados.csv");

   arquivo_desordenado = fopen("massaDados.csv", "r");
   if (arquivo_desordenado == NULL){
        printf("impossivel abrir o arquivo desordenado!\n"); //se for nulo
    }
    //lerArquivo(reg_desordenado, arquivo_desordenado);



    arquivo_ordenado = fopen("massaDadosOrdenados.csv", "r");
    if (arquivo_ordenado == NULL){
        printf("impossivel abrir o arquivo ordenado!\n"); //se for nulo
    }


    do {
            system("cls");
        printf("===== MENU =====\n");
        printf("1. Árvore AVL com dados Ordenados \n");
        printf("2. Árvore AVL com dados Desordenados \n");
        printf("3. Árvore RRLB com dados Ordenados \n");
        printf("4. Árvore RRLB com dados Desordenados \n");
        printf("0. Sair\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);


        switch (opcao) {
            case 1:
                arquivo = fopen("massaDadosOrdenados.csv", "r");
                    if (arquivo == NULL) {
                        printf("Erro ao abrir o arquivo .\n");
                        return 0;
                    }

                    fgets(linha, sizeof(linha), arquivo); // Lê a primeira linha (cabeçalho) e descarta

                    inicio = clock();
                    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                        info registro;
                        sscanf(linha, "%d;%[^;];%d;%[^;];%[^;];%f",
                               &(registro.codigo), registro.nome, &(registro.idade),
                               registro.empresa, registro.departamento, &(registro.salario));

                        insertAVL(treeAVL, registro);
                    }
                    fim = clock();
                    tempoExecucao = fim - inicio;
                    printf("%.2f ms", tempoExecucao);
                    fclose(arquivo);


                    //printTreeAVL(treeAVL); //apagar depois

                break;
            case 2:
                 ///
            arquivo = fopen("massaDados.csv", "r");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo.\n");
                return 0;
            }

            fgets(linha, sizeof(linha), arquivo); // Lê a primeira linha (cabeçalho) e descarta


            inicio = clock();
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                info registro;
                sscanf(linha, "%d;%[^;];%d;%[^;];%[^;];%f",
                       &(registro.codigo), registro.nome, &(registro.idade),
                       registro.empresa, registro.departamento, &(registro.salario));

                insert(treeAVL, registro);
            }
            fim = clock();
            tempoExecucao = fim - inicio;
            printf("%.2f ms", tempoExecucao);

            fclose(arquivo);

           // printTreeAVL(treeAVL); // apagar depois
///

                break;
            case 3:
                arquivo = fopen("massaDadosOrdenados.csv", "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo ordenado.\n");
                    return 0;
                }

                fgets(linha, sizeof(linha), arquivo); // Lê a primeira linha (cabeçalho) e descarta
                inicio = clock();
                while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                    info registro;
                    sscanf(linha, "%d;%[^;];%d;%[^;];%[^;];%f",
                           &(registro.codigo), registro.nome, &(registro.idade),
                           registro.empresa, registro.departamento, &(registro.salario));

                    insert(tree, registro);
                }
                fim = clock();
                tempoExecucao = fim - inicio;
                printf("%.2f ms", tempoExecucao);
               // printTree(tree);

                fclose(arquivo);
                break;
            case 4:
            arquivo = fopen("massaDados.csv", "r");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo .\n");
                return 0;
            }
            fgets(linha, sizeof(linha), arquivo); // Lê a primeira linha (cabeçalho) e descarta
             inicio = clock();
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                info registro;
                sscanf(linha, "%d;%[^;];%d;%[^;];%[^;];%f",
                &(registro.codigo), registro.nome, &(registro.idade),
                registro.empresa, registro.departamento, &(registro.salario));

                insert(tree, registro);
            }
            fim = clock();
            tempoExecucao = fim - inicio;
            printf("%.2f ms", tempoExecucao);
           // printTree(tree);//apagar

            fclose(arquivo);


                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Digite novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione qualquer tecla para continuar...\n");
            getchar();
            getchar();  // Aguarda a leitura de um caractere
            printf("\n");
        }
    } while (opcao != 0);



    fclose(arquivo_desordenado);
    fclose(arquivo_ordenado);
    printf("ooeee");
    return 0;
}
