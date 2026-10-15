#define GLFW_INCLUDE_NONE
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>  // Header File For The GLFW Library
#include <GL/gl.h>       // Header File For The OpenGL32 Library
#include <GL/glu.h>      // Header File For The GLu32 Library

void processInput(GLFWwindow *window);

// settings
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

// Rotation
static GLfloat yRot = 0.0f;
static GLfloat anguloPernas = 0.0f; //angulo das pernas 
static GLfloat sentidoPernas = 1.0f; //sentido das pernas 
static GLfloat anguloBracoEsq = 0.0f; //angulo do braço esquerdo 
static GLfloat sentidoBracoEsq = 1.0f; //sentido do braço esquerdo 
static GLfloat anguloOmbroEsq = 0.0f; //0 = braço baixo, 90 = braço levantado
static int faseAceno = 3; //0 levantando, 1 acenando, 2 baixando, 3 parado
static int contador = 0; //conta a quantidade de acenos ou quando estiver parado


/* function to reset our viewport after a window resize */
void resizeWindow(GLFWwindow* window, int w, int h )
{
    GLfloat fAspect;  
  
    // Prevent a divide by zero  
    if(h == 0)  
        h = 1;  
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}

// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.  
void setupRC(){  

    // Light values and coordinates  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    // Enable lighting  
    glEnable(GL_LIGHTING);  
  
    // Setup and enable light 0  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    // Enable color tracking  
    glEnable(GL_COLOR_MATERIAL);  
      
    // Set Material properties to follow glColor values  
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    // Black blue background  
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f); 

}  

/* function to handle key press events */
void handleKeyPress(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }

    //começa o aceno com a condição do braço estar parado
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && faseAceno == 3) {
        faseAceno = 0;
    }
    
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
        yRot -= 5.0f;  
  
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)  
        yRot += 5.0f;  
                  
    yRot = (GLfloat)((const int)yRot % 360);  

}

/* Here goes our drawing code */
void drawGLScene(GLFWwindow* window)
{
    GLUquadricObj *pObj;    // Quadric Object  
      
    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

    // chao
    glColor3f(0.35f, 0.35f, 0.35f);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-5.0f, -0.75f, -5.0f);
        glVertex3f(-5.0f, -0.75f,  5.0f);
        glVertex3f( 5.0f, -0.75f,  5.0f);
        glVertex3f( 5.0f, -0.75f, -5.0f);
    glEnd();

	// Draw something  
	pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);  
    
    //tronco
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
        glTranslatef(0.0f, 0.5f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.27f, 0.27f, 0.60f, 26, 13);
	glPopMatrix();

    //cabeça 
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
        glTranslatef(0.0f, 1.40f, 0.0f);
        gluSphere(pObj, 0.23f, 26, 13);
    glPopMatrix();

    //pescoço 
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, 1.10f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.08f, 0.08f, 0.10f, 26, 13);
    glPopMatrix();
   
    //braço esquerdo - que irá acenar

    glPushMatrix();
        //posiciona e elabora o ombro
        glTranslatef(-0.35f, 0.90f, 0.0f);
        glColor3f(0.5f, 0.5f, 0.5f);
        gluSphere(pObj, 0.09f, 20, 10);

        //levanta o braço para o lado, negativo tendo em vista que se trata do lado esquerdo em um plano cartesiano
        glRotatef(-anguloOmbroEsq, 0.0f, 0.0f, 1.0f);

        //braço esquerdo
        glColor3f(1.0f, 1.0f, 1.0f);
        glPushMatrix();
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.07f, 0.06f, 0.30f, 20, 10);
        glPopMatrix();

        glTranslatef(0.0f, -0.30f, 0.0);

        //cotovelo esquerdo
        glColor3f(0.5f, 0.5f, 0.5f);
        gluSphere(pObj, 0.08f, 20, 10);

        //dobre o cotovelo para acompanhar o ombro e possibilitar o aceno
        glRotatef(-(anguloOmbroEsq+anguloBracoEsq), 0.0f, 0.0f, 1.0f);
        
        //antebraço esquerdo
        glColor3f(1.0f,1.0f, 1.0f);
        glPushMatrix();
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.06f, 0.05f, 0.30f, 20, 10);
        glPopMatrix();

        glTranslatef(0.0f, -0.30f, 0.0f);

        //mão
        glColor3f(0.5f, 0.5f, 0.5f);
        gluSphere(pObj, 0.07f, 20, 10);

        // fim do braco esquerdo
        glPopMatrix();

    // ombro direito
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
        glTranslatef(0.35f, 0.90f, 0.0f);
        gluSphere(pObj, 0.09f, 20, 10);
    glPopMatrix();

    //braço direito
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.35f, 0.90f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.07f, 0.06f, 0.30f, 20, 10);
    glPopMatrix();

    //cotovelo direito
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
        glTranslatef(0.35f, 0.60f, 0.0f);
        gluSphere(pObj, 0.08f, 20, 10);
    glPopMatrix();

    // antebraço direito
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.35f, 0.60f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.06f, 0.05f, 0.30f, 20, 10);
    glPopMatrix();

    // mão direita
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
        glTranslatef(0.35f, 0.35f, 0.0f);
        gluSphere(pObj, 0.07f, 20, 10);
    glPopMatrix();
    
    // Cintura
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, 0.40f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.21f, 0.21f, 0.10f, 20, 10);
    glPopMatrix();

    // quadril esquerdo
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
        glTranslatef(-0.14f, 0.30f, 0.0f);
        gluSphere(pObj, 0.09f, 20, 10);
    glPopMatrix();

    // quadril direito
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
        glTranslatef(0.14f, 0.30f, 0.0f);
        gluSphere(pObj, 0.09f, 20, 10);
    glPopMatrix();

    //meio 
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, 0.25f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.08f, 0.08f, 0.15f, 20, 10);
    glPopMatrix();

    // grupo da perna esquerda
    glPushMatrix();

    // posiciona a articulacao no quadril esquerdo
    glTranslatef(-0.14f, 0.30f, 0.0f);

    // rotacao da caminhada
    glRotatef(anguloPernas, 1.0f, 0.0f, 0.0f);

    //coxa esquerda
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.08f, 0.07f, 0.35f, 20, 10);
    glPopMatrix();

    // joelho esquerdo
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
        glTranslatef(0.0f, -0.35f, 0.0f);//aqui
        gluSphere(pObj, 0.08f, 20, 10);
    glPopMatrix();

    //perna esquerda 
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, -0.39f, 0.0f);//aqui
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.08f, 0.09f, 0.35f, 20, 10);
    glPopMatrix();

    // pé esquerdo
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, -0.67f, 0.0f);//aqui
        gluCylinder(pObj, 0.10f, 0.09f, 0.20f, 20, 10);
    glPopMatrix();

    // esfera na ponta do pé esquerdo
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, -0.67f, 0.20f);//aqui
        gluSphere(pObj, 0.09f, 20, 10);
    glPopMatrix();

    // fim do grupo da perna esquerda
    glPopMatrix();

    // grupo da perna direita
    glPushMatrix();

    // posiciona a articulacao no quadril direito
    glTranslatef(0.14f, 0.30f, 0.0f);

    // potacao contraria a perna esquerda
    glRotatef(-anguloPernas, 1.0f, 0.0f, 0.0f);

    //coxa direita
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.08f, 0.07f, 0.35f, 20, 10);
    glPopMatrix();

    // joelho direito
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
        glTranslatef(0.0f, -0.35f, 0.0f);//aqui
        gluSphere(pObj, 0.08f, 20, 10);
    glPopMatrix();

    //perna direita
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, -0.39f, 0.0f);//aqui
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.08f, 0.09f, 0.35f, 20, 10);
    glPopMatrix();

    // pé direito
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, -0.67f, 0.0f);//aqui
        gluCylinder(pObj, 0.10f, 0.09f, 0.20f, 20, 10);
    glPopMatrix();

    // esfera na ponta do pé direito
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, -0.67f, 0.20f);
        gluSphere(pObj, 0.09f, 20, 10);
    glPopMatrix();

    // Fim do grupo da perna direita
    glPopMatrix();

    // Restore the matrix state  
    glPopMatrix();  
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Robô", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resizeWindow);
    glfwSwapInterval(1);
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    resizeWindow(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    setupRC();

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        handleKeyPress(window);

        // Atualiza o angulo das pernas
        anguloPernas += 1.5f * sentidoPernas;

        // Chegou ao limite da frente
        if (anguloPernas >= 30.0f) {
            anguloPernas = 30.0f;
            sentidoPernas = -1.0f;
        }

        // Chegou ao limite de tras
        if (anguloPernas <= -30.0f) {
            anguloPernas = -30.0f;
            sentidoPernas = 1.0f;
        }

        if (faseAceno == 0) {
            // levantando braço
            anguloOmbroEsq+=1.5f;
            if(anguloOmbroEsq>=90.0f){
                anguloOmbroEsq=90.0f;
                contador=0;
                sentidoBracoEsq=1.0f;
                faseAceno=1;
            }
        }
        else if (faseAceno == 1) {
            // acenando

            anguloBracoEsq += 2.0f * sentidoBracoEsq;

            // Chegou ao limite da frente
            if (anguloBracoEsq >= 25.0f) {
                anguloBracoEsq = 25.0f;
                sentidoBracoEsq = -1.0f;
                contador++;
            }

            // Chegou ao limite de tras
            if (anguloBracoEsq <= -25.0f) {
                anguloBracoEsq = -25.0f;
                sentidoBracoEsq = 1.0f;
                contador++;
            }

            if(contador>=4) {
                anguloBracoEsq=0.0f;
                faseAceno=2;
            }
        }

        else if (faseAceno == 2) {
            // baixando
            anguloOmbroEsq-=1.5f;
            if(anguloOmbroEsq<=0.0f){
                anguloOmbroEsq=0.0f;
                contador=0;
                faseAceno=3;
            }
        }
        else {
            //parado espera tecla

        }
        // render
        drawGLScene(window);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    
    }      
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;

}
