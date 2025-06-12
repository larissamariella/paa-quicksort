# Trabalho sobre QuickSort

## Descrição

Implementação do algoritmo QuickSort e QuickSampleSort baseada no artigo **"A perspective on QuickSort"** de J. JaJa (Computing in Science and Engineering, vol. 2 No. 1, pp. 43-49, 2000).

###v Grupo: Gabriel Jota e Larissa Mariella

## Arquivos

- **`quicksort.c`** - Implementação em C dos algoritmos
- **`README.md`** - Esta documentação
- **`Artigoquicksort.pdf`** - Artigo fonte de referência
- **`QuickSort.pdf`** - Especificação do trabalho

## Algoritmos Implementados

### 1. QuickSort Convencional

Implementação conforme especificação do trabalho:
- Usa o último elemento como pivô
- Particionamento in-place
- Recursão sobre as partições

### 2. QuickSampleSort com 4 Processadores

Implementação baseada no sample sort descrito no artigo:
- **Etapa 1**: Seleção de pivôs através de amostragem aleatória
- **Etapa 2**: Particionamento do array em 4 buckets usando os pivôs
- **Etapa 3**: Ordenação de cada bucket usando QuickSort convencional
- **Etapa 4**: Concatenação dos buckets ordenados

## Compilação e Execução

```bash
# Compilar
gcc -o quicksort quicksort.c

# Executar
./quicksort
```

## Características da Implementação

### QuickSort Convencional
- **Complexidade**: O(n²) no pior caso, O(n log n) no caso médio
- **Estratégia**: Divide-and-conquer
- **Pivô**: Último elemento do subarray

### QuickSampleSort
- **Complexidade**: O(n log n) com alta probabilidade
- **Processadores**: 4 (simulados sequencialmente)
- **Amostragem**: n/4 elementos aleatórios
- **Balanceamento**: Melhor distribuição através da amostragem

## Vantagens do Sample Sort

1. **Melhor balanceamento de carga** - A amostragem estatística reduz a probabilidade de partições desbalanceadas
2. **Independência da distribuição inicial** - Funciona bem mesmo com dados pré-ordenados
3. **Escalabilidade** - Adaptável para diferentes números de processadores
4. **Análise probabilística rigorosa** - Complexidade O(n log n) com alta probabilidade

## Resultados dos Testes

O programa executa dois testes:

1. **Teste 1**: Array pequeno (20 elementos)
   - Mostra passo a passo do SampleSort
   - Compara com QuickSort convencional
   - Verifica corretude

2. **Teste 2**: Array grande (1000 elementos)
   - Demonstra escalabilidade
   - Mede tempo de execução
   - Verifica balanceamento dos buckets

## Referências

- JaJa, J. "A perspective on QuickSort", Computing in Science and Engineering, vol. 2 No. 1, pp. 43-49, 2000.
- Hoare, C.A.R. "Quicksort", The Computer Journal, Vol. 5, No. 1, 1962.
- Knuth, D.E. "The Art of Computer Programming, Vol. 3: Sorting and Searching", Addison-Wesley, 1973.
