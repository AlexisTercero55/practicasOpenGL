/*  Alexis Tercero: https://github.com/AlexisTercero55
                    alexistercero55@gmail.com
    build command: gcc plantilla.c -lfreeglut -lopengl32 -lglu32
    build task@\.vscode\task.json : ctrl + shift + b

    CONFIGURACION BASICA DE UNA APLICACION DE OpenGL y FreeGlut
    Este programa solo despliega una ventana negra.
*/
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

/*PROTOTIPOS*/
//Plantilla
void dibujar(void);
void teclado (unsigned char key, int x, int y);
void configVentanaGlut(void);

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    configVentanaGlut();
    //registro y ejecuccion de procesos
    glutDisplayFunc(dibujar);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}

void configVentanaGlut(void)
{
    //configuracion de pantalla
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Plantilla de OpenGL: Alexis Tercero");
}

void dibujar(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*ponga aqui sus primitivas OpenGL*/
    /*  ENTORNO DE DIBUJO BASICO
    glBegin(GLenum mode); //DEFINE UN DIBUJO
        //ponga aqui sus primitivas OpenGL
        //No hay límite para el número de vértices que se pueden definir entre glBegin y glEnd.
    glEnd();// TERMINA EL DIBUJO
    */
    /*  OTRAS IMPLEMENTACIONES
    switch (dibujar_con) //dibujar_con : VARIABLE GLOBAL
    {
        case 0:
            d_puntos();//DIBUJOS INDEPENDIENTES
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
    */
    //glutSwapBuffers();//cuando se habilitan los buffers
    glFinish();
}

void teclado (unsigned char key, int x, int y) 
{
    switch (key) 
    {
        case 27: //scape in ASCII
            exit(0);
            break;
    }
    //INDICAR AL OS QUE DIBUJE YA
    glutPostRedisplay(); //optimizacion de recursos
    
    /* OTRA IMPLEMENTACION DE INTERACCION CON EL USUARIO
    switch (key) 
    {
        case 27: //scape in ASCII
            exit(0);
            break;
        case '+':
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
            break;
        default:
            break;
    }
    //INDICAR AL OS QUE DIBUJE YA
    glutPostRedisplay(); //optimizacion de recursos
    */
}