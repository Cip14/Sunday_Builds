#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

#define RANGE 1000

void mergesort(double arr[], size_t start, size_t end);
void merge(double arr[], size_t start, size_t mid, size_t end);
void print_arr(double arr[], size_t size, char *msg);
void contar_numeros_distintos(double arr[], size_t size, int dist_arr[], int range);
bool checar_ordenado(double arr[], size_t size, int dist_arr[], int range);

int main(int argc, char const *argv[]) {
  if (argc > 2) {
    printf("Uso: merge [tamanho do array aleatorio(unsigned short int)](opcional)\n");
    return 1;
  }

  if (argc == 2 && atoi(argv[1]) > USHRT_MAX) {
    printf("Tamanho máximo excedido\n");
    return 1;
  }

  size_t size;
  if (argc == 1) {
    size = USHRT_MAX;
  }else{
    size = atoi(argv[1]);
  }
  double arr[size];

  time_t t;
  srand((unsigned) time(&t));
  for (size_t i = 0; i < size; i++) {
    arr[i] = rand() % RANGE;
  }

  int dist_arr[RANGE];
  contar_numeros_distintos(arr, size, dist_arr, RANGE);

  print_arr(arr, size, "Array aleatorio");

  clock_t inicio, fim;
  double diff;
  inicio = clock();

  mergesort(arr, 0, size - 1);

  fim = clock();
  diff = (double)(fim - inicio)/CLOCKS_PER_SEC;

  print_arr(arr, size, "Array ordenado");
  printf("Tempo de execução: %f s\n", diff);
  if (checar_ordenado(arr, size, dist_arr, RANGE)) {
    printf("Funciona :)\n");
  }

  return 0;
}

void mergesort(double arr[], size_t start, size_t end){
  if (start < end) {
    size_t mid = (start + end) / 2;
    mergesort(arr, start, mid);
    mergesort(arr, mid + 1, end);
    merge(arr, start, mid, end);
  }
}

void merge(double arr[], size_t start, size_t mid, size_t end) {
  size_t tamanho = end - start + 1;
  size_t a = start;
  size_t b = mid + 1;
  bool fim_a = false, fim_b = false;
  double sorted[tamanho];

  for (size_t i = 0; i < tamanho; i++) {
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
  for (size_t i = start, j = 0; i <= end; i++) {
    arr[i] = sorted[j++];
  }
}

void print_arr(double arr[], size_t size, char *msg){
  printf("\n%s\n", msg);
  for (size_t i = 0; i < size; i++) {
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

void contar_numeros_distintos(double arr[], size_t size, int dist_arr[], int range){
  for (int i = 0; i < range; i++) {
    dist_arr[i] = 0;
  }
  for (size_t i = 0; i < size; i++) {
    dist_arr[(int)arr[i]]++;
  }
}

bool checar_ordenado(double arr[], size_t size, int dist_arr[], int range){
  for (size_t i = 0; i < size - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      printf("Array fora de ordem\n");
      return false;
    }
    dist_arr[(int)arr[i]]--;
  }
  dist_arr[(int)arr[size - 1]]--;

  for (int i = 0; i < range; i++) {
    if (dist_arr[i] != 0) {
      printf("Integridade de dados comprometida\n");
      return false;
    }
  }
}
