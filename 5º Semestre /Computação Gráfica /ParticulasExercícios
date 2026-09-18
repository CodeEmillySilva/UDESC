//Compilação:
// gcc nome_arquivo.c -lglut -lGL -lGLU -lm -o nome_arquivo
// ./nome_arquivo

/*Referência:
    - Slides disponibilizados no Moodle
    - Uso do código disponibilizado pelo professor de fogos de artifício de base
    - Uso de IA para identificação mais rápida 
    de erros e facilitar o entendimento mais rápido 
    de lógica*/

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <unistd.h>

#define ESCAPE 27
#define NUM_PARTICLES 3000
#define FALL 0.03

struct unit_particles {

    float x, y, z, veloc_y;

} particles[NUM_PARTICLES];

int window;

void InitParticle (int pause) {

    for (int i=0; i<NUM_PARTICLES; i++) {
        particles[i].x = (float) ((rand() % 2000) / 100.0 - 8); // como é espalhado na tela
        particles[i].y = 4.13; // de onde parte a neve
        particles[i].veloc_y = - FALL - ((float)(rand() % 200) / 1000); //velocidade de queda
    }

}

void InitGL(int Width, int Height) {

    glClearColor(0.0f, 1.0f, 1.0f, 1.0f); //fundo azul claro
    glClearDepth(1.0); 
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);

    InitParticle(0); //começar a nevar sem pausa

}

void ReSizeGLScene(int Width, int Height) {
  if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene() {

  int i, ative_particles=0;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
  glLoadIdentity();				// Reset The View

  glTranslatef(0.0f,0.0f,-10.0f);

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
  glPointSize(4.0f);

  glBegin(GL_POINTS);
  for(i=0;i<NUM_PARTICLES;i++) {
    particles[i].y += particles[i].veloc_y;
    glVertex3f( particles[i].x, particles[i].y, 0.0f);

    if(particles[i].y < -3.0) {
        particles[i].x = (float) ((rand() % 2000) / 100.0 - 8); // como é espalhado na tela
        particles[i].y = 4.13; // de onde parte a neve
        particles[i].veloc_y = - FALL - ((float)(rand() % 200) / 1000);
    }

  }
  glEnd();

  // swap buffers to display, since we're double buffered.
  glutSwapBuffers();
  usleep(20000);

  if(!ative_particles) InitParticle(1); // reset particles

}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) {

  if (key == ESCAPE) 
  { 
	glutDestroyWindow(window); 
	
	exit(0);                   
  }

}

int main(int argc, char **argv) {  
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(640, 480);  
  glutInitWindowPosition(0, 0);  
  window = glutCreateWindow("Dia nevado");  
  glutDisplayFunc(&DrawGLScene);  
  glutFullScreen();
  glutIdleFunc(&DrawGLScene);
  glutReshapeFunc(&ReSizeGLScene);
  glutKeyboardFunc(&keyPressed);
  InitGL(640, 480);
  glutMainLoop();  

  return 0;
}
