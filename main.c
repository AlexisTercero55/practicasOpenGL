/*  Alexis tercero: https://github.com/AlexisTercero55
                    alexistercero55@gmail.com
    build command: gcc plantilla.c -lfreeglut -lopengl32 -lglu32
    build task@\.vscode\task.json : ctrl + shift + b

    Programa que genera graficos 2D.
*/
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/*PROTOTIPOS*/
//Plantilla
void configVentanaGlut(void);
void dibujar(void);
void teclado (unsigned char key, int x, int y);

void d_puntos(void);
void d_lineas(void);
void d_tiangulos(void);
void graficador2D(float (*f) (float),float a, float b, int n, int ord);

int dibujar_con = 0;

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
    glutCreateWindow("Alexis Tercero 9/1/21 Practica : 1");
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

void d_lineas(void)
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
    /*ponga aqui sus primitivas OpenGL*/
        glColor3f(1,0,0); glVertex2f(-.5, 0);
        glColor3f(0,1,0); glVertex2f(.5, 0);
        glColor3f(0,0,1);glVertex2f(0, .5);
    glEnd();
}

void dibujar(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (dibujar_con)
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
    glFinish();//que se muestre ya
    //glutSwapBuffers(); //cuando se habilitan los buffers
}

void teclado (unsigned char key, int x, int y) 
{
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
}