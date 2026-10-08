#include <stdio.h>
#include <stdlib.h>

#define N 25

int grafo[N][N], cor[N];

int ler_grafo(char *arquivoOrigem){

    FILE *arquivo = fopen(arquivoOrigem, "r");

    if(arquivo==NULL) {
        printf("Erro de abertura"); 
        return 0;
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            fscanf(arquivo,"%d",&grafo[i][j]);
            fgetc(arquivo);
        }
    }

    fclose(arquivo);

    return 1;

}

int cor_disponivel (int v, int c) { //v= vértice c=cor
    for(int i=0; i<N; i++) { //passando por todas verificando
        if (grafo[v][i] == 1 && cor[i]==c) { //se um vizinho já tem cor x volta, a cor já está sendo utilizada
            return 0;
        }
    }
    return 1; //do contrário a cor está livre para ser utilizada
    
}

int guloso (int grafo[N][N]) {

    int total = 0;

    //aplica -1 como cor para todos a prícipio
    for (int i=0; i<N; i++) {
            cor[i]=-1;
    }

    for (int i=0; i<N; i++) {
        
        int c = 0;

        while (cor_disponivel(i,c) == 0) {
            c++;
        }

        cor[i]=c;

        if (c+1>total) total=c+1;

    }

    return total;

}
