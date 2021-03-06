
#include "Mundo.h"
#include "ETSIDI.h"
#include "glut.h"
#include <iostream>

using namespace std;

using namespace ETSIDI;

Mundo mundo;

enum { MOUSE_LEFT_BUTTON, MOUSE_MIDDLE_BUTTON, MOUSE_RIGHT_BUTTON };
enum { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };

//los callback, funciones que seran llamadas automaticamente por la glut
//cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void onDraw(void); //esta funcion sera llamada para dibujar
void onTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void onKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void onSpecialKeyboardDown(int key, int x, int y); //cuando se pulse una tecla especial	
void OnMouseClick(int button, int state, int x, int y);

int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	//Registrar los callbacks
	glutDisplayFunc(onDraw);
	glutTimerFunc(25, onTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(onKeyboardDown);
	glutSpecialFunc(onSpecialKeyboardDown);
	glutMouseFunc(OnMouseClick);


	//mundo.inicializa();

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}

void onDraw(void)
{
	//Borrado de la pantalla
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.1, 30, // posicion del ojo
		0.0, 0, 0.0, // hacia que punto mira (0,0,0)
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
						//en este caso dibujamos solo un cubo de alambre
						//aqui es donde hay que poner el código de dibujo

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(1, 0); glVertex3f(10, 10, 0);
	glTexCoord2d(1, 1); glVertex3f(10, -10, 0);
	glTexCoord2d(0, 1); glVertex3f(-10, -10, 0);
	glTexCoord2d(0, 0); glVertex3f(-10, 10, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	setTextColor(0, 0, 0);
	setFont("fuentes/Game of Thrones.ttf", 16);
	printxy("GAME OF THRONES", -9.5, -9.5);

	setTextColor(0, 0, 0);
	setFont("fuentes/Game of Thrones.ttf", 8);
	printxy("Trapiello Y Perea Vanguelov", 1, -9.5);
	//Al final, cambiar el buffer (redibujar)
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void onKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	mundo.tecla(key);

	glutPostRedisplay();
}
void onSpecialKeyboardDown(int key, int x, int y)
{
	//mundo.teclaEspecial(key);
}
void onTimer(int value)
{
	//poner aqui el código de animacion

	//no borrar estas lineas
	glutTimerFunc(25, onTimer, 0);
	glutPostRedisplay();
}

void OnMouseClick(int b, int state, int x, int y)
{
	//////////////
	//captures clicks with mouse with or without special keys (CTRL or SHIFT)
	//gives control to board scene
	bool down = (state == GLUT_DOWN);
	int button;
	if (b == GLUT_LEFT_BUTTON) 
	{
		button = MOUSE_LEFT_BUTTON;
		cout << "MOUSE_LEFT_BUTTON" << "\nX = " << x << "Y = " << y << endl;
	}
	if (b == GLUT_RIGHT_BUTTON)
	{
		button = MOUSE_RIGHT_BUTTON;
		cout << "MOUSE_RIGHT_BUTTON" <<"\nX = " << x << "Y = " << y << endl;
	}
	if (b == GLUT_MIDDLE_BUTTON)
	{
		button = MOUSE_MIDDLE_BUTTON;
		cout << "MOUSE_MIDDLE_BUTTON" << "\nX = " << x << "Y = " << y << endl;
	}
	int specialKey = glutGetModifiers();
	bool ctrlKey = (specialKey & GLUT_ACTIVE_CTRL) ? true : false;
	bool sKey = specialKey & GLUT_ACTIVE_SHIFT;



	glutPostRedisplay();
}