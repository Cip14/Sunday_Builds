#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ALTURA 25
#define LARGURA 25

void closemaze(int lar, int alt, bool maze[lar][alt], bool visto[lar][alt]);
void printmaze(int lar, int alt, bool maze[lar][alt]);
void gerarmaze(int lar, int alt, bool maze[lar][alt], bool visto[lar][alt]);
void pathfinder(int lar, int alt, bool maze[lar][alt], bool visto[lar][alt], int x, int y);
int oddrand(int min, int max);

int main(int argc, char const *argv[]) {
  int lar = LARGURA*2+1, alt = ALTURA*2+1;
  bool maze[lar][alt], visto[lar][alt];

  closemaze(lar, alt, maze, visto);
  gerarmaze(lar, alt, maze, visto);
  printmaze(lar, alt, maze);

  return 0;
}

// Inicializa o maze todo fechado e o mapa "visto" que registra pontos
// visitados
void closemaze(int lar, int alt, bool maze[lar][alt], bool visto[lar][alt]){
  for (int i = 0; i < alt; i++) {
    for (int j = 0; j < lar; j++) {
      maze[j][i] = true;
      visto[j][i] = false;
    }
  }
}

void printmaze(int lar, int alt, bool maze[lar][alt]){
  for (int i = 0; i < alt; i++) {
    for (int j = 0; j < lar; j++) {
      if (maze[j][i]) {
        printf("# ");
      }else{
        printf("  ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

// Aqui se inicia a magia
void gerarmaze(int lar, int alt, bool maze[lar][alt], bool visto[lar][alt]){
  // gera e exibe a semente para replicação do labirinto
  long seed = time(NULL);
  printf("Seed: %li\n", seed);
  srand(seed);
  // Determina um ponto inicial aleatorio impar
  // Pontos iniciais pares tendem a gerar paredes externas duplas
  int x = oddrand(1, lar);
  int y = oddrand(1, alt);
  maze[x][y] = false;
  visto[x][y] = true;

  pathfinder(lar, alt, maze, visto, x, y);
}

// função recursiva para abrir caminhos criando o labirinto
void pathfinder(int lar, int alt, bool maze[lar][alt], bool visto[lar][alt], int x, int y) {
  int nPaths = 0;
  int path[4];
  bool atravessouParede;
  // itera pelas 4 direções possiveis
  // conta e registra quantos e quais os caminhos disponiveis
  for (int c = 0, i, j; c < 4; c++) {
    switch (c) {
      case 0:
      i = 0;
      j = -2;
      break;
      case 1:
      i = 0;
      j = 2;
      break;
      case 2:
      i = 2;
      j = 0;
      break;
      case 3:
      i = -2;
      j = 0;
      break;
    }

    if (x + i < 1 || x + i > lar - 2 || y + j < 1 || y + j > alt - 2) {
      atravessouParede = true;
    }else{
      atravessouParede = false;
    }

    if (!atravessouParede && !visto[x + i][y + j]) {
      path[nPaths] = c;
      nPaths++;
    }
  }

  // caso o pathfinder não encontre mais nenhum caminho
  // ele retona o trabalho para o pathfinder anterior
  if (nPaths == 0) {
    return;
  }

  int escolha = rand() % nPaths;
  for (int i = 0; i < 2; i++) {
    switch (path[escolha]) {
      case 0:
      y--;
      break;
      case 1:
      y++;
      break;
      case 2:
      x++;
      break;
      case 3:
      x--;
      break;
    }
    maze[x][y] = false;
    visto[x][y] = true;
  }
  // apos dar dois passos na direção escolhida pathfinder irá
  // chamar outro de si mesmo para dar mais dois passos
  pathfinder(lar, alt, maze, visto, x, y);
  // ao retornar ao ponto anterior um novo pathfinder ira buscar um
  // novo caminho disponivel ou retornar novamente
  pathfinder(lar, alt, maze, visto, x, y);
}

int oddrand(int min, int max){
  int x;
  do{
    x = rand () % (max - min) + min;
  }while(x % 2 == 0);
  return x;
}
