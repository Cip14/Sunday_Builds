#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

void mergesort(double arr[], unsigned int start, unsigned int end);
void merge(double arr[], unsigned int start, unsigned int mid, unsigned int end);
void print_arr(double arr[], unsigned int size, char *msg);

int main(int argc, char const *argv[]) {
  if (argc > 2) {
    printf("Uso: merge [tamanho do array aleatorio(unsigned int)](opcional)\n");
    return 1;
  }

  if (argc == 2 && atoi(argv[1]) > UINT_MAX) {
    printf("Tamanho máximo excedido\n");
    return 1;
  }

  unsigned int size;
  if (argc == 1) {
    size = UINT_MAX;
  }else{
    size = atoi(argv[1]);
  }
  double arr[size];

  time_t t;
  srand((unsigned) time(&t));
  for (unsigned int i = 0; i < size; i++) {
    arr[i] = rand() % 1000;
  }

  print_arr(arr, size, "Array aleatorio");

  clock_t inicio, fim;
  double diff;
  inicio = clock();

  mergesort(arr, 0, size - 1);

  fim = clock();
  diff = (double)(fim - inicio)/CLOCKS_PER_SEC;

  print_arr(arr, size, "Array ordenado");
  printf("Tempo de execução: %f s\n", diff);

  return 0;
}

void mergesort(double arr[], unsigned int start, unsigned int end){
  if (start < end) {
    int mid = (start + end) / 2;
    mergesort(arr, start, mid);
    mergesort(arr, mid + 1, end);
    merge(arr, start, mid, end);
  }
}

void merge(double arr[], unsigned int start, unsigned int mid, unsigned int end) {
  unsigned int tamanho = end - start + 1;
  unsigned int a = start;
  unsigned int b = mid + 1;
  bool fim_a = false, fim_b = false;
  double sorted[tamanho];

  for (unsigned int i = 0; i < tamanho; i++) {
    if (!fim_a && !fim_b) {
      if (arr[a] < arr[b]) {
        sorted[i] = arr[a++];
      }else{
        sorted[i] = arr[b++];
      }
      if (a > mid) {
        fim_a = true;
      }
      if (b > end) {
        fim_b = true;
      }
    }else{
      if (!fim_a) {
        sorted[i] = arr[a++];
      }else{
        sorted[i] = arr[b++];
      }
    }
  }
  for (unsigned int i = start, j = 0; i <= end; i++) {
    arr[i] = sorted[j++];
  }
}

void print_arr(double arr[], unsigned int size, char *msg){
  printf("\n%s\n", msg);
  for (unsigned int i = 0; i < size; i++) {
    if (i % 30 == 0 && i > 1) {
      printf("\n");
    }
    printf("%3.0f | ", arr[i]);
    if (i > 120) {
      printf("...");
      break;
    }
  }
  printf("\n\n");
}
