#include<GL/glut.h>
#include<GL/freeglut.h>
#include<stdlib.h>
#include<stdio.h>


GLfloat distance = 5;
GLfloat azimuth = 0;
GLfloat incidence = 0;
GLfloat twist = 0;
GLfloat velocidadeGeral = 1;


void polarView() {
    glTranslatef(0.0, 0.0, -distance);
    glRotatef(-twist, 0.0, 0.0, 1.0);
    glRotatef(-incidence, 1.0, 0.0, 0.0);
    glRotatef(-azimuth, 0.0, 0.0, 1.0);
}

void display () {
    const double a = glutGet(GLUT_ELAPSED_TIME) / 10;
	GLfloat lightPosition[4] = {0, 0, 0, 1};
	GLfloat yellow[4] = {1, 1, 0, 1};
    GLfloat black[4] = {0, 0, 0, 1};


    float tamSol = 0.50;
    float tamTerra = 0.15;
    float tamOutro = 0.12;



    float velTerra = 1.40 * velocidadeGeral;
    float velOutro = 0.75 * velocidadeGeral;



    float distOrbitaTerra = 1.40;
    float distOrbitaOutro = 1.70;



    float tamOrbitas = 0.005;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        polarView();

        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);


        glMaterialfv(GL_FRONT, GL_EMISSION, yellow);


        glPushMatrix();
            glRotated(a, 0, 0, 1);
            glColor3d(1, 1, 0);
            glutSolidSphere(tamSol, 20, 20);
        glPopMatrix();

        glMaterialfv(GL_FRONT, GL_EMISSION, black);




        glPushMatrix();
            glRotated(velTerra * a, 0, 0, 1);
            glTranslated(distOrbitaTerra, 0, 0);
            glColor3d(0.196078, 0.6, 0.8);
            glRotated(5 * -a, 0, 0, 1);
            glutSolidSphere(tamTerra, 20, 20);


            glPushMatrix();
                glRotated(a, 0, 0, 1);
                glTranslated(0.2, 0, 0);
                glColor3d(0.74902, 0.847059, 0.847059);
                glRotated(a, 0, 0, 1);
                glutSolidSphere(0.02, 20, 20);
            glPopMatrix();
        glPopMatrix();


        glPushMatrix();
            glRotated(velOutro * a, 0, 0, 1);
            glTranslated(distOrbitaOutro, 0, 0);
            glColor3d(1.0, 0.25, 0.0);
            glRotated(5 * -a, 0, 0, 1);
            glutSolidSphere(tamOutro, 20, 20);
        glPopMatrix();




        glDisable(GL_LIGHTING);


            glPushMatrix();
                glColor3d(1, 1, 1);
                glutSolidTorus(tamOrbitas, distOrbitaTerra, 50, 50);
            glPopMatrix();


            glPushMatrix();
                glColor3d(1, 1, 1);
                glutSolidTorus(tamOrbitas, distOrbitaOutro, 50, 50);
            glPopMatrix();



        glEnable(GL_LIGHTING);
	glPopMatrix();

	glutSwapBuffers();
}

void myReshape(int winWidth, int winHeight) {
	int t = winWidth < winHeight ? winWidth : winHeight;

    glViewport (0, 0, t, t);
}

void mouseWheel(int button, int dir, int x, int y) {
    if (dir > 0) {
        distance += 2;
    } else {
        distance -= 2;
    }
}

void myKeyboard (unsigned char c, int x, int y){
	switch (c){
		case 27: // ESC em ASCII
			exit(0);
			break;
        case 'w':
            incidence += 2;
            break;
        case 's':
            incidence -= 2;
            break;
        case 'z':
            distance++;
            break;
        case 'x':
            distance--;
            break;
        case 'd':
            azimuth += 5;
            break;
        case 'a':
            azimuth -= 5;
            break;
        case 'e':
            twist += 5;
            break;
        case 'q':
            twist -= 5;
            break;
        case 'f':
            if (velocidadeGeral == 1) {
                velocidadeGeral = 0.2;
            } else {
                velocidadeGeral = 1;
            }

            break;
	}
}

void wireBox(float x, float y, float z) {
	glPushMatrix();
		glTranslatef(x/2, 0, 0);
		glutWireCube(1);
		glScalef(x, y, z);
	glPopMatrix();
}

void myMouse (int b, int s, int x, int y) {
	switch (b){
		case GLUT_LEFT_BUTTON:
			if(s == GLUT_DOWN)
				printf("L Buttom down(%d, %d)\n", x, y);
			else if (s == GLUT_UP)
				printf("L Buttom up (%d, %d)\n", x, y);
			break;
	}
}

void keySpecial(int key, int x, int y) {
	switch(key){
        case GLUT_KEY_LEFT:
        printf("Left pressed\n");
        break;
        case GLUT_KEY_UP:
        printf("Up pressed\n");
        break;
        case GLUT_KEY_RIGHT:
        printf("Right pressed\n");
        break;
        case GLUT_KEY_DOWN:
        printf("Down pressed\n");
        break;
            if(glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
                printf("SHIFT pressed.\n");
            }
        if(glutGetModifiers() == GLUT_ACTIVE_ALT) {
                printf("ALT pressed.\n");
            }
        if(glutGetModifiers() == GLUT_ACTIVE_CTRL) {
            printf("CTRL pressed.\n");
        }
    }
}

void idle() {
	glutPostRedisplay();
}

void init() {

	glClearColor(0.0, 0.0, 0.0, 0.0);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// glOrtho(-1.0, 1.0, -1.0 , 1.0, -1.0, 1.0);

	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

int main(int argc, char** argv) {
    printf("Controles de camera:\n");
    printf("Zoom: Z / X ou MouseWheel Up / Down\n");
    printf("Rotacao vertical: W / S\n");
    printf("Rotacao: A / D\n");
    printf("Inclinacao: Q / E\n");
    printf("Reduzir velocidade: F\n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello world!");
	init();
	glutDisplayFunc(display);
	//glutDisplayFunc(myReshape);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(keySpecial);
	glutMouseFunc(myMouse);
	glutMouseWheelFunc(mouseWheel);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}