#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

GLint b = 300;
float counter = 600.0;

GLfloat distance = 50;
GLfloat azimuth = 0;
GLfloat incidence = 0;
GLfloat twist = 0;
GLfloat angle, fAspect;

GLfloat rotX, rotY, rotX_ini, rotY_ini;

GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;

int x_ini, y_ini, bot;

void polarView()
{
	glTranslatef(0.0, 0.0, -distance);
	glRotatef(-twist, 0.0, 0.0, 1.0);
	glRotatef(-incidence, 1.0, 0.0, 0.0);
	glRotatef(-azimuth, 0.0, 0.0, 1.0);
}

void DefineIluminacao(void)

{

	GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};

	GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0}; // "cor"

	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"

	GLfloat posicaoLuz[4] = {20.0, 150.0, 50.0, 1.0};

	// Capacidade de brilho do material

	GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};

	GLint especMaterial = 60;

	// Define a refletância do material

	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);

	// Define a concentração do brilho

	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);

	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

void PosicionaObservador(void)

{

	// Especifica sistema de coordenadas do modelo

	glMatrixMode(GL_MODELVIEW);

	// Inicializa sistema de coordenadas do modelo

	glLoadIdentity();

	DefineIluminacao();

	// Posiciona e orienta o observador

	glTranslatef(-obsX, -obsY, -obsZ);

	glRotatef(rotX, 1, 0, 0);

	glRotatef(rotY, 0, 1, 0);
}

// Função usada para especificar o volume de visualização

void EspecificaParametrosVisualizacao(void)

{

	// Especifica sistema de coordenadas de projeção

	glMatrixMode(GL_PROJECTION);

	// Inicializa sistema de coordenadas de projeção

	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)

	gluPerspective(angle, fAspect, 0.5, 500);

	PosicionaObservador();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)

void Teclado(unsigned char tecla, int x, int y)

{

	if (tecla == 27) // ESC ?

		exit(0);
}

// Função callback para tratar eventos de teclas especiais

void TeclasEspeciais(int tecla, int x, int y)

{

	switch (tecla)

	{

	case GLUT_KEY_HOME:
		if (angle >= 10)
			angle -= 5;

		break;

	case GLUT_KEY_END:
		if (angle <= 150)
			angle += 5;

		break;
	}

	EspecificaParametrosVisualizacao();

	glutPostRedisplay();
}

// Função callback para eventos de botões do mouse

void GerenciaMouse(int button, int state, int x, int y)

{

	if (state == GLUT_DOWN)

	{

		// Salva os parâmetros atuais

		x_ini = x;

		y_ini = y;

		obsX_ini = obsX;

		obsY_ini = obsY;

		obsZ_ini = obsZ;

		rotX_ini = rotX;

		rotY_ini = rotY;

		bot = button;
	}

	else
		bot = -1;
}

// Função callback para eventos de movimento do mouse

#define SENS_ROT 5.0

#define SENS_OBS 10.0

#define SENS_TRANSL 10.0

void GerenciaMovim(int x, int y)

{

	// Botão esquerdo ?

	if (bot == GLUT_LEFT_BUTTON)

	{

		// Calcula diferenças

		int deltax = x_ini - x;

		int deltay = y_ini - y;

		// E modifica ângulos

		rotY = rotY_ini - deltax / SENS_ROT;

		rotX = rotX_ini - deltay / SENS_ROT;
	}

	// Botão direito ?

	else if (bot == GLUT_RIGHT_BUTTON)

	{

		// Calcula diferença

		int deltaz = y_ini - y;

		// E modifica distância do observador

		obsZ = obsZ_ini + deltaz / SENS_OBS;
	}

	// Botão do meio ?

	else if (bot == GLUT_MIDDLE_BUTTON)

	{

		// Calcula diferenças

		int deltax = x_ini - x;

		int deltay = y_ini - y;

		// E modifica posições

		obsX = obsX_ini + deltax / SENS_TRANSL;

		obsY = obsY_ini - deltay / SENS_TRANSL;
	}

	PosicionaObservador();

	glutPostRedisplay();
}

// Função callback chamada quando o tamanho da janela é alterado

void Reshape(GLsizei w, GLsizei h)

{

	// Para previnir uma divisão por zero

	if (h == 0)
		h = 1;

	// Especifica as dimensões da viewport

	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto

	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// adicionar as formas a serem mostradas na cena
void display()
{
	const double a = glutGet(GLUT_ELAPSED_TIME) / 10;
	GLfloat yellow[4] = {1, 1, 0, 1};

	/* Limpa todos os pixels da tela */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DefineIluminacao();

	glPushMatrix(); // comeco do chao
		glTranslatef(0, -510, 0);
		glColor3d(0, 0.5, 0);
		glutSolidCube(1000);
	glPopMatrix(); // fim do chao

	glPushMatrix(); //  comeco do sol
		glTranslatef(20, 150, 100);
		glColor3d(1, 1, 0.2);
		glutSolidSphere(25, 100, 100);
	glPopMatrix(); // fim do sol

	glPushMatrix(); // comeco do carro
		polarView();

		glColor3d(0, 0.7, 0.88); // comeco da cor no meio
		glutSolidCylinder(4, 16, 100, 100); // comeco da cor no meio
		
		glTranslatef(0, -5, 0); // comeco da roda da frente
		glRotatef(90, 0, 1, 0);
		glColor3d(0, 0, 0);
		glutSolidTorus(1.5, 2, 100, 100); // fim da roda da frente
		
		glTranslatef(0, 5, 0); // comeco da ponta do carro
		glRotatef(90, 0, 1, 0);
		glColor3d(0, 0, 0.5);
		glutSolidCone(4, 12, 100, 100); // fim da ponta do carro
		
		glRotatef(180, 0, 1, 0); // comeco da cor no centro/costa
		glTranslatef(0, 0, 16);
		glColor3d(1, 1, 1);
		glutSolidCylinder(4, 35, 100, 100); // fim da cor no centro/costa

		glTranslatef(0, 4, 20); // comeco da cabine
		glRotatef(45, 0, 0, 1);
		glColor3d(1, 1, 1);
		glutSolidCylinder(5.7, 15, 4, 100); // fim da cabine

		
		glTranslatef(0, 0, -0.1); // comeco da janela
		glColor3d(0, 0.8, 0.9);
		glutSolidCylinder(5.8, 5, 4, 100); // fim da janela

		glRotatef(-45, 0, 0, 1); // comeco da crina
		glTranslatef(0, 5.6, 2.5);
		glRotatef(45, 0, 0, 1);
		glColor3d(0, 0.7, 0.88);
		glutSolidCylinder(2, 10, 4, 100); // fim da crina

		glRotatef(-45, 0, 0, 1); // comeco da roda direita
		glTranslatef(5.7, -14, 6);
		glRotatef(90, 0, 1, 0);
		glColor3d(0, 0, 0);
		glutSolidTorus(2, 3, 100, 100); // fim da roda direita

		glTranslatef(0, 0, -11.4); // comeco da roda esquerda
		glColor3d(0, 0, 0);
		glutSolidTorus(2, 3, 100, 100); // fim da roda esquerda
	glPopMatrix(); // fim do carro


	glPushMatrix(); // comeco da Arvore

		glTranslatef(40, -15, 20); // comeco do tronco
		glRotatef(90, -1, 0, 0);
		glColor3d(0.39, 0.26, 0.13);
		glutSolidCylinder(5, 100, 100, 20);	// fim do tronco


		glRotatef(90, 1, 0, 0); // comeco das folhas
		glTranslatef(0, 100, 10);
		glColor3d(0, 1, 0);
		glutSolidSphere(20,100,100);
		glTranslatef(0, 0, -20);
		glutSolidSphere(20,100,100);
		glTranslatef(10, 0, 10);
		glutSolidSphere(20,100,100);
		glTranslatef(-20, 0, 0);
		glutSolidSphere(20,100,100);
		glTranslatef(10, 20, 0);
		glutSolidSphere(20,100,100); // fim das folhas

	glPopMatrix(); // fim da Arvore

	glPushMatrix(); // comeco do poste
		glTranslatef(-40, -15, 20); // comeco do tronco
		glRotatef(90, -1, 0, 0);
		glColor3d(0.5, 0.5, 0.5);
		glutSolidCylinder(2, 50, 100, 20);	// fim do tronco

		glRotatef(90, 1, 0, 0); // comeco do lugar da lampada
		glTranslatef(2.5, 50, 0);
		glScalef(1.5, 0.333, 1);
		glutSolidCube(5); // fim do lugar da lampada

		glScalef(0.75, 3, 1); // comeco da lampada
		glTranslatef(1.5, -1, 0);
		glColor3d(1, 1, 0);
		glutSolidSphere(1, 10, 10); // fim da lampada
	glPopMatrix(); // fim do poste

	glPushMatrix(); // comeco do ceu nublado

	glTranslatef(0, 125, 0);
	glColor3d(1, 1, 1);

	glTranslatef(-40, 0, 0);
	glPushMatrix(); //comeco de prototipo de nuvem
	glPushMatrix(); // comeco andar 1
		glutSolidSphere(10, 200, 200);
		glPushMatrix(); // comeco camada 2
			glTranslatef(5, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);
			glPushMatrix(); // comeco camada 3
				glTranslatef(15, 0, 5);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);

				glTranslatef(20, 0, 5);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);

				glTranslatef(20, 0, 5);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);

			glPopMatrix(); // fim camada 3
			glTranslatef(10, 0, 20);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);
		glPopMatrix(); // fim camada 2
		glTranslatef(0, 0, 30);
		glutSolidSphere(10, 200, 200);
	glPopMatrix(); // fim andar 1
	glTranslatef(0, 5, 5);
	glPushMatrix(); // comeco andar 2
		glutSolidSphere(10, 200, 200);
		glPushMatrix(); // comeco camada 2
			glTranslatef(5, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);

			glTranslatef(10, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);

			glTranslatef(10, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);
		glPopMatrix(); // fim camada 2
		glTranslatef(0, 0, 20);
		glutSolidSphere(10, 200, 200);
	glPopMatrix(); // fim andar 2
	glTranslatef(0, 5, 5);
	glPushMatrix(); // comeco andar 3
		glutSolidSphere(10, 200, 200);

		glTranslatef(0, 0, 5);
		glutSolidSphere(10, 200, 200);

		glTranslatef(0, 0, 5);
		glutSolidSphere(10, 200, 200);
	glPopMatrix(); // fim andar 3
	glPopMatrix(); // fim prototipo nuvem

	glTranslatef(80, 0, -100);
	glPushMatrix(); //comeco de nuvem clone 1
	glPushMatrix(); // comeco andar 1
		glutSolidSphere(10, 200, 200);
		glPushMatrix(); // comeco camada 2
			glTranslatef(5, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);
			glPushMatrix(); // comeco camada 3
				glTranslatef(15, 0, 5);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);

				glTranslatef(20, 0, 5);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);

				glTranslatef(20, 0, 5);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);

			glPopMatrix(); // fim camada 3
			glTranslatef(10, 0, 20);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);
		glPopMatrix(); // fim camada 2
		glTranslatef(0, 0, 30);
		glutSolidSphere(10, 200, 200);
	glPopMatrix(); // fim andar 1
	glTranslatef(0, 5, 5);
	glPushMatrix(); // comeco andar 2
		glutSolidSphere(10, 200, 200);
		glPushMatrix(); // comeco camada 2
			glTranslatef(5, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);

			glTranslatef(10, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);

			glTranslatef(10, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);
		glPopMatrix(); // fim camada 2
		glTranslatef(0, 0, 20);
		glutSolidSphere(10, 200, 200);
	glPopMatrix(); // fim andar 2
	glTranslatef(0, 5, 5);
	glPushMatrix(); // comeco andar 3
		glutSolidSphere(10, 200, 200);

		glTranslatef(0, 0, 5);
		glutSolidSphere(10, 200, 200);

		glTranslatef(0, 0, 5);
		glutSolidSphere(10, 200, 200);
	glPopMatrix(); // fim andar 3
	glPopMatrix(); // fim nuvem clone 1


	glTranslatef(-150, 0, 150);
	glPushMatrix(); //comeco de nuvem clone 1
	glPushMatrix(); // comeco andar 1
		glutSolidSphere(10, 200, 200);
		glPushMatrix(); // comeco camada 2
			glTranslatef(5, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);
			glPushMatrix(); // comeco camada 3
				glTranslatef(15, 0, 5);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);

				glTranslatef(20, 0, 5);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);

				glTranslatef(20, 0, 5);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);
				glTranslatef(-10, 0, 0);
				glutSolidSphere(10, 200, 200);

			glPopMatrix(); // fim camada 3
			glTranslatef(10, 0, 20);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);
		glPopMatrix(); // fim camada 2
		glTranslatef(0, 0, 30);
		glutSolidSphere(10, 200, 200);
	glPopMatrix(); // fim andar 1
	glTranslatef(0, 5, 5);
	glPushMatrix(); // comeco andar 2
		glutSolidSphere(10, 200, 200);
		glPushMatrix(); // comeco camada 2
			glTranslatef(5, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);

			glTranslatef(10, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);

			glTranslatef(10, 0, 5);
			glutSolidSphere(10, 200, 200);
			glTranslatef(-10, 0, 0);
			glutSolidSphere(10, 200, 200);
		glPopMatrix(); // fim camada 2
		glTranslatef(0, 0, 20);
		glutSolidSphere(10, 200, 200);
	glPopMatrix(); // fim andar 2
	glTranslatef(0, 5, 5);
	glPushMatrix(); // comeco andar 3
		glutSolidSphere(10, 200, 200);

		glTranslatef(0, 0, 5);
		glutSolidSphere(10, 200, 200);

		glTranslatef(0, 0, 5);
		glutSolidSphere(10, 200, 200);
	glPopMatrix(); // fim andar 3
	glPopMatrix(); // fim nuvem clone 1



	glPopMatrix(); // fim do ceu nublado

	glutSwapBuffers();
}

void wireBox(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x / 2, 0, 0);
	glutWireCube(1);
	glScalef(x, y, z);
	glPopMatrix();
}

void myReshape(int winWidth, int winHeight) // reshape window
{
	int tam = winWidth < winHeight ? winWidth : winHeight;
	glViewport(0, 0, tam, tam); // reset the viewport
}

/*comandos especiais do teclado*/

void keySpecial(int key, int x, int y)
{
	printf("(%d, %d)\n", x, y);
	switch (key)
	{
	case GLUT_KEY_LEFT:
		printf("Left pressed\n");
		break;
	case GLUT_KEY_UP:
		printf("Up pressed\n");
		break;
	}

	if (glutGetModifiers() == GLUT_ACTIVE_ALT) // GLUT_ACTIVE_CTRL ou SHIFT
		printf("ALT pressed\n");
}

void myKeyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
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
	case 'p':
		exit(0);
		break;
	}
}

// imprimir as coordenadas com o clique do mouse

void myMouse(int b, int s, int x, int y)
{
	switch (b)
	{
	case GLUT_LEFT_BUTTON:
		printf("(%d, %d)\n", x, y);
	}
}

// função detecta movimento do mouse e salva coordenadas
void myMotion(int x, int y)
{
	printf("Motion: (%d, %d)\n", x, y);
}

void init(void)

{

	// Define a cor de fundo da janela de visualização como branca

	glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

	// Habilita a definição da cor do material a partir da cor corrente

	glEnable(GL_COLOR_MATERIAL);

	// Habilita o uso de iluminação

	glEnable(GL_LIGHTING);

	// Habilita a luz de número 0

	glEnable(GL_LIGHT0);

	// Habilita o depth-buffering

	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de colorização de Gouraud

	glShadeModel(GL_FLAT);

	// Inicializa a variável que especifica o ângulo da projeção

	// perspectiva

	angle = 45;

	// Inicializa as variáveis usadas para alterar a posição do

	// observador virtual

	rotX = 0;

	rotY = 0;

	obsX = obsY = 0;

	obsZ = 150;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	// Define o modo de operação da GLUT

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Especifica a posição inicial da janela GLUT

	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT

	glutInitWindowSize(450, 450);

	// Cria a janela passando como argumento o título da mesma

	glutCreateWindow("Quero Morrer!");

	// Registra a função callback de redesenho da janela de visualização

	glutDisplayFunc(display);

	// Registra a função callback de redimensionamento da janela de visualização

	glutReshapeFunc(Reshape);

	// Registra a função callback para tratamento das teclas normais

	glutKeyboardFunc(Teclado);

	// Registra a função callback para tratamento das teclas especiais

	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback para eventos de botões do mouse

	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para eventos de movimento do mouse

	glutMotionFunc(GerenciaMovim);

	// Chama a função responsável por fazer as inicializações

	init();

	// Inicia o processamento e aguarda interações do usuário

	glutMainLoop();

	return 0;
}
