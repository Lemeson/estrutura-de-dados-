#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "arquivo.h"

int main() {
    int algoritmo_escolhido, quantidade_elementos, opcao, i, j;
    int *vetor;
    double tempos_execucao[10];
    double tempo_total, tempo_medio;
    double tempo_crescente, tempo_decrescente;

    do {
        printf("\nEscolha o algoritmo de ordenação:\n");
        printf("1. BubbleSort\n");
        printf("2. SelectionSort\n");
        printf("3. InsertionSort\n");
        printf("4. MergeSort\n");
        printf("5. QuickSort\n");
        printf("6. ShellSort\n");
        printf("7. HeapSort\n");
        printf("8. TimSort\n");
        printf("9. RadixSort\n");

        // Adicione as opções para os outros algoritmos
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &algoritmo_escolhido);

        if (algoritmo_escolhido == 0) {
            break;
        }

        printf("\nEscolha a quantidade de elementos a serem ordenados:\n");
        printf("1. 1.000\n");
        printf("2. 5.000\n");
        printf("3. 10.000\n");
        printf("4. 20.000\n");
        printf("5. 50.000\n");
        printf("6. 100.000\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                quantidade_elementos = 1000;
                break;
            case 2:
                quantidade_elementos = 5000;
                break;
            case 3:
                quantidade_elementos = 10000;
                break;
            case 4:
                quantidade_elementos = 20000;
                break;
            case 5:
                quantidade_elementos = 50000;
                break;
            case 6:
                quantidade_elementos = 100000;
                break;
            default:
                printf("Opção inválida!\n");
                continue;
        }

        vetor = malloc(quantidade_elementos * sizeof(int));

        tempo_total = 0.0;
        for (j = 0; j < 10; j++) {
            rand_seed(get_current_time_seed());

           // for (i = 0; i < quantidade_elementos; i++) {
            //    vetor[i] = rand() % (quantidade_elementos * 10); //conferir
           // }

            fisherYates(vetor, quantidade_elementos);


            tempos_execucao[j] = execute_algorithm_and_measure_time(algoritmo_escolhido, quantidade_elementos, vetor); //retorna tempo de execucao
            tempo_total += tempos_execucao[j];
        }

        tempo_medio = tempo_total / 10;

        // Executar com vetor ordenado de forma crescente
        tempo_crescente = execute_algorithm_and_measure_time(algoritmo_escolhido, quantidade_elementos, vetor);

        // Inverter o vetor para ordem decrescente
        for (i = 0; i < quantidade_elementos / 2; i++) {
            int temp = vetor[i];
            vetor[i] = vetor[quantidade_elementos - 1 - i];
            vetor[quantidade_elementos - 1 - i] = temp;
        }

        // Executar com vetor ordenado de forma decrescente
        tempo_decrescente = execute_algorithm_and_measure_time(algoritmo_escolhido, quantidade_elementos, vetor);


        // Exibir os resultados
        printf("\nResultados das 10 execuções:\n");
        for (j = 0; j < 10; j++) {
            printf("Execução %d: %.2f ms\n", j + 1, tempos_execucao[j]);
        }
        printf("\nTempo médio de execução: %.2f ms\n", tempo_medio);
        printf("Tempo com vetor ordenado de forma crescente: %.2f ms\n", tempo_crescente);
        printf("Tempo com vetor ordenado de forma decrescente: %.2f ms\n", tempo_decrescente);

        // Armazenar os valores de tempo medidos
        double tempos_medidos[12];
        for (i = 0; i < 10; i++) {
            tempos_medidos[i] = tempos_execucao[i];
        }
        tempos_medidos[10] = tempo_crescente;
        tempos_medidos[11] = tempo_decrescente;

        // Exibir os resultados em uma tabela ----bom/melhor ou seila -- que seja um gráfico
        printf("\nResultados das 10 execuções e comportamentos natural e pior caso:\n");
        print_table_header();
        for (j = 1; j <= 10; j++) {
            print_table_row(j, tempos_execucao[j-1], tempo_crescente, tempo_decrescente);
        }


        free(vetor);
    } while (1);

    return 0;
}
