/*  Alexis tercero: https://github.com/AlexisTercero55
                    alexistercero55@gmail.com
    build command: gcc plantillaNotas.c -lfreeglut -lopengl32 -lglu32
    build task@\.vscode\task.json : ctrl + shift + b

    Aqui se da una explicacion que trata (en la medida de lo posible)
    de explicar el ¿Por qué? y ¿Cómo? funciona el codigo. Help: notas.txt
*/
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

void dibujar(void);
void teclado(unsigned char key, int x, int y);
void dibujar_triangulo(void);

int main(int argc, char** argv)
{
  //iniciar FreeGLUT : gestor de ventanas, (entorno de OpenGL)
  glutInit(&argc, argv);
  //especificar el tamaño de ventana (resolucion) en pixeles
  glutInitWindowSize(800, 600);
  //definir posicion inicial de pantalla
  glutInitWindowPosition(0,0);
  //crear ventana y darle un titulo
  glutCreateWindow("Practica 1: Alexis Tercero");

  /*Se requiere especificar a la ventana que es lo que va a dibujar
    mediante una funcion que procesa las primitivas, en este caso se trata de
    la funcion: void dibujar(void)*/

  //indicar a GLUT los procesos que debe realizar
  glutDisplayFunc(dibujar_triangulo);

  /*Configurar FreeGlut para recibir eventos de teclado*/
  glutKeyboardFunc(teclado);
  
  /*      El problema de las ventanas (game loop)
    Se necesita especificar que una ventana se mantenga abierta
    y empiece a procesar los eventos de dibujo e interaccion con el usuario
    mediante la funcion: glutMainLoop()*/
  glutMainLoop();

  return 0;
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
    glFinish();
}

void teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: //scape in ASCII
            exit(0);//no erros
            break;
    }
}

void dibujar_triangulo(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        glVertex2f(-0.5, -0.5);
        glColor3f(0, 1, 0);
        glVertex2f(0.5, -0.5);
        glColor3f(0, 0, 1);
        glVertex2f(0.0, 0.5);
      glEnd();
    glutSwapBuffers();
}