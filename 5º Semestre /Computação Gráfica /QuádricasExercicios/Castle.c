/*Primeiro contato com computação gráfica, utilizei:
* Slides disponibilizados pelo professor,
* Site: https://www.inf.ufsc.br/~aldo.vw/grafica/apostilas/openGL/lesson01/index.html
* Eventuais correções com auxílio do ChatGPT para achar o ponto de erro mais rápido
* Código das cores: https://pt.scribd.com/document/396245751/CodeGL-Color
*/

// Compilação: gcc castle.c -lglut -lGL -lGLU -lm -o castle
//             ./castle

//Library to facilitate
#include <GL/glut.h>
  
// Rotation
static GLfloat yRot = 0.0f;

// Change viewing volume and viewport.  Called when window is resized  
void ChangeSize(int w, int h) {

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
    gluPerspective(50.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  

}  
  
  
// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.  
void SetupRC() {  

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
    glClearColor(0.231f, 0.525f, 0.129f, 1.0f);  

}  
  
// Respond to arrow keys (rotate snowman)
void SpecialKeys(int key, int x, int y) {  

    if(key == GLUT_KEY_LEFT)  
        yRot -= 5.0f;  
  
    if(key == GLUT_KEY_RIGHT)  
        yRot += 5.0f;  
                  
    yRot = (GLfloat)((const int)yRot % 360);  
  
    // Refresh the Window  
    glutPostRedisplay();  

}
  
// Called to draw scene  
void RenderScene(void) {

    GLUquadricObj *pObj;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Castle scene, every glPushMatrix need to have a glPopMatrix
    glPushMatrix();

        glTranslatef(0.0f, -1.0f, -15.0f);

        // Castle rotation
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);

        pObj = gluNewQuadric();
        gluQuadricNormals(pObj, GLU_SMOOTH);

        // Tower 1
        // Dark grey
        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(+2.0f, 0.0f, +2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.5f, 0.5f, 3.0f, 26, 10);

        glPopMatrix();

        //Flag Pole 1

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(+2.0f, 0.0f, +2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.06f, 0.06f, 4.3f, 26, 10);

        glPopMatrix();

        // Flag 1

        glColor3f(1.0f, 0.5f, 0.0f);

        glPushMatrix();

            glTranslatef(2.4f, 4.08f, 2.0f);
            glScalef(0.8f, 0.4f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();

        // Tower 2
        // Dark grey
        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-2.0f, 0.0f, +2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.5f, 0.5f, 3.0f, 26, 10);

        glPopMatrix();

        //Flag pole 2

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-2.0f, 0.0f, +2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.06f, 0.06f, 4.3f, 26, 10);

        glPopMatrix();

        // Flag 2

        glColor3f(1.0f, 0.5f, 0.0f);

        glPushMatrix();

            glTranslatef(-1.6f, 4.08f, +2.0f);
            glScalef(0.8f, 0.4f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();

        // Tower 3
        // Dark grey
        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-2.0f, 0.0f, -2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.5f, 0.5f, 3.0f, 26, 10);

        glPopMatrix();

        //Flag pole 3

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-2.0f, 0.0f, -2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.06f, 0.06f, 4.3f, 26, 10);

        glPopMatrix();        

        // Flag 3

        glColor3f(1.0f, 0.5f, 0.0f);

        glPushMatrix();

            glTranslatef(-1.6f, 4.08f, -2.0f);
            glScalef(0.8f, 0.4f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();

        // Tower 4
        // Dark grey
        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(+2.0f, 0.0f, -2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.5f, 0.5f, 3.0f, 26, 10);

        glPopMatrix();

        //Flag pole 4

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(+2.0f, 0.0f, -2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.06f, 0.06f, 4.3f, 26, 10);

        glPopMatrix();

        // Flag 4

        glColor3f(1.0f, 0.5f, 0.0f);

        glPushMatrix();

            glTranslatef(2.4f, 4.08f, -2.0f);
            glScalef(0.8f, 0.4f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();

        // Central Tower
        // Dark grey
        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(0.0f, 0.0f, 0.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.8f, 0.8f, 4.0f, 26, 10);

        glPopMatrix();

        //Flag pole Center 

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(0.0f, 0.0f, 0.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.06f, 0.06f, 5.5f, 26, 10);

        glPopMatrix();

        // Center Flag

        glColor3f(1.0f, 0.5f, 0.0f);

        glPushMatrix();

            glTranslatef(0.4f, 5.2f, 0.0f);
            glScalef(0.8f, 0.5f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();        
        
        // Wall 1

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(0.0f, 1.0f, 2.0f);

            glScalef(4.0, 2.0f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix();        

        // Castle blocks 1

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-1.5f, 2.0f, 2.0f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix();
        
                glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-0.5f, 2.0f, 2.0f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix(); 

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(0.5f, 2.0f, 2.0f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix(); 

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(1.5f, 2.0f, 2.0f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix();

        // Wall 2

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-2.0f, 1.0f, 0.0f);

            glScalef(0.5, 2.0f, 4.0f);
            glutSolidCube(1.0f);

        glPopMatrix();

        // Castle blocks 2

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-2.0f, 2.0f, -1.5f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix();
        
                glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-2.0f, 2.0f, -0.5f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix(); 

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-2.0f, 2.0f, 0.5f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix(); 

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-2.0f, 2.0f, 1.5f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix();

        // Windows Wall 2

        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(-2.0f, 1.5f, 0.0f);

            glScalef(0.8f, 0.40f, 0.5f);

            glutSolidCube(1.0f);

        glPopMatrix(); 

        glPushMatrix();

            glTranslatef(-2.0f, 1.5f, 0.9f);

            glScalef(0.8f, 0.40f, 0.5f);

            glutSolidCube(1.0f);

        glPopMatrix(); 

        glPushMatrix();

            glTranslatef(-2.0f, 1.5f, -0.9f);

            glScalef(0.8f, 0.40f, 0.5f);

            glutSolidCube(1.0f);

        glPopMatrix(); 

        // Wall 3

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(2.0f, 1.0f, 0.0f);

            glScalef(0.5, 2.0f, 4.0f);
            glutSolidCube(1.0f);

        glPopMatrix();

        // Castle blocks 3

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(2.0f, 2.0f, -1.5f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix();
        
                glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(2.0f, 2.0f, -0.5f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix(); 

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(2.0f, 2.0f, 0.5f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix(); 

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(2.0f, 2.0f, 1.5f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix();

        // Windows Wall 3

        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(2.0f, 1.5f, 0.0f);

            glScalef(0.8f, 0.40f, 0.5f);

            glutSolidCube(1.0f);

        glPopMatrix(); 

        glPushMatrix();

            glTranslatef(2.0f, 1.5f, 0.9f);

            glScalef(0.8f, 0.40f, 0.5f);

            glutSolidCube(1.0f);

        glPopMatrix(); 

        glPushMatrix();

            glTranslatef(2.0f, 1.5f, -0.9f);

            glScalef(0.8f, 0.40f, 0.5f);

            glutSolidCube(1.0f);

        glPopMatrix(); 

        // Wall 4

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(0.0f, 1.0f, -2.0f);

            glScalef(4.0, 2.0f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix();

        // Castle blocks 4

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-1.5f, 2.0f, -2.0f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix();
        
                glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(-0.5f, 2.0f, -2.0f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix(); 

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(0.5f, 2.0f, -2.0f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix(); 

        glColor3f(0.35f, 0.35f, 0.35f);

        glPushMatrix();

            glTranslatef(1.5f, 2.0f, -2.0f);

            glScalef(0.5f, 0.6f, 0.5f);
            glutSolidCube(1.0f);

        glPopMatrix();        

        // Windows Wall 4

        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(0.0f, 1.5f, -2.0f);

            glScalef(0.5f, 0.40f, 0.8f);

            glutSolidCube(1.0f);

        glPopMatrix(); 

        glPushMatrix();

            glTranslatef(1.0f, 1.5f, -2.0f);

            glScalef(0.5f, 0.40f, 0.8f);

            glutSolidCube(1.0f);

        glPopMatrix(); 

        glPushMatrix();

            glTranslatef(-1.0f, 1.5f, -2.0f);

            glScalef(0.5f, 0.40f, 0.8f);

            glutSolidCube(1.0f);

        glPopMatrix(); 

        // Door
        glColor3f(0.20f, 0.10f, 0.05f);

        glPushMatrix();

            glTranslatef(0.0f, 0.75f, 2.2f);

            glScalef(1.0f, 1.5f, 0.2f);

            glutSolidCube(1.0f);

        glPopMatrix();

        // Door handle

        glColor3f(0.20f, 0.10f, 0.05f);

        glPushMatrix();

            glTranslatef(0.3f, 0.75f, 2.3f);

            glutSolidSphere(0.07f, 18.0f, 9.0f);

        glPopMatrix();

        // Conical roof 1
        // Dark grey
        glColor4f(1.0f, 0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(-2.0f, +3.0f, +2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.5f, 0.0f, 1.0f, 26, 10);

        glPopMatrix();

        // Conical roof 2
        // Dark grey
        glColor4f(1.0f, 0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(-2.0f, +3.0f, -2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.5f, 0.0f, 1.0f, 26, 10);

        glPopMatrix();

        // Conical roof 3
        // Dark grey
        glColor4f(1.0f, 0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(+2.0f, +3.0f, -2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

        gluCylinder(pObj, 0.5f, 0.0f, 1.0f, 26, 10);

        glPopMatrix();

        // Conical roof 4
        // Dark grey
        glColor4f(1.0f, 0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(+2.0f, +3.0f, +2.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.5f, 0.0f, 1.0f, 26, 10);

        glPopMatrix();

        // Central conical roof 
        // Dark grey
        glColor4f(1.0f, 0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(0.0f, +4.0f, 0.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);            

            gluCylinder(pObj, 0.8f, 0.0f, 1.0f, 26, 10);

        glPopMatrix();

        // Windows - Tower 1
        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(2.0f, 2.45f, -2.5f);

            glScalef(0.20f, 0.40f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();      
        
            glColor3f(0.0f, 0.0f, 0.0f);

            glPushMatrix();

            glTranslatef(2.0f, 2.5f, -1.5f);

            glScalef(0.20f, 0.40f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();   

        // Window - Tower 2
        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(-2.0f, 2.4f, -2.51f);

            glScalef(0.20f, 0.40f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();

                glPushMatrix();

            glTranslatef(-2.0f, 2.45f, -1.5f);

            glScalef(0.20f, 0.40f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();   

        // Window - Tower 3
        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(-2.0f, 2.4f, 2.51f);

            glScalef(0.20f, 0.40f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();

                glPushMatrix();

            glTranslatef(-2.0f, 2.45f, 1.5f);

            glScalef(0.20f, 0.40f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();

        // Window - Tower 4
        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(2.0f, 2.4f, 2.51f);

            glScalef(0.20f, 0.40f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();
        
        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(2.0f, 2.45f, 1.5f);

            glScalef(0.20f, 0.40f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();

        // Window - Center Tower 
        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(0.0f, 2.95f, 0.8f);

            glScalef(0.4f, 0.6f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();
        
        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();

            glTranslatef(0.0f, 2.95f, -0.8f);

            glScalef(0.4f, 0.6f, 0.05f);

            glutSolidCube(1.0f);

        glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();

}    

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Castle");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}
