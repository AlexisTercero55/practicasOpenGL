/*  PUBLICADO EL 8/31/21
    CODIGO DEL PROFESOR Vargas Castro Daniel
    PLATILLA PARA TRABAJAR EN 3D CON OPENGL Y FREEGLUT
*/
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLboolean proy_orto = GL_TRUE;

void dibujar(void);
void camara (void);
void teclado (unsigned char key, int x, int y);
void redimensionar (int ancho, int alto);
void config_GLUT(void);
void config_OGL(void);

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    config_GLUT();
    config_OGL();
    glutMainLoop();
    return 0;
}

void dibujar(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(1.0);
    glutSwapBuffers();
}

void camara (void) 
{            
    float ancho = GLUT_WINDOW_WIDTH;
    float alto = GLUT_WINDOW_HEIGHT;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (proy_orto) {
        glOrtho(-5, 5, -5, 5, -5, 5);    
    }
    else {
        gluPerspective(45, ancho/alto, 0.1, 1000);
        gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void teclado (unsigned char key, int x, int y) 
{
    switch (key) {
        case 'P':
        case 'p':
            proy_orto = !proy_orto;
            camara();
            break;
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void redimensionar (int ancho, int alto) 
{
    if (alto == 0) alto = 1;
    int lado = ancho < alto ? ancho : alto;
    glViewport((ancho - lado) / 2, (alto - lado) / 2, lado, lado);
    camara();
}


void config_GLUT(void) 
{
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Plantilla");
    glutDisplayFunc(dibujar);
    glutKeyboardFunc(teclado);
    glutReshapeFunc(redimensionar);
}

void config_OGL(void) 
{
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    camara();
}