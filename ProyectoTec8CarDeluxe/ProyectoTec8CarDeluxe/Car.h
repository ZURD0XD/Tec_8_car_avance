#pragma once
#include "Shapes.h"
#include "Texture.h"
#include <GL/glut.h>

// ------- CLASE HIJA / RECTANGULO ---------------------------
class Car : public Shapes {

	// ----- ATRIBUTOS PERTENECIENTES A RECTANGULO -----------
private:
	float base;
	float height;
	bool enemy;
	Vertex vertices[4];
	Texture3d text;

public:
	// ------- CONSTRUCTORES SOBRECARGADOS -----------------------
	// DE CREARSE EL OBJETO VACIO, AUTOMATICAMENTE SON ASIGNADOS
	// LOS VALORES FALTANTES, DEL MISMO MODO CON LOS OTROS 
	// CONSTRUCTORES QUE NO SE ENVIAN LOS PARAMETROS COMPLETOS ---
	Car() {
		setOrigin(0, 0);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setBase(10);
		setHeight(5);
		setEnemy(false);
		setNoVertices(4);
		calculateVertex();
	}

	Car(float x, float y) {
		setOrigin(x, y);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setBase(10);
		setHeight(5);
		setEnemy(false);
		setNoVertices(4);
		calculateVertex();
	}

	Car(float x, float y, float ba, float h, bool e) {
		setOrigin(x, y);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setBase(ba);
		setHeight(h);
		setEnemy(e);
		setNoVertices(4);
		calculateVertex();
	}

	Car(float x, float y, float ba, float h, bool e, float r, float g, float b) {
		setOrigin(x, y);
		setColor(r, g, b);
		setLineWidth(1);
		setBase(ba);
		setHeight(h);
		setEnemy(e);
		setNoVertices(4);
		calculateVertex();

	}

	Car(float x, float y, float ba, float h, bool e, float r, float g, float b, int lwidth) {
		setOrigin(x, y);
		setColor(r, g, b);
		setLineWidth(lwidth);
		setBase(ba);
		setHeight(h);
		setEnemy(e);
		setNoVertices(4);
		calculateVertex();

	}

	Car(const Car& car) {
		Vertex pos = car.getOrigin();
		setOrigin(pos.getX(), pos.getY());
		Color col = car.getColor();
		setColor(col.getR(), col.getG(), col.getB());
		setLineWidth(car.getLineWidth());
		setBase(car.getBase());
		setHeight(car.getHeight());
		setEnemy(car.getEnemy());
		setNoVertices(4);
		calculateVertex();

	};

	// ------- METODOS IMPLEMENTADOS DE LOS SETTERS --------------
	// SI ALGUNOS VALORES IMPORTANTES QUE PUDIESEN AFECTAR EL
	// FUNCIONAMIENTO DEL SET NO CONOCEN LOS REQUISITOS
	// NECESARIOS, SON ASIGNADOS VALORES PREDEFINIDOS ------------
	void setBase(float b) {
		if (b > 0) { base = b; }
		else { base = b * -1; }
		area = calculateArea();
		perimeter = calculatePerimeter();
		calculateVertex();
	}

	void setHeight(float h) {
		if (h > 0) { height = h; }
		else { height = h * -1; }
		area = calculateArea();
		perimeter = calculatePerimeter();
		calculateVertex();
	}

	void setEnemy(bool e) {
		enemy = e;
		assignTexture();
	}

	float getBase() const { return base; }
	float getHeight() const { return height; }
	bool getEnemy() const { return enemy; }

	double calculateArea() { return (base * height); }
	double calculatePerimeter() { return (2 * (base + height)); }

	void assignTexture()
	{
		if (getEnemy())
		{
			text = Texture3d((char*)"Carrito_cutre.bmp");
		}
		else
		{
			text = Texture3d((char*)"Carrito_cutre_1.bmp");
		}

		text.loadTexture();
	}

	void calculateVertex() {
		Vertex aux_pos = getOrigin();
		float x1 = aux_pos.getX() - (getBase() / 2), y1 = aux_pos.getY() - (getHeight() / 2);
		float x2 = aux_pos.getX() + (getBase() / 2), y2 = aux_pos.getY() + (getHeight() / 2);
		setVertices(x1, y1, x2, y2);
	}

	void setVertices(float x1, float y1, float x2, float y2) {
		vertices[0].setX(x1), vertices[0].setY(y1); // vertice 1
		vertices[1].setX(x1), vertices[1].setY(y2); // vertice 2
		vertices[2].setX(x2), vertices[2].setY(y2); // vertice 3
		vertices[3].setX(x2), vertices[3].setY(y1); // vertice 4
	}

	void drawShape() {

		glLineWidth(getLineWidth());
		glEnable(GL_TEXTURE_2D);
		text.useTexture();
		glBindTexture(GL_TEXTURE_2D, text.texture);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex2i(vertices[0].getX(), vertices[0].getY());
		glTexCoord2f(1.0, 0.0);
		glVertex2i(vertices[1].getX(), vertices[1].getY());
		glTexCoord2f(1.0, 1.0);
		glVertex2i(vertices[2].getX(), vertices[2].getY());
		glTexCoord2f(0.0, 1.0);
		glVertex2i(vertices[3].getX(), vertices[3].getY());
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void drawShapeFill() {

		//Color aux_color = getColor();
		//glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		//glLineWidth(getLineWidth());

		//glBindTexture(GL_TEXTURE_2D, texture[0]);
		glBegin(GL_QUADS);
		//glTexCoord2f(0.0, 0.0);
		glVertex2i(vertices[0].getX(), vertices[0].getY());
		//glTexCoord2f(1.0, 0.0);
		glVertex2i(vertices[1].getX(), vertices[1].getY());
		//glTexCoord2f(1.0, 1.0);
		glVertex2i(vertices[2].getX(), vertices[2].getY());
		//glTexCoord2f(0.0, 1.0);
		glVertex2i(vertices[3].getX(), vertices[3].getY());
		/*
		for (int i = 0; i < NoVertices; i++)
		{
		glVertex2i(vertices[i].getX(), vertices[i].getY());
		}*/
		glEnd();
		//glBindTexture(GL_TEXTURE_2D, 0);
		//glDeleteTextures(1, &texture[0]);
	}

	void moveShape(float _x, float _y) {
		origin.moveVertex(_x, _y);
		calculateVertex();
	}

	void scaleShape(float factor) {
		setBase(factor * getBase());
		setHeight(factor * getHeight());
		calculateVertex();
	}

	void rotateShape(float _x, float _y, double _theta) {
		for (int i = 0; i < NoVertices; i++)
		{
			vertices[i].rotateVertex(_x, _y, _theta);
		}
	}

};
