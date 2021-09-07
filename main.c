/*  Alexis Tercero: https://github.com/AlexisTercero55
                    alexistercero55@gmail.com
    build command: gcc main.c -lfreeglut -lopengl32 -lglu32
    build task@\.vscode\task.json : ctrl + shift + b
    --------------------------------------------------------------------
            PERCEPCIÓN DE PROFUNDIDAD EN UNA IMAGEN PLANA
    IMPLEMENTACIÓN MEDIANTE CÁMARAS, LUCES Y BUFFERS EN GLUT/FREEGLUT
    --------------------------------------------------------------------
    Programa que renderiza una el modelo 3D de una 'tetera'
    predefinida en OpenGL por glutSolidTeapot();.
    con dos perspectivas diferentes: 
        Ortogonal y 
        perspectiva,
    utilice 'p' para cambiar de perspectiva.

    SE CONFIGURARON:
        Buffers de Color, ILUMINACION y de profundidad.
        Se habilita: Uso de buffer doble.
        Intercambio de buffers de dibujo.
        Iluminacion: Luz numero 1.
        Redimencionamiento: Relacion pantalla-render.

        PERSPECTIVAS: ORTOGONAL Y EN PERSPECTIVA
*/
#include <stdlib.h>
#include <GL/glut.h>    //-lfreeglut
#include <GL/glu.h>     //-lglu32
#include <GL/gl.h>      //-lopengl32

/*PROTOTIPOS*/
//Plantilla
void configVentanaGlut(void);
void dibujar(void);
void teclado (unsigned char key, int x, int y);
void camara(void);
void config_OGL();
void redimensionar (int ancho, int alto);

void graficador2D(float (*f) (float),float a, float b, int n, int ord);
/* void d_puntos(void);
void d_lineas(void);
void d_tiangulos(void); */

//INDICADORES DE ESTADO
GLboolean proy_orto = GL_FALSE;
// int dibujar_con = 0;

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    configVentanaGlut();
    config_OGL();
    glutMainLoop();
    return 0;
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
   //glClearColor(.2,.2,1,1); 
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
        gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
    }

    glMatrixMode(GL_MODELVIEW);//SE REGISTRAN LOS NUEVOS CAMBIOS
    glLoadIdentity();
}

void configVentanaGlut(void)
{
    //configuracion de pantalla
    /*SE RESERVA MEMORIA PARA LOS BUFFERS DE COLOR, DOBLE Y DE PROFUNDIDAD*/
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Alexis Tercero 8/31/21 Practica 2 : PERCEPCION DE PROFUNDIDAD & GRAFICOS 3D");
    //registro y ejecuccion de procesos
    glutDisplayFunc(dibujar);//LO QUE SE RENDERIZA
    glutKeyboardFunc(teclado);//INTERACTIVIDAD : REAL-TIME 3D
    glutReshapeFunc(redimensionar);//USER EXPERIENCE
}

void dibujar(void) 
{
    //LIMPIAR BUFFERS DE COLOR Y DE PROFUNDIDAD.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(1); //pone una tetera
    glutSwapBuffers(); //hacer cambio de buffers (HABILITAR BUFFERDOBLE POR FREEGLUT)
    /* switch (dibujar_con)
    {
        case 0:
            d_puntos();
            break;
        case 1:
            d_lineas();
            break;
        case 2:
            d_tiangulos();
            break;
        default:
            break;
    }
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
        /* case '+':
            dibujar_con++; //siguiente dibujo
            break;
        case '-':
            dibujar_con--; //dibujo anterior
            break;
        case '0':
            dibujar_con = 0;
            break;
        case '1':
            dibujar_con = 1;
            break;
        case '2':
            dibujar_con = 2;
            break; */
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