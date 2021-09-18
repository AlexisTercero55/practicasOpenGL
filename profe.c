/*  9/2/21
    CODIGO PUBLICADO POR EL PROFESOR Vargas Castro Daniel
    PROGRAMA QUE DIBUJA 10 PRIMITIVAS GEOMETRICAS,
    CON DIFERENTES PERSPECTIVAS Y MODOS DE DIBUJO.
*/
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846
#define PLANO 0
#define CUBO 1
#define ESFERA 2
#define CONO 3
#define CILINDRO 4
#define TOROIDE 5
#define DODECAEDRO 6
#define ICOSAEDRO 7
#define TETRAEDRO 8
#define TETERA 9
#define TAM 2.0
#define RAD 1.0

GLboolean proy_orto = GL_FALSE;
GLboolean wireframe = GL_FALSE;
GLint figura = PLANO;

void plano_xz(GLfloat l) {
    glBegin(GL_QUADS);
        glVertex3f(-l/2, 0, l/2);
        glVertex3f(l/2, 0, l/2);
        glVertex3f(l/2, 0, -l/2);
        glVertex3f(-l/2, 0, -l/2);
    glEnd();
}

void plano_xz_wire(GLfloat l) {
    glBegin(GL_LINE_LOOP);
        glVertex3f(-l/2, 0, l/2);
        glVertex3f(l/2, 0, l/2);
        glVertex3f(l/2, 0, -l/2);
        glVertex3f(-l/2, 0, -l/2);
    glEnd();
}

void cubo (GLfloat l) {
    glBegin(GL_QUAD_STRIP);
        //Cara frontal
        glVertex3f(-l/2, l/2, l/2);
        glVertex3f(-l/2, -l/2, l/2);
        glVertex3f(l/2, l/2, l/2);
        glVertex3f(l/2, -l/2, l/2);
        //Cara derecha
        glVertex3f(l/2, l/2, -l/2);
        glVertex3f(l/2, -l/2, -l/2);
        //Cara trasera
        glVertex3f(-l/2, l/2, -l/2);
        glVertex3f(-l/2, -l/2, -l/2);
        //Cara izquierda
        glVertex3f(-l/2, l/2, l/2);
        glVertex3f(-l/2, -l/2, l/2);
    glEnd();
    glBegin(GL_QUADS);
        //Cara superior
        glVertex3f(-l/2, l/2, l/2);
        glVertex3f(l/2, l/2, l/2);
        glVertex3f(l/2, l/2, -l/2);
        glVertex3f(-l/2, l/2, -l/2);
        //Cara inferior
        glVertex3f(-l/2, -l/2, l/2);
        glVertex3f(l/2, -l/2, l/2);
        glVertex3f(l/2, -l/2, -l/2);
        glVertex3f(-l/2, -l/2, -l/2);
    glEnd();
}

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

void cilindro_wireframe(GLfloat r, GLfloat h, GLint n) {
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
    glBegin(GL_LINES);
        for (i = 0; i < n; i++) {
            glVertex3f(verts[i].x, verts[i].y, h/2);
            glVertex3f(verts[i].x, verts[i].y, -h/2);
        }
    glEnd();
    
    //Cara trasera.
    glBegin(GL_LINE_LOOP);
        for (i = 0; i < n; i++) {
            glVertex3f(verts[i].x, verts[i].y, -h/2);
            glVertex3f(verts[i].x, verts[i].y, -h/2);
        }
    glEnd();

    //Cara frontal.
    glBegin(GL_LINE_LOOP);
        for (i = 0; i < n; i++) {
            glVertex3f(verts[i].x, verts[i].y, h/2);
            glVertex3f(verts[i].x, verts[i].y, h/2);
        }
    glEnd();
    glDisable(GL_NORMALIZE);
    
    free(verts);
}

void dibujar(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (figura) {
        case PLANO: 
            wireframe ? plano_xz_wire(TAM) : plano_xz(TAM);  break;
        case CUBO: 
            wireframe ? glutWireCube(TAM) : glutSolidCube(TAM);  break;
        case ESFERA: 
            wireframe ? glutWireSphere(RAD, 20, 30) : glutSolidSphere(RAD, 20, 30);  break;
        case CONO: 
            wireframe ? glutWireCone(RAD, TAM, 20, 1) : glutSolidCone(RAD, TAM, 20, 1); break;
        case CILINDRO: 
            wireframe ? cilindro_wireframe(RAD, TAM, 20) : cilindro_solido(RAD, TAM, 20); break;
        case TOROIDE: 
            wireframe ? glutWireTorus(RAD, TAM, 10, 20) :  glutSolidTorus(RAD, TAM, 10, 20); break;
        case DODECAEDRO: 
            wireframe ? glutWireDodecahedron() : glutSolidDodecahedron(); break;
        case ICOSAEDRO: 
            wireframe ? glutWireIcosahedron() : glutSolidIcosahedron(); break;
        case TETRAEDRO: 
            wireframe ? glutWireTetrahedron() : glutSolidTetrahedron(); break;
        case TETERA: 
            wireframe ? glutWireTeapot(TAM) : glutSolidTeapot(TAM); break;
    }
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
        gluPerspective(45, ancho/alto, 0.1, 10000);
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
        case 'W': case 'w':
            wireframe = !wireframe;
            break;
        case '0':
            figura = PLANO;
            break;
        case '1':
            figura = CUBO;
            break;
        case '2':
            figura = ESFERA;
            break;
        case '3':
            figura = CONO;
            break;
        case '4':
            figura = CILINDRO;
            break;
        case '5':
            figura = TOROIDE;
            break;
        case '6':
            figura = DODECAEDRO;
            break;
        case '7':
            figura = ICOSAEDRO;
            break;
        case '8':
            figura = TETRAEDRO;
            break;
        case '9':
            figura = TETERA;
            break;
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