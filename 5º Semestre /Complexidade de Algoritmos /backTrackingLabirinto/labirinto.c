#include <stdio.h>
#include <stdlib.h>


#define N 61


int isSafe(int maze[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 0);
}

int solveMazeUtil(int maze[N][N], int x, int y) {

    if (x==N-1 && y==N-1 && maze[x][y]==0){
        maze[x][y]=2;
        return 1;
    }

    if (isSafe(maze, x, y)) {

        maze[x][y] = 2;

        if (solveMazeUtil(maze, x + 1, y)) {
            return 1;
        }

        if (solveMazeUtil(maze, x - 1, y)) {
            return 1;
        }

        if (solveMazeUtil(maze, x, y + 1)) {
            return 1;
        }

        if (solveMazeUtil(maze, x, y - 1)) {
            return 1;
        }

        maze[x][y]=-1;

        return 0;

    }

    return 0;
}

void printMaze(int maze[N][N]){
    printf("Caminho no labirinto:\n");
    printf("\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(maze[i][j] == 1){
                printf("*");
            }else if(maze[i][j] == 2){
                printf("O");
            }else{
                printf(" ");
            }
            //printf("%d ", maze[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

int solveMaze(int maze[N][N]) {
    // Iniciar a busca a partir do ponto de partida (0, 0)

    if (solveMazeUtil(maze, 0, 0) == 0) {
        printf("N�o h� solu��o para o labirinto.\n");
        return 0;
    }

    // Imprimir
    printMaze(maze);
    return 1;
}

void loadMaze(int maze[N][N], char *fname){
    //gere um nesse site, cole no arquivo lab.txt ou outro
    //https://www.dcode.fr/maze-generator
    //veja quantas linhas e colunas tem e altere o valor de N
    //uma diferen�a de 1 na quantia de colunas geralmente n�o causa problema
    //pois o algoritmo aqui inclui uma borda extra
    FILE *f;
    int i, lineN = 0;
    char line[N+10];
    f = fopen(fname, "r");
    while(fgets(line, sizeof(line), f) != NULL){
        i = 0;
        if(line[0]=='0' || line[0] == '1'){
            while(line[i] != '\0'){
                maze[lineN][i] = line[i] - '0';
                i++;
                if(i>=N) break;
            }
            lineN++;
            if(lineN>=N){ break;}
        }
    }

    printf("i: %d, LineN: %d\n", i, lineN);

}

int main() {

    int maze[N][N];

    loadMaze(maze, "lab.txt");

    if (solveMaze(maze)) {
        printf("Labirinto resolvido!\n");
    } else {
        printf("Não foi possível encontrar uma solução.\n");
    }

    return 0;
}

