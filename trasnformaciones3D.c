/*  9/9/21
    CODIGO PUBLICADO POR EL PROFESOR Vargas Castro Daniel
    PROGRAMA DE IMPLEMENTACION QUE APLICA TRANSFORMACIONES
    AFINES: TRASLACION, ROTACION Y ESCALA A OBJETOS 3D.

    Dibuja un sistema de coordenadas global y una tetera con 
    sus coordenadas locales. La tetera se puede mover con las 
    teclas WASD, rotar con las teclas IJKL o escalar con las 
    teclas + y -, mientras que el sistema de coordenadas global 
    permanece intacto.
*/
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//Variables de traslación en X y Y.
GLfloat tx = 0;
GLfloat ty = 0;
//Variables de rotación en X y Y.
GLfloat rx = 0;
GLfloat ry = 0;
//Variable de escala en todos los ejes.
GLfloat es = 1;

GLboolean proy_orto = GL_FALSE;

//Función que dibuja los ejes X, Y y Z.
void ejes(void) {
    glBegin(GL_LINES);
        //Eje X
        glVertex3f(-10, 0, 0);
        glVertex3f(10, 0, 0);
        //Eje Y
        glVertex3f(0, -10, 0);
        glVertex3f(0, 10, 0);
        //Eje Z
        glVertex3f(0, 0, -10);
        glVertex3f(0, 0, 10);
    glEnd();
}

void dibujar(void) {
    //Matrices de transformacion traspuestas (para usar con glMultMatrix)
    GLfloat tras[16] = {1,  0,  0, 0,
                        0,  1,  0, 0,
                        0,  0,  1, 0,
                        tx, ty, 0, 1};
    GLfloat esc[16] = { es,  0,  0, 0,
                         0, es,  0, 0, 
                         0,  0, es, 0,
                         0,  0,  0, 1};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Dibujo del sistema de coordenadas global.
    ejes(); 
    
    
    glPushMatrix(); //Empieza sistema de coordenadas local para la tetera.
    //Transformaciones para este sistema local.
        //glMultMatrixf(tras);  //Se puede trasladar también de esta forma.
        glTranslatef(tx, ty, 0);
        glRotatef(rx, 1, 0, 0);
        glRotatef(ry, 0, 1, 0);
        //glMultMatrixf(esc);   //Se puede escalar también de esta forma.
        glScalef(es, es, es);
        
        //Se dibuja después de hacer las transformaciones.
        ejes(); 
        glutSolidTeapot(1.0);
    glPopMatrix();  //Termina sistema de coordenadas local para la tetera.

    //Otro sistema de coordenadas local
    /*glPushMatrix();
        glTranslatef(-3, -5, 0);
        ejes(); 
        glutSolidCube(1.0);
    glPopMatrix();*/

    glutSwapBuffers();
}

void camara (void) {            
    float ancho = GLUT_WINDOW_WIDTH;
    float alto = GLUT_WINDOW_HEIGHT;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (proy_orto) {
        glOrtho(-5, 5, -5, 5, -5, 5);    
    }
    else {
        gluPerspective(45, ancho/alto, 0.1, 1000);
        gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void teclado (unsigned char key, int x, int y) {
    switch (key) {
        case 'P': case 'p':
            proy_orto = !proy_orto;
            camara();
            break;
        //TRASLACIÓN
        case 'W': case 'w': ty += 0.1; break;
        case 'S': case 's': ty -= 0.1; break;
        case 'A': case 'a': tx -= 0.1; break;
        case 'D': case 'd': tx += 0.1; break;
        //ROTACIÓN
        case 'I': case 'i': rx += 5; break;
        case 'K': case 'k': rx -= 5; break;
        case 'J': case 'j': ry += 5; break;
        case 'L': case 'l': ry -= 5; break;
        //ESCALA
        case '+': es += 0.1; break;
        case '-': es -= 0.1; break;
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void redimensionar (int ancho, int alto) {
    if (alto == 0) alto = 1;
    int lado = ancho < alto ? ancho : alto;
    glViewport((ancho - lado) / 2, (alto - lado) / 2, lado, lado);
    camara();
}


void config_GLUT(void) {
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Plantilla");
    glutDisplayFunc(dibujar);
    glutKeyboardFunc(teclado);
    glutReshapeFunc(redimensionar);
}

void config_OGL(void) {
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    camara();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    config_GLUT();
    config_OGL();
    glutMainLoop();
    return 0;
}