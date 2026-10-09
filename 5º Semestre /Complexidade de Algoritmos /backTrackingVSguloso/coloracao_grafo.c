#include <stdio.h>
#include <stdlib.h>

#define N 25

int grafo[N][N], cor_guloso[N], cor_tracking[N];

int ler_grafo(char *arquivoOrigem){

    //leitura de arquivo
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

int cor_disponivel (int v, int c, int cor[]) { //v= vértice c=cor

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
            cor_guloso[i]=-1;
    }

    for (int i=0; i<N; i++) {
        
        int c = 0;

        //testa desde menor quantidade de cores, e se não estiver disponível testa a próxima
        while (cor_disponivel(i, c, cor_guloso) == 0) {
            c++;
        }

        //quando a cor livre for achada pinta o vértice
        cor_guloso[i]=c;

        //atualiza o total de cores
        if (c+1>total) total=c+1;

    }

    return total;

}

int backtracking (int v, int caixa) {

    if(v==N) return 1; //grafo completamente pintado

    for(int c=0; c<caixa; c++) {
        if (cor_disponivel(v, c, cor_tracking)==1) { //verifica se determinada cor pode
            cor_tracking[v]=c; //colore
            
            if(backtracking(v+1, caixa)==1) return 1; //verifica se é possível com o próximo

            cor_tracking[v]=-1; //caso não seja possível, apaga
        }
    }

    return 0; //não é possível colorir volta sem cor

}

int main () {

    //leitura do arquivo csv
    if(!ler_grafo("grafo_25nos.csv")) return 1;

    int total_guloso = guloso(grafo);

    int caixa=1;

    printf("BackTracking:\n");

    while(1) {

        //aplica -1 como cor a principio
        for (int i=0; i<N; i++) {
            cor_tracking[i]=-1;
        }

        //testa se essa "caixa" de cores é suficiente para o grafo
        if(backtracking(0,caixa)==1) {
            printf("Caixa = %d: conseguiu!\n", caixa);
            break;
        }

        //se não for indica, e acrescenta cores para testar novamente
        printf("Caixa = %d, não foi possível\n", caixa);
        caixa++;
    }

    //indica quantas cores foram necessárias
    printf("Cores guloso: %d\n", total_guloso);
    printf("Cores backtracking: %d\n", caixa);

    return 0;

}
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
