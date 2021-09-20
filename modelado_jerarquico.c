/*  9/9/21
    CODIGO PUBLICADO POR EL PROFESOR Vargas Castro Daniel
    PROGRAMA DE DEMOSTRACION DE TECNICAS DE MODELADO.

    Dibuja una escena con una casa y un árbol sobre un piso, 
    utilizando modelado jerárquico con base en el grafo de 
    escena de la página 25 de esta presentación. Se puede 
    transformar todo el modelo con los mismo controles que 
    en transformaciones3D.c. Este código se puede usar como 
    base para su tarea 2.
*/
#include <math.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define PI 3.14159265358979323846

//Variables de traslación en X y Y.
GLfloat tx = 0;
GLfloat ty = 0;
//Variables de rotación en X y Y.
GLfloat rx = 0;
GLfloat ry = 0;
//Variables de escala en todos los ejes.
GLfloat es = 1;

GLboolean proy_orto = GL_FALSE;

//Función que dibuja un plano normal al eje Y.
void plano_xz(GLfloat l) {
    glPushMatrix();
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(-l/2, 0, l/2);
        glVertex3f(l/2, 0, l/2);
        glVertex3f(l/2, 0, -l/2);
        glVertex3f(-l/2, 0, -l/2);
    glEnd();
    glPopMatrix();
}

//Función que dibuja un cilindro sólido.
void cilindro_solido (GLfloat r, GLfloat h, GLint n) {
    //Variables para generar los vértices del cilindro.
    int i;
    float theta;
    float xi, yi, zi;
    struct vertice2D {
        GLfloat x;
        GLfloat y;
    };
    typedef struct vertice2D v2D;
    v2D *verts = NULL;

    //Reservación de memoria para los vértices.
    verts = malloc(n*sizeof(v2D));

    //Cálculo de los vértices.
    for (i = 0; i < n; i++) {
        theta = 2 * PI * (i/(float)n);
        verts[i].x = r * cos(theta);
        verts[i].y = r * sin(theta);
    }
    
    //Empieza dibujo del cilindro.
    glEnable(GL_NORMALIZE);
    //Caras superficie.
    glBegin(GL_QUAD_STRIP);
        for (i = 0; i < n; i++) {
            glNormal3f(verts[i].x, verts[i].y, h/2);
            glVertex3f(verts[i].x, verts[i].y, h/2);
            glVertex3f(verts[i].x, verts[i].y, -h/2);
        }
        glNormal3f(verts[0].x, verts[0].y, h/2);
        glVertex3f(verts[0].x, verts[0].y, h/2);
        glVertex3f(verts[0].x, verts[0].y, -h/2);
    glEnd();
    
    //Cara trasera.
    glNormal3f(0, 0, -1);
    glBegin(GL_POLYGON);
        for (i = 0; i < n; i++) {
            glVertex3f(verts[i].x, verts[i].y, -h/2);
            glVertex3f(verts[i].x, verts[i].y, -h/2);
        }
    glEnd();

    //Cara frontal.
    glNormal3f(0, 0, 1);
    glBegin(GL_POLYGON);
        for (i = 0; i < n; i++) {
            glVertex3f(verts[i].x, verts[i].y, h/2);
            glVertex3f(verts[i].x, verts[i].y, h/2);
        }
    glEnd();
    glDisable(GL_NORMALIZE);
    
    free(verts);
}

//Función que dibuja el piso.
void piso(void) {
    glPushMatrix();
        plano_xz(10);
    glPopMatrix();
}

//Función que dibuja la casa.
void dibujar_casa(void) {
    //Dibujo de la base de la casa.
    glPushMatrix();
        glutSolidCube(2);
    glPopMatrix();

    //Dibujo del techo de la casa.
    glPushMatrix();
        glTranslatef(0, 1, 0);
        glRotatef(45, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2, 1, 4, 1);
    glPopMatrix();
}

//Función que dibuja el árbol.
void dibujar_arbol(void) {
    //Dibujo del tronco del árbol.
    glPushMatrix();
        glTranslatef(0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        cilindro_solido(0.25, 2, 20);
    glPopMatrix();

    //Dibujo del follaje del árbol.
    glPushMatrix();
        glTranslatef(0, 2, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidSphere(1, 20, 20);
    glPopMatrix();
}

void dibujar(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //La matriz de coordenadas global está intacta en este punto.
    glPushMatrix();                 //Empieza el nodo raíz.
        glTranslatef(tx, ty, 0);    //Transformaciones al nodo raíz e hijos.
        glRotatef(rx, 1, 0, 0);
        glRotatef(ry, 0, 1, 0);
        glScalef(es, es, es);
        
        piso();                     //Se dibuja el piso.

        glPushMatrix();             //Empieza el nodo de la casa.
            glTranslatef(-2, 1, 0); //Transformaciones a toda la casa e hijos.
            glScalef(2, 1, 1);
            dibujar_casa();         //Se dibuja la casa.
        glPopMatrix();              //Termina el nodo de la casa.

        glPushMatrix();             //Empieza el nodo del árbol
            glTranslatef(3, 0, 0);  //Transformaciones a todo el árbol e hijos.
            dibujar_arbol();        //Se dibuja el árbol.
        glPopMatrix();              //Termina el nodo del árbol.

    glPopMatrix();
    //La matriz de coordenadas global está intacta en este punto.

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
        gluLookAt(0, 0, 15, 0, 0, 0, 0, 1, 0);
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
    glutCreateWindow("Ejemplo de modelado jerarquico");
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