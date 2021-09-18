/*  Alexis Tercero: https://github.com/AlexisTercero55
                    alexistercero55@gmail.com
    build command: gcc clase.c -lfreeglut -lopengl32 -lglu32
    build task@\.vscode\task.json : ctrl + shift + b
    CLASE 9/2/21 Graficación por Computadora con OpenGL 
    ---------------------------------------------------------------------------------
                                OBJETOS 3D
                GENERACIÓN DE MALLAS POLIGONALES CON OPENGL
    ---------------------------------------------------------------------------------
    
    PROGRAMA QUE DIBUJA 10 PRIMITIVAS GEOMETRICAS,
    CON DIFERENTES PERSPECTIVAS Y MODOS DE DIBUJO.

    PRESIONE LOS NUMEROS DEL '0' AL '9' PARA CAMBIAR DE PRIMITIVA GEONETRICA.

    PRESIONE 'p' para cambiar de perspectiva:
        Ortogonal
        perspectiva
    
    PRESIONES 'W' PARA CAMBIAR EL MODO DE DIBUJO.

    SE CONFIGURARÓN:
        Buffers de Color, ILUMINACION y de profundidad.
        Se habilita: Uso de buffer doble.
        Intercambio de buffers de dibujo.
        Iluminacion: Luz numero 0.
        Redimencionamiento: Relacion pantalla-render.
        PERSPECTIVAS: ORTOGONAL Y EN PERSPECTIVA
    
    Pendientes:
        ** revisar iluminacion de cilindroSolidWireframeGlut y su
           consecuencia en el plano plano_xz
*/
#include <stdlib.h>
#include <GL/glut.h>    //-lfreeglut
#include <GL/glu.h>     //-lglu32
#include <GL/gl.h>      //-lopengl32

//MACROS DE APP **CAMBIAR A C++ (ENUM O CONST)
#define PLANO 0
#define CUBO 1
#define ESFERA 2
#define CONO 3
#define CILINDRO 4
#define TORO 5
#define TAM 2.0
#define RAD 1.0

/*PROTOTIPOS*/
//Plantilla
void configVentanaGlut(void);
void dibujar(void);
void teclado (unsigned char key, int x, int y);
void camara(void);
void config_OGL();
void redimensionar (int ancho, int alto);

void cilindroSolidWireframeGlut(GLdouble base, GLdouble top, GLdouble height,
 	                            GLint slices, GLint stacks);
void toroSolidWireframeGlut(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings);
void conoSolidWireframeGlut(GLdouble base, GLdouble height, GLint slices, GLint stacks);
void esferaSolidWireframeGlut(GLdouble radius, GLint slices, GLint stacks);
void cuboSolidWireframeGlut(GLdouble size);
void plano_xz(GLfloat L);
void plano_xz_WIRE(GLfloat L);
void graficador2D(float (*f) (float),float a, float b, int n, int ord);
/* void d_puntos(void);
void d_lineas(void);
void d_tiangulos(void); */

//INDICADORES DE ESTADO
GLboolean WIREFRAME_STATE = GL_FALSE;
GLboolean proy_orto = GL_FALSE;
int figura = PLANO; //**CAMBIAR figura -> dibujo

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    configVentanaGlut();
    config_OGL();
    glutMainLoop();
    return 0;
}

void cilindroSolidWireframeGlut(GLdouble base, GLdouble top, GLdouble height,
 	                            GLint slices, GLint stacks)
{
    //paso 1
    GLUquadricObj *quad = gluNewQuadric();
    //paso 2
    WIREFRAME_STATE ? gluQuadricDrawStyle(quad,GLU_LINE) : 
                      gluQuadricDrawStyle(quad,GLU_FILL);
    //paso 3
    gluCylinder(quad, base, top, height, slices, stacks);
}

void toroSolidWireframeGlut(GLdouble innerRadius, GLdouble outerRadius,
                            GLint nsides, GLint rings)
{
    WIREFRAME_STATE ? glutWireTorus(innerRadius, outerRadius, nsides, rings) :
                      glutSolidTorus(innerRadius, outerRadius, nsides, rings);
}

void conoSolidWireframeGlut(GLdouble base, GLdouble height, GLint slices, GLint stacks)
{
    WIREFRAME_STATE ?  glutWireCone( base,  height,  slices,  stacks) :
                       glutSolidCone( base,  height,  slices,  stacks);
}

void esferaSolidWireframeGlut(GLdouble radius, GLint slices, GLint stacks)
{
    WIREFRAME_STATE ?  glutWireSphere( radius,  slices,  stacks) : 
                       glutSolidSphere( radius,  slices,  stacks);
}

void cuboSolidWireframeGlut(GLdouble size)
{
    WIREFRAME_STATE ? glutWireCube(size) : glutSolidCube(size);
}

void plano_xz_WIRE(GLfloat L) //L : longitud de cada lado
{
    glBegin(GL_LINE_LOOP);
        glVertex3f(-L/2, 0, L/2);
        glVertex3f(L/2, 0, L/2);
        glVertex3f(L/2, 0, -L/2);
        glVertex3f(-L/2, 0, -L/2);
    glEnd();
}

void plano_xz(GLfloat L) //L : longitud de cada lado
{
    glBegin(GL_QUADS);
        glVertex3f(-L/2, 0, L/2);
        glVertex3f(L/2, 0, L/2);
        glVertex3f(L/2, 0, -L/2);
        glVertex3f(-L/2, 0, -L/2);
    glEnd();
}

void redimensionar (int ancho, int alto) 
{
    if (alto == 0) alto = 1;
    int lado = ancho < alto ? ancho : alto;
    glViewport((ancho - lado) / 2, (alto - lado) / 2, lado, lado);
    camara();
}

void config_OGL()
{
   camara();
   //habilitar uso de buffers
   glEnable(GL_LIGHTING);//ILUMINACION EN GENERAL
   glEnable(GL_LIGHT0);//LUS ESPECIFICA
   glEnable(GL_DEPTH_TEST);//ACTIVA EL USO DELBUFFER DE PROFUNDIDAD.
   glClearColor(.2,.2,.2,1); 
}

void camara(void)
{
    /*FUNCION QUE CONFIGURA LA PERSPECTIVA DE LA ESCENA
      Y EL VOLUMEN DE RECORTE DE RENDERIZADO*/
    float ancho = GLUT_WINDOW_WIDTH;
    float alto = GLUT_WINDOW_HEIGHT;
    glMatrixMode(GL_PROJECTION);//indica CAMBIOS EN LA MATIZ DE PROYECCION
    glLoadIdentity();

    //SE INDICA EL TIPO DE PROYECCION
    if (proy_orto){ //ORTOGRAFICA
        glOrtho(-5, 5, -5, 5, -5, 5);
    }
    else{ //EN PERSPECTIVA
        gluPerspective(45, ancho/alto, 0.1, 1000);
        gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
    }

    glMatrixMode(GL_MODELVIEW);//SE REGISTRAN LOS NUEVOS CAMBIOS
    glLoadIdentity();// LIMPIAR EL RESULTADOS DE LA ESCENA
}

void configVentanaGlut(void)
{
    //configuracion de pantalla
    /*SE RESERVA MEMORIA PARA LOS BUFFERS DE COLOR, DOBLE Y DE PROFUNDIDAD*/
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Alexis Tercero 9/2/21 Practica 3 : GRAFICOS 3D & PRIMITIVAS GEOMETRICAS");
    //registro y ejecuccion de procesos
    glutDisplayFunc(dibujar);//LO QUE SE RENDERIZA
    glutKeyboardFunc(teclado);//INTERACTIVIDAD : REAL-TIME 3D
    glutReshapeFunc(redimensionar);//USER EXPERIENCE
}

void dibujar(void) 
{
    //LIMPIAR BUFFERS DE COLOR Y DE PROFUNDIDAD.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (figura)
    {
        case PLANO:
            WIREFRAME_STATE ? plano_xz_WIRE(10) : plano_xz(10);
            break;
        case CUBO:
            cuboSolidWireframeGlut(3);
            break;
        case ESFERA:
            esferaSolidWireframeGlut( 2,  20,  20);//radio, **
            break;
        case CONO:
            conoSolidWireframeGlut(1, 2, 20, 1);//radio, **
            break;
        case CILINDRO:
            cilindroSolidWireframeGlut(2, 1, 3, 4, 1);
            break;
        case TORO:
            toroSolidWireframeGlut(RAD, TAM, 10, 20);
            break;
        default:
            break;
    }
    glutSwapBuffers(); //hacer cambio de buffers (HABILITAR BUFFERDOBLE POR FREEGLUT)

    /* 
    glutSolidTeapot(1); //pone una tetera
    
    glFinish();//que se muestre ya */
}

void teclado (unsigned char key, int x, int y) 
{
    switch (key) 
    {
        case 27: //scape in ASCII
            exit(0);
            break;
        case 'p': case 'P'://CAMBIAR ENTRE PERSPECTIVAS DE LA ESCENA
            proy_orto = !proy_orto;
            camara();
            break;
        case 'w': case 'W'://CAMBIAR ENTRE MODO SOLIDO Y WIREFRAME
            WIREFRAME_STATE = !WIREFRAME_STATE;
            break;
        //confi para dibujar objetos 3D
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
            figura = TORO;
            break;
        case '+':
            figura++; //siguiente dibujo
            break;
        case '-':
            figura--; //dibujo anterior
            break;
        default:
            break;
    }
    //INDICAR AL O.S. QUE DIBUJE YA
    glutPostRedisplay(); //optimizacion de recursos
}

void graficador2D(float (*f) (float), float a, float b, int n, int orden)
{
    float x,y, paso = (b-a)/n; 

    if(orden)// X CRECIENTE
    {
        x = a;
        for(int i=0; i<n; ++i)
        {
            y = f(x);
            glVertex2f(x, y);
            x += paso;
        }
    } 
    else// X DECRECIENTE
    {
        x = b;
        for(int i=0; i<n; ++i)
        {
            y = f(x);
            glVertex2f(x, y);
            x -= paso;
        }
    }
        
}

//Entornos basicos de dibujo-
/* void d_lineas(void)
{
    glColor3f(1,1,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-.5, 0);
        glVertex2f(.5, 0);
        glVertex2f(0, .5);
    glEnd();
}

void d_puntos(void)
{
    //glPointSize(5);
    glColor3f(0,1,0);

    glBegin(GL_POINTS);
        glVertex2f(-.5, 0);
        glVertex2f(.5, 0);
        glVertex2f(0, .5);
    glEnd();
}

void d_tiangulos(void)
{
    glBegin(GL_TRIANGLES);//Usar CCW
    //ponga aqui sus primitivas OpenGL
        glColor3f(1,0,0); glVertex2f(-.5, 0);
        glColor3f(0,1,0); glVertex2f(.5, 0);
        glColor3f(0,0,1);glVertex2f(0, .5);
    glEnd();
}
 */