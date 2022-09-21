#include<GL/glut.h>

#include<GL/freeglut.h>

#include<stdlib.h>

#include<stdio.h>


int valor = 0;

void init()


{

    /* Define a cor de fundo (preto) */

    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* Inicializa as Matrizes do OpenGL */

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity(); 

    gluPerspective(60.0,1.0,1.0,20.0);

    glMatrixMode( GL_MODELVIEW );


}


void wireBox(float x, float y, float z){

glPushMatrix();

glTranslatef(x/2, 0, 0);

glScalef(x, y, z);

glutWireCube(1);

glPopMatrix();

}



void keySpecial(int key, int x, int y) {

    switch(key){

        case GLUT_KEY_DOWN:

            valor = (valor - 5) % 360;


            break;

        case GLUT_KEY_UP:

            valor = (valor + 5) % 360;

            break;

    }


     glutPostRedisplay(); //diz pro loop que teve atualização de algo

}



void display(void){

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    glColor3f(1,0,0);


    glTranslatef( 0.0, 0.0, -8.0);

    wireBox( 2.0, 0.4, 1.0 ); //desenha o cubo achatado reto(braço)


    /* origem posicionada no cotovelo */

    glTranslatef( 2.0, 0.0, 0.0 );

    glPushMatrix();

    glRotatef( (GLfloat) valor, 0.0, 0.0, 1.0 ); //desenha conforme valor lido na tecla apertada

    glRotatef( 45.0 , 0.0, 0.0, 1.0 );

    wireBox( 2.0, 0.4, 1.0 ); //desenha o cubo acima

    glRotatef( -45.0 , 0.0, 0.0, 1.0 );

    wireBox( 2.0, 0.4, 1.0 ); //desenha o cubo abaixo

    glPopMatrix();


    /* origem volta para o sistema de coordenadas original */

    glPopMatrix();

    glutSwapBuffers();


}


void myReshape(int winWidth, int winHeight) // reshape window

{

    int tam = winWidth < winHeight ? winWidth : winHeight;

    glViewport(0, 0, tam, tam); // reset the viewport


}



int main(int argc, char** argv)

{

    glutInit(&argc, argv); //inicializa

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //mostra o display como

    glutInitWindowSize(350, 350); //tamanho da janela

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Hello world!");

    init();

    glutDisplayFunc(display);

    glutReshapeFunc(myReshape);

    glutSpecialFunc(keySpecial);

    glutMainLoop();

    return 0;


}