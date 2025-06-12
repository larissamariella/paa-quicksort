#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Função para trocar dois elementos
void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// QuickSort convencional conforme especificado no trabalho
void quicksort(int A[], int esq, int dir) {
    int i = esq;
    int j = dir;
    int pivo = A[dir];
    
    do {
        while (A[i] < pivo) i = i + 1;
        while (A[j] > pivo) j = j - 1;
        
        if (i <= j) {
            troca(&A[i], &A[j]);
            i = i + 1;
            j = j - 1;
        }
    } while (i <= j);
    
    if (j > esq) quicksort(A, esq, j);
    if (i < dir) quicksort(A, i, dir);
}

// Função para encontrar pivôs usando amostragem
void encontrarPivos(int A[], int n, int numProcessadores, int pivos[]) {
    int amostrasSize = n / 4; // Tamanho da amostra
    int *amostras = (int*)malloc(amostrasSize * sizeof(int));
    
    // Coleta amostras aleatórias
    srand(time(NULL));
    for (int i = 0; i < amostrasSize; i++) {
        amostras[i] = A[rand() % n];
    }
    
    // Ordena as amostras
    quicksort(amostras, 0, amostrasSize - 1);
    
    // Seleciona pivôs uniformemente distribuídos
    for (int i = 0; i < numProcessadores - 1; i++) {
        int indice = (i + 1) * amostrasSize / numProcessadores;
        pivos[i] = amostras[indice];
    }
    
    free(amostras);
}

// Função para particionar o array usando os pivôs
void particionarArray(int A[], int n, int pivos[], int numProcessadores, 
                     int **buckets, int tamanhosBuckets[]) {
    
    // Inicializa contadores
    for (int i = 0; i < numProcessadores; i++) {
        tamanhosBuckets[i] = 0;
    }
    
    // Conta elementos para cada bucket
    for (int i = 0; i < n; i++) {
        int bucket = 0;
        for (int j = 0; j < numProcessadores - 1; j++) {
            if (A[i] <= pivos[j]) {
                bucket = j;
                break;
            }
            bucket = j + 1;
        }
        tamanhosBuckets[bucket]++;
    }
    
    // Aloca memória para os buckets
    for (int i = 0; i < numProcessadores; i++) {
        buckets[i] = (int*)malloc(tamanhosBuckets[i] * sizeof(int));
    }
    
    // Reseta contadores para reutilizar como índices
    int indices[numProcessadores];
    for (int i = 0; i < numProcessadores; i++) {
        indices[i] = 0;
    }
    
    // Distribui elementos nos buckets
    for (int i = 0; i < n; i++) {
        int bucket = 0;
        for (int j = 0; j < numProcessadores - 1; j++) {
            if (A[i] <= pivos[j]) {
                bucket = j;
                break;
            }
            bucket = j + 1;
        }
        buckets[bucket][indices[bucket]++] = A[i];
    }
}

// QuickSampleSort com 4 processadores conforme especificação do artigo
void quickSampleSort(int A[], int n) {
    const int numProcessadores = 4;
    int pivos[numProcessadores - 1];
    int **buckets = (int**)malloc(numProcessadores * sizeof(int*));
    int tamanhosBuckets[numProcessadores];
    
    printf("=== Iniciando QuickSampleSort com %d processadores ===\n", numProcessadores);
    
    // Etapa 1: Encontrar pivôs usando amostragem aleatória
    printf("Etapa 1: Selecionando pivôs através de amostragem...\n");
    encontrarPivos(A, n, numProcessadores, pivos);
    
    printf("Pivôs selecionados: ");
    for (int i = 0; i < numProcessadores - 1; i++) {
        printf("%d ", pivos[i]);
    }
    printf("\n");
    
    // Etapa 2: Particionar o array usando os pivôs
    printf("Etapa 2: Particionando array em %d buckets...\n", numProcessadores);
    particionarArray(A, n, pivos, numProcessadores, buckets, tamanhosBuckets);
    
    printf("Tamanhos dos buckets: ");
    for (int i = 0; i < numProcessadores; i++) {
        printf("P%d:%d ", i+1, tamanhosBuckets[i]);
    }
    printf("\n");
    
    // Etapa 3: Ordenar cada bucket usando QuickSort convencional
    printf("Etapa 3: Ordenando buckets com QuickSort convencional...\n");
    for (int i = 0; i < numProcessadores; i++) {
        if (tamanhosBuckets[i] > 1) {
            printf("Processador %d ordenando %d elementos...\n", i+1, tamanhosBuckets[i]);
            quicksort(buckets[i], 0, tamanhosBuckets[i] - 1);
        }
    }
    
    // Etapa 4: Juntar os buckets ordenados de volta no array original
    printf("Etapa 4: Juntando buckets ordenados...\n");
    int indice = 0;
    for (int i = 0; i < numProcessadores; i++) {
        for (int j = 0; j < tamanhosBuckets[i]; j++) {
            A[indice++] = buckets[i][j];
        }
    }
    
    // Libera memória
    for (int i = 0; i < numProcessadores; i++) {
        free(buckets[i]);
    }
    free(buckets);
    
    printf("=== QuickSampleSort concluído ===\n");
}

// Função auxiliar para imprimir array
void imprimirArray(int A[], int n, char *titulo) {
    printf("%s: ", titulo);
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Função para verificar se array está ordenado
int verificarOrdenacao(int A[], int n) {
    for (int i = 1; i < n; i++) {
        if (A[i] < A[i-1]) {
            return 0; // Não está ordenado
        }
    }
    return 1; // Está ordenado
}

// Função para gerar array aleatório
void gerarArrayAleatorio(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1000; // Números entre 0 e 999
    }
}

int main() {
    printf("========================================\n");
    printf("   IMPLEMENTAÇÃO QUICKSORT E SAMPLE SORT\n");
    printf("   Baseado no artigo de J. JaJa (2000)\n");
    printf("========================================\n\n");
    
    // Teste com array pequeno
    printf("TESTE 1: Array pequeno (20 elementos)\n");
    printf("-------------------------------------\n");
    int tamanho1 = 20;
    int *array1 = (int*)malloc(tamanho1 * sizeof(int));
    int *copia1 = (int*)malloc(tamanho1 * sizeof(int));
    
    gerarArrayAleatorio(array1, tamanho1);
    memcpy(copia1, array1, tamanho1 * sizeof(int));
    
    imprimirArray(array1, tamanho1, "Array original");
    
    printf("\n--- Teste QuickSort Convencional ---\n");
    quicksort(copia1, 0, tamanho1 - 1);
    imprimirArray(copia1, tamanho1, "Array ordenado (QuickSort)");
    printf("Verificação: %s\n", verificarOrdenacao(copia1, tamanho1) ? "CORRETO" : "ERRO");
    
    printf("\n--- Teste QuickSampleSort ---\n");
    quickSampleSort(array1, tamanho1);
    imprimirArray(array1, tamanho1, "Array ordenado (SampleSort)");
    printf("Verificação: %s\n", verificarOrdenacao(array1, tamanho1) ? "CORRETO" : "ERRO");
    
    free(array1);
    free(copia1);
    
    // Teste com array maior
    printf("\n\nTESTE 2: Array grande (1000 elementos)\n");
    printf("--------------------------------------\n");
    int tamanho2 = 1000;
    int *array2 = (int*)malloc(tamanho2 * sizeof(int));
    
    gerarArrayAleatorio(array2, tamanho2);
    
    printf("Array gerado com %d elementos aleatórios\n", tamanho2);
    
    clock_t inicio = clock();
    quickSampleSort(array2, tamanho2);
    clock_t fim = clock();
    
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.6f segundos\n", tempo);
    printf("Verificação: %s\n", verificarOrdenacao(array2, tamanho2) ? "CORRETO" : "ERRO");
    
    free(array2);
    
    printf("\n========================================\n");
    printf("           TESTES CONCLUÍDOS\n");
    printf("========================================\n");
    
    return 0;
} 