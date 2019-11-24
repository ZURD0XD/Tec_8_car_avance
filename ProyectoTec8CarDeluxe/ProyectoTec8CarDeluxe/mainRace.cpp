/*
* INTEGRANTES:
* IVAN FRANCO DELGADO
* JESUS EDUARDO SOSA DIAZ
* JOSUE TORRES AVALOS
*/
#include <GL/glut.h> // IMPORTA LA LIBRERIA DE GLUT
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <Windows.h>
#include <string>
#include <MMSystem.h>
#include <iterator>
#include "Car.h"

// VALORES UTILIZADOS PARA EL TAMANO DE LA
// PANTALLA DEFINIENDO ALTO Y ANCHO
#define HEIGHT 720
#define WIDTH 880


using namespace std;

// PROTOTIPOS DE FUNCIONES
void initializer(void);
bool g_o = true;
int sum = 0;
int pas_cars = 0;
int start = 0;
int fps = 1;

void writeBitmapString(void *font, const char *string);
void userInterface(void);
list <Car> Enemigos_guardar(Car Enemigos[]);
void keyInput(unsigned char, int, int);
void specialKeyInput(int, int, int);
void mouseControl(int, int, int, int);
void ValueTime(int value);
void Colission(void);
void MapCar(void);
void restart_Cars(void);
void Menu_principal(void);
/*void Generar_Enemigos(list <Car> Enemigos);*/

static long font = (long)GLUT_BITMAP_TIMES_ROMAN_24, font_Name = (long)GLUT_BITMAP_HELVETICA_12;
Car carro(100,110,100,150,false,1.0,0.0,1.0);
Car Enemigos[3] = {Car (210,610,100,150,true,0.0,1.0,1.0),Car(210,1100,100,150,true,0.0,1.0,1.0),Car(210,1590,100,150,true,0.0,1.0,1.0) };

list<Car> Enemigos_ls = Enemigos_guardar(Enemigos);


Vertex Origin_carro(100,110);
Vertex Origin_enemigo(100, 610);

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT); // ESTABLECE EL TAMANO DE LA VENTANA
	glutCreateWindow("Tec8 Car Deluxe");

	initializer(); // INICIALIZA LA VENTANA

	glutDisplayFunc(userInterface); // ACTUALIZA LA PANTALLA DE TRAZADO
	glutKeyboardFunc(keyInput); // CAPTURA LAS TECLAS PERTENECIENTES AL ASCII
	glutSpecialFunc(specialKeyInput); // CAPTURA LAS TECLAS ESPECIALES COMO LAS FLECHAS
	glutTimerFunc(1000/fps, ValueTime, 0);
	glutMouseFunc(mouseControl); // CAPTURA LOS CLICS
	glutMainLoop(); // GENERA EL LOOP

	return 0;
}

void restart_Cars() {
	if (g_o) {
		g_o = false;
		int y = 610;
		for (Car &enemy : Enemigos_ls) {
			enemy.setOrigin(210,y);
			y += 490;
		}
	}
}

void Colission(void) {
	for (Car &enemy : Enemigos_ls) {
		float x2 = carro.getOrigin().getX() + carro.getBase();
		float y2 = carro.getOrigin().getY() + carro.getHeight();
		Vertex Player_vtx(x2,y2);
		float x2_e = enemy.getOrigin().getX() + carro.getBase();
		float y1_e = enemy.getOrigin().getY();
		Vertex Enemigo_vtx(x2_e, y1_e);
		if (Enemigo_vtx.getX() == Player_vtx.getX()) {
			if (Enemigo_vtx.getY() <= Player_vtx.getY() && Enemigo_vtx.getY() + enemy.getHeight() >= Player_vtx.getY()- carro.getHeight()) {
				cout << "colisiona" << endl;
				start = 0;
				g_o = true;
			}
		}
	}
}

list <Car> Enemigos_guardar(Car Enemigos[]) {
	list <Car> temp;
	for (int i = 0; i < 3; i++)
	{
		temp.push_front(Enemigos[i]);
	}
	return temp;
}

/*void Generar_Enemigos(list <Car> enemigos) {
	for (Car &enemy : Enemigos_ls) {
		enemy.drawShape();
	}
}*/

void Mover_enemigos() {
	restart_Cars();
	for (Car &enemy : Enemigos_ls) {
		Vertex temp = enemy.getOrigin();
		if (temp.getY() <= -350) {
			pas_cars++;
			enemy.setOrigin(carro.getOrigin().getX(), 1050);
		}
		enemy.moveShape(0,-10);
	}
}

void Menu_principal(void) {
	glColor3f(.7, .3, .8);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glVertex2f(275, 20);
	glVertex2f(480+135, 20);
	glVertex2f(480+135, 700);
	glVertex2f(275, 700);
	glEnd();
	glFlush();
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2f(340, 420);
	writeBitmapString((void*)font, "TEC8 CAR DELUXE");
	glColor3f(0.0, 1.0, 1.0);
	glRasterPos2f(430, 400);
	writeBitmapString((void*)font_Name, " By:");
	glRasterPos2f(405, 385);
	writeBitmapString((void*)font_Name, "Eduardo Sosa");
	glRasterPos2f(405, 365);
	writeBitmapString((void*)font_Name, "Josue Torres");
	glRasterPos2f(400, 345);
	writeBitmapString((void*)font_Name, "Ivan el delgado");
	glColor3f(0.2, 0.3, 0.6);
	glRasterPos2f(355, 310);
	writeBitmapString((void*)font, "SPACE: Para jugar");
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(365, 275);
	writeBitmapString((void*)font, "E: salir del juego");
}


void MapCar(void) {
	glColor3f((.2), (.5), (.7));
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glVertex2f(40, 20);
	glVertex2f(380, 20);
	glVertex2f(380, 700);
	glVertex2f(40, 700);
	glEnd();
	glFlush();
}

void ValueTime(int value) {
	glutPostRedisplay();
	glutTimerFunc(1000/fps, ValueTime, 0);
}

void writeBitmapString(void *font, const char *string){
	const char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void keyInput(unsigned char key, int x, int y){
	switch (key){
		
		case 97:
			if (Origin_carro.getX() != 100) {
				carro.moveShape(-110,0);
				Origin_carro.setX(Origin_carro.getX() - 110);
			}
			
			break;
		case 100:
			if (Origin_carro.getX() != 320.0) {
				carro.moveShape(110,0);
				Origin_carro.setX(Origin_carro.getX() + 110);
			}
			break;
		case 115:
			if (Origin_carro.getY() != 110) {
				carro.moveShape(0, -70);
				Origin_carro.setY(Origin_carro.getY() - 70);
			}
			break;
		case 119:
			if (Origin_carro.getY() <= 300) {
				carro.moveShape(0, 70);
				Origin_carro.setY(Origin_carro.getY() + 70);
			}
			break;
		case ' ':
			/*PlaySound(TEXT("super stick golf song with download link.wav"), NULL, SND_SYNC);*/
			start = 1;
			break;
		case '	':
			start = 0;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void specialKeyInput(int key, int x, int y)
{
}

void mouseControl(int button, int state, int x, int y)
{
}

void initializer(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // COLOR CANVAS
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT); // TAMANO DE MANTA
}

void menuOptions(void) {
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2f(650, 690);
	writeBitmapString((void*)font, "TEC8 CAR DELUXE");
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(650, 670);
	writeBitmapString((void*)font, "               Puntuacion: ");
	glRasterPos2f(780, 650);
	writeBitmapString((void*)font,std::to_string(pas_cars).c_str());
}

void userInterface(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (start == 0) {
		fps = 1;
		glClearColor(0.0, 0.0, 0.0, 0.0);
		Menu_principal();
	}
	else if (start == 1) {
		fps = 80;
		Mover_enemigos();
		Colission();
		MapCar();
		/*Generar_Enemigos(Enemigos_ls); */
		glClearColor(0.0, 0.0, 0.0, 0.0);
		menuOptions();
		carro.drawShape();
	}
	glFlush();
}