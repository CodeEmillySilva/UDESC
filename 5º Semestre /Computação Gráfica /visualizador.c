#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define MAX 10000

float vertices [MAX][3]; //linha canto, coluna xyz
int numeroVertices = 0;
float pontos[MAX][2]; //pontos na foto
int numeroPontos = 0;

typedef struct {

    char nomeMaterial[100];
    char fotoNome[200];
    GLuint textura;

} Material;

Material materiais[50];
int materialNum=0;

typedef struct {

    int material; //imagem utilizada
    int quant; //quantidade de pontos
    int v[10]; //vertices
    int c[10]; //pontos

} Face;

Face faces[MAX];
int numFaces = 0;

float angX = 20, angY = -30;

void ler_mtl(char *arquivo) {

    char linha[500];
    FILE *f = fopen(arquivo, "r");
    if (f==NULL) return;

    while (fgets(linha, sizeof(linha), f) != NULL) {

        linha[strcspn(linha,"\r\n")] = '\0'; //tira a quebra de linha na leitura para não impossibilitar o funcionamento

        if (strncmp(linha, "newmtl ", 7)==0) {

            strcpy(materiais[materialNum].nomeMaterial, linha+7); //compiar para próximo bloco livre
            materiais[materialNum].fotoNome[0]='\0'; //caso não tenho objeto permanece vazia
            materialNum++;

        } else if (strncmp(linha, "map_Kd ", 7)==0) {

            char *nome = linha+7;
            char *barra = strrchr(nome, '/');
            if (barra==NULL) barra = strrchr(nome, '\\');
            if (barra != NULL) nome = barra +1;
            strcpy(materiais[materialNum-1].fotoNome, nome); //guarda exclusivamente a imagem criada no último material instanciado

        }

    }

    fclose(f);

}

int materialAchar (char *nome) {

    for(int i=0; i<materialNum; i++) {
        if(strcmp(materiais[i].nomeMaterial, nome)==0) return i;
    }

    return -1;

}

void leituraObj (char *arq) {

    char linha[500];

    int atual = -1;

    FILE *f = fopen(arq, "r");

    if(f==NULL) {

        printf("Nada encontrado ou problema");
        exit(1);

    }

    while(fgets(linha, sizeof(linha), f) != NULL) {

        linha[strcspn(linha, "\r\n")] = '\0';

        if(strncmp(linha,"v ", 2)==0) { //vertice
            sscanf(linha, "v%f %f %f", &vertices[numeroVertices][0], &vertices[numeroVertices][1], &vertices[numeroVertices][2]);
            numeroVertices++;
        } else if (strncmp(linha, "vt ", 3)==0) { //ponto
            sscanf(linha, "vt %f %f", &pontos[numeroPontos][0], &pontos[numeroPontos][1]);
            numeroPontos++;
        } else if (strncmp(linha, "mtllib ", 7) == 0) { //qual arquivo
            ler_mtl(linha+7);
        } else if (strncmp(linha, "usemtl ", 7) == 0) {
            atual = materialAchar(linha+7);
        } else if (strncmp(linha, "f ", 2) == 0) {
            Face *face = &faces[numFaces];
            char *pedaco = strtok (linha+2, " ");
            face->quant = 0;
            face->material = atual;
        
            while (pedaco != NULL && face->quant < 10) {
                int x=0, y=0;

                sscanf(pedaco, "%d/%d", &x, &y);
                face->v[face->quant]=x-1;
                face->c[face->quant]=y-1;
                face->quant++;
                pedaco=strtok(NULL, " ");

            }

            numFaces++;

        } 

    }

    fclose(f);

}

void carregarTex (void) {

    int larg, alt, canais;

    unsigned char *pixels; //cor da imagem

    stbi_set_flip_vertically_on_load(1); //garante que a foto não apareça invertida

    for (int i=0; i<materialNum; i++) {
        materiais[i].textura=0;
        if(materiais[i].fotoNome[0]=='\0') continue;

        pixels=stbi_load(materiais[i].fotoNome, &larg, &alt, &canais, 4); //devolve as proporções que serão utilizadas para fazer a imagem

        if(pixels==NULL) {
            printf("erro no pixel");
            continue;
        }

        //fazer com que o que se encontra na RAM passe para placa de vídeo

        glGenTextures(1, &materiais[i].textura);
        glBindTexture(GL_TEXTURE_2D, materiais[i].textura);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, larg, alt, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        stbi_image_free(pixels);

    }

}

void desenho(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 6,
              0, 0, 0,
              0, 1, 0);
    glRotatef(angX, 1, 0, 0);
    glRotatef(angY, 0, 1, 0);

    glEnable(GL_TEXTURE_2D);
    glColor3f(1,1,1);

    for(int i=0; i<numFaces; i++) {
        int m = faces[i].material;

        //foto ou sem foto
        if(m>=0) {
            glBindTexture(GL_TEXTURE_2D, materiais[m].textura);
        } else {
            glBindTexture(GL_TEXTURE_2D,0);
        }

        glBegin(GL_POLYGON);

        for(int j=0; j<faces[i].quant; j++) {
            int k = faces[i].c[j]; //ponto
            int p = faces[i].v[j]; //vertice

            if(k>=0) glTexCoord2f(pontos[k][0], pontos[k][1]);

            glVertex3f(vertices[p][0], vertices[p][1], vertices[p][2]);

        }

        glEnd();
    
    }

    glutSwapBuffers();

}

void redimensionar (int width, int height) {

    if (height==0) height=1;

    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)width/height, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

}

void teclado (unsigned char tecla, int x, int y) {

    if (tecla == 'a') angY -= 10; //esq
    if (tecla == 'd') angY += 10; //dir
    if (tecla == 'w') angX -= 10; //tras
    if (tecla == 's') angX += 10; //frente
    if (tecla == 27) exit(0);
    glutPostRedisplay();

}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,700);
    glutCreateWindow("CaixaOpenGL");
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);

    leituraObj("caixa.obj");
    carregarTex();

    glutDisplayFunc(desenho);
    glutReshapeFunc(redimensionar);
    glutKeyboardFunc(teclado);
    glutMainLoop();

    return 0;

}
