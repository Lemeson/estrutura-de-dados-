#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "arquivo.h"

// algoritimos de ordenação
//são 9 algoritimos de ordenação

void insertionSort(int arr[], int tamanho) {
  int i, key, j;

  for (i = 1; i < tamanho; i++) {
    key = arr[i];
    j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

void bubbleSort(int arr[], int tamanho) {


  int i, j, temp;
  for (i = 0; i < tamanho - 1; i++) {
    for (j = 0; j < tamanho - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        // troca os elementos
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void selectionSort(int arr[], int tamanho) {
    int i, j, min_idx;

    for (i = 0; i < tamanho - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < tamanho; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void shellSort(int arr[], int tamanho) {
    int i, j, gap, temp;
    for (gap = tamanho / 2; gap > 0; gap /= 2) {
        for (i = gap; i < tamanho; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

void merge(int arr[], int left, int middle, int right) {
  int i, j, k;
  int n1 = middle - left + 1;
  int n2 = right - middle;

  int L[n1], R[n2];

  for (i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[middle + 1 + j];

  i = 0;
  j = 0;
  k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int left, int right) {
  if (left < right) {
    int middle = left + (right - left) / 2;

    mergeSort(arr, left, middle);
    mergeSort(arr, middle + 1, right);

    merge(arr, left, middle, right);
  }
}

void troca(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particao(int arr[], int inicio, int fim) {
    int pivo = arr[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        if (arr[j] < pivo) {
            i++;
            troca(&arr[i], &arr[j]);
        }
    }
    troca(&arr[i + 1], &arr[fim]);
    return (i + 1);
}

void quickSort(int arr[], int inicio, int fim) {
    int* pilha = (int*)malloc((fim - inicio + 1) * sizeof(int));

    int topo = -1;

    pilha[++topo] = inicio;
    pilha[++topo] = fim;

    while (topo >= 0) {
        fim = pilha[topo--];
        inicio = pilha[topo--];

        int p = particao(arr, inicio, fim);

        if (p - 1 > inicio) {
            pilha[++topo] = inicio;
            pilha[++topo] = p - 1;
        }

        if (p + 1 < fim) {
            pilha[++topo] = p + 1;
            pilha[++topo] = fim;
        }
    }

    free(pilha);
}


void heapify(int arr[], int tamanho, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamanho && arr[esquerda] > arr[maior]) {
        maior = esquerda;
    }

    if (direita < tamanho && arr[direita] > arr[maior]) {
        maior = direita;
    }

    if (maior != i) {
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;

        heapify(arr, tamanho, maior);
    }
}

void heapSort(int arr[], int tamanho) {
    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        heapify(arr, tamanho, i);
    }

    for (int i = tamanho - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int getDigit(int num, int pos) {
    return (num / pos) % 10;
}

// Ordena o vetor usando o algoritmo RadixSort
void radixSort(int *arr, int tamanho) {
    int maior = arr[0];
    for (int i = 1; i < tamanho; i++) {
        if (arr[i] > maior) {
            maior = arr[i];
        }
    }

    int *buffer = (int*) malloc((tamanho + 10) * sizeof(int));

    for (int pos = 1; maior / pos > 0; pos *= 10) {
        int *contagem = buffer + tamanho;
        memset(contagem, 0, 10 * sizeof(int));

        for (int i = 0; i < tamanho; i++) {
            int digito = (arr[i] / pos) % 10;
            contagem[digito]++;
        }

        for (int i = 1; i < 10; i++) {
            contagem[i] += contagem[i - 1];
        }

        for (int i = tamanho - 1; i >= 0; i--) {
            int digito = (arr[i] / pos) % 10;
            buffer[contagem[digito] - 1] = arr[i];
            contagem[digito]--;
        }

        for (int i = 0; i < tamanho; i++) {
            arr[i] = buffer[i];
        }
    }

    free(buffer);
}





// Função que mescla dois subarrays ordenados
void merge_tim(int arr[], int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;

    // Alocação dinâmica de memória
    int* left = (int*)malloc(len1 * sizeof(int));
    int* right = (int*)malloc(len2 * sizeof(int));

    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];

    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < len1)
        arr[k++] = left[i++];

    while (j < len2)
        arr[k++] = right[j++];

    // Liberação da memória alocada
    free(left);
    free(right);
}

// Função que realiza o insertion sort
void insertion_timSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Função principal

// Função principal
void timSort(int arr[], int n) {
    const int RUN = 32;
    for (int i = 0; i < n; i += RUN)
        insertion_timSort(arr, i, fmin((i + RUN - 1), (n - 1)));

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = fmin((left + 2 * size - 1), (n - 1));
            merge_tim(arr, left, mid, right);
        }
    }
}

//rand_seed
void rand_seed(unsigned int seed) {
    srand(seed);
}

unsigned int get_current_time_seed() {
    return (unsigned int)time(NULL);
}



//print_time
void print_time(float tempo_medio, float tempo_crescente, float tempo_decrescente) {
    printf("\nTempo médio de execução: %.2f ms\n", tempo_medio);
    printf("Tempo de execução com vetor ordenado crescente: %.0f ms\n", tempo_crescente);
    printf("Tempo de execução com vetor ordenado decrescente: %.0f ms\n", tempo_decrescente);
}




void print_table_header() {
    printf("\n+------------------+---------------+---------------+---------------+\n");
    printf("|   Execução Nº    | Tempo Médio   | Ordem Cresc.  | Ordem Decresc.|\n");
    printf("+------------------+---------------+---------------+---------------+\n");
}

void print_table_row(int exec_num, double tempo_medio, double tempo_crescente, double tempo_decrescente) {
    printf("| %-16d | %-13.0f | %-13.0f | %-13.0f |\n", exec_num, tempo_medio, tempo_crescente, tempo_decrescente);
    printf("+------------------+---------------+---------------+---------------+\n");
}




// Inclua suas implementações das funções execute_algorithm(), print_time(), rand_seed() e get_current_time_seed() aqui
double execute_algorithm_and_measure_time(int algoritmo_escolhido, int tamanho_vetor, int *vetor) {
    clock_t start, end;
    double tempo_execucao;


    switch (algoritmo_escolhido) {
        case 1:
            // Bubble Sort
            start = clock();
            bubbleSort(vetor, tamanho_vetor);
            end = clock();
            break;
        case 2:
            // Selection Sort
            start = clock();
            selectionSort(vetor, tamanho_vetor);
            end = clock();
            break;
        case 3:
            // Insertion Sort
            start = clock();
            insertionSort(vetor, tamanho_vetor);
            end = clock();
            break;
        case 4:
            // Merge Sort
            start = clock();
            mergeSort(vetor, 0, tamanho_vetor - 1);
            end = clock();
            break;
        case 5:
            // Quick Sort
            start = clock();
            quickSort(vetor, 0, tamanho_vetor - 1);
            end = clock();
            break;
        case 6:
            // Shell Sort
            start = clock();
            shellSort(vetor, tamanho_vetor);
            end = clock();
            break;
        case 7:
            // Heap Sort
            start = clock();
            heapSort(vetor, tamanho_vetor);
            end = clock();
            break;
        case 8:
            // Tim Sort
            start = clock();
            timSort(vetor, tamanho_vetor);
            end = clock();
            break;
        case 9:
            // Radix Sort
            start = clock();
            radixSort(vetor, tamanho_vetor);
            end = clock();
            break;
        default:
            printf("Opção inválida!\n");
            exit(1);
    }


    tempo_execucao = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    return tempo_execucao;
}

//função fisherYates
void fisherYates(int *vetor, int tamanho_vetor) {
    for (int i = tamanho_vetor - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }
}








