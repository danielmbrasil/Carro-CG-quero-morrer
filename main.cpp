#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#define SENS_ROT 5.0
#define SENS_OBS 10.0
#define SENS_TRANSL 10.0

GLint b = 300;
float counter = 600.0;

GLfloat distance = 50;
GLfloat azimuth = 0;
GLfloat incidence = 0;
GLfloat twist = 0;
GLfloat angle, fAspect;

GLfloat rotX, rotY, rotX_ini, rotY_ini;

GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;

GLfloat mov = 20.f;

int x_ini, y_ini, mouse_button;

void polarView() {
	glTranslatef(0.0, 0.0, -distance);
	glRotatef(-twist, 0.0, 0.0, 1.0);
	glRotatef(-incidence, 1.0, 0.0, 0.0);
	glRotatef(-azimuth, 0.0, 0.0, 1.0);
}

void DefineIluminacao() {
	GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};
	GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0}; // "cor"
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"
	GLfloat posicaoLuz[4] = {20.0, 150.0, 50.0, 1.0};

	GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
	GLint especMaterial = 60;

	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

void PosicionaObservador() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DefineIluminacao();
	glTranslatef(-obsX, -obsY, -obsZ);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
}

void EspecificaParametrosVisualizacao() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, fAspect, 0.5, 500);
	PosicionaObservador();
}

void GerenciaMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		mouse_button = button;
	}

	else mouse_button = -1;
}

void GerenciaMovim(int x, int y) {
	if (mouse_button == GLUT_LEFT_BUTTON) {
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		rotY = rotY_ini - deltax / SENS_ROT;
		rotX = rotX_ini - deltay / SENS_ROT;
	} else if (mouse_button == GLUT_RIGHT_BUTTON) {
		int deltaz = y_ini - y;
		obsZ = obsZ_ini + deltaz / SENS_OBS;
	} else if (mouse_button == GLUT_MIDDLE_BUTTON) {
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		obsX = obsX_ini + deltax / SENS_TRANSL;
		obsY = obsY_ini - deltay / SENS_TRANSL;
	}

	PosicionaObservador();
	glutPostRedisplay();
}

void Reshape(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	EspecificaParametrosVisualizacao();
}

void display() {
	/* Limpa todos os pixels da tela */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DefineIluminacao();

	glPushMatrix(); // ground
		glTranslatef(0, -510, 0);
		glColor3d(0, 0.5, 0);
		glutSolidCube(1000);
	glPopMatrix(); // end of ground

	glPushMatrix(); // sun
		glTranslatef(mov, 100, 100);
		glColor3d(1, 1, 0.2);
		glutSolidSphere(25, 100, 100);
	glPopMatrix(); // end of sun

	glPushMatrix(); // truck
		polarView();

		glColor3d(1, 0, 0); // back of truck
		glTranslatef(mov, 0, 0);
		glutSolidCube(15);

		glColor3d(1, 0, 0);
		glTranslatef(15, 0, 0);
		glutSolidCube(15); // end of back of truck

		glColor3d(1, 1, 1); // front of truck
		glTranslatef(13.2, -2, 0);
		glutSolidCube(10); // end of front of truck

		glTranslatef(0, -5, 5); // front right wheel
		glColor3d(0, 0, 0);
		glutSolidTorus(1, 1, 100, 100); // end of front right wheel

		glTranslatef(0, 0, -10); // front left wheel
		glColor3d(0, 0, 0);
		glutSolidTorus(1, 1, 100, 100); // end of front let wheel

		glTranslatef(-28, 0, 12); // brack right wheel 1
		glColor3d(0, 0, 0);
		glutSolidTorus(1, 1, 100, 100); // end brack right wheel 1

		glTranslatef(-4, 0, 0); // brack right wheel 2
		glColor3d(0, 0, 0);
		glutSolidTorus(1, 1, 100, 100); // end brack right wheel 2


		glTranslatef(4, 0, -14); // brack left wheel 1
		glColor3d(0, 0, 0);
		glutSolidTorus(1, 1, 100, 100); // end brack left wheel 1

		glTranslatef(-4, 0, 0); // brack left wheel 2
		glColor3d(0, 0, 0);
		glutSolidTorus(1, 1, 100, 100); // end brack left wheel 2
	glPopMatrix(); // end of truck

	glPushMatrix(); // pole
		glTranslatef(40, -10, 20);
		glRotatef(90, -1, 0, 0);
		glColor3d(0.5, 0.5, 0.5);
		glutSolidCylinder(2, 50, 4, 20);
	glPopMatrix(); // end of pole

	glPushMatrix(); // cloud
		glTranslatef(20, 150, 100);
		glColor3d(0.8, 0.8, 0.8);
		glutSolidSphere(7, 100, 100);
		glTranslatef(4.8, 0, 0);
		glutSolidSphere(7, 100, 100);
		glTranslatef(4.8, 0, 0);
		glutSolidSphere(7, 100, 100);
		glTranslatef(-4.8, 4.8, 0);
		glutSolidSphere(7, 100, 100);
	glPopMatrix(); // end of cloud

	glPushMatrix(); // cloud
		glTranslatef(0, 130, 100);
		glColor3d(0.8, 0.8, 0.8);
		glutSolidSphere(7, 100, 100);
		glTranslatef(4.8, 0, 0);
		glutSolidSphere(7, 100, 100);
		glTranslatef(4.8, 0, 0);
		glutSolidSphere(7, 100, 100);
		glTranslatef(-4.8, 4.8, 0);
		glutSolidSphere(7, 100, 100);
	glPopMatrix(); // end of cloud

	glPushMatrix(); // cloud
		glTranslatef(80, 140, 100);
		glColor3d(0.8, 0.8, 0.8);
		glutSolidSphere(7, 100, 100);
		glTranslatef(4.8, 0, 0);
		glutSolidSphere(7, 100, 100);
		glTranslatef(4.8, 0, 0);
		glutSolidSphere(7, 100, 100);
		glTranslatef(-4.8, 4.8, 0);
		glutSolidSphere(7, 100, 100);
	glPopMatrix(); // end of cloud

	glPushMatrix(); // cloud
		glTranslatef(20, 150, 0);
		glColor3d(0.8, 0.8, 0.8);
		glutSolidSphere(7, 100, 100);
		glTranslatef(4.8, 0, 0);
		glutSolidSphere(7, 100, 100);
		glTranslatef(4.8, 0, 0);
		glutSolidSphere(7, 100, 100);
		glTranslatef(-4.8, 4.8, 0);
		glutSolidSphere(7, 100, 100);
	glPopMatrix(); // end of cloud

	glutSwapBuffers();
}

void myReshape(int winWidth, int winHeight) {
	int tam = winWidth < winHeight ? winWidth : winHeight;
	glViewport(0, 0, tam, tam); // reset the viewport
}

/*comandos especiais do teclado*/
void keySpecial(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		mov -= 5.f;
		break;
	case GLUT_KEY_RIGHT:
		mov += 5.f;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void myKeyboard(unsigned char c, int x, int y) {
	switch (c) {
	case 27: // ESC em ASCII
		exit(0);
		break;
	case 'q':
		exit(0);
		break;
	}
}

// imprimir as coordenadas com o clique do mouse
void myMouse(int b, int s, int x, int y) {
	switch (b) {
	case GLUT_LEFT_BUTTON:
		printf("(%d, %d)\n", x, y);
	}
}

// função detecta movimento do mouse e salva coordenadas
void myMotion(int x, int y) {
	printf("Motion: (%d, %d)\n", x, y);
}

void init() {
	// background color
	glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	angle = 45;
	rotX = 0;
	rotY = 10;
	obsX = 20;
	obsY = 0;
	obsZ = 100;
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(5, 5);
	glutInitWindowSize(450, 450);
	glutCreateWindow("Trabalho CG");
	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(keySpecial);
	glutMouseFunc(GerenciaMouse);
	glutMotionFunc(GerenciaMovim);
	init();
	glutMainLoop();

	return 0;
}
