#pragma once

#include <GL/glut.h>
#include <iostream>

class Texture3d {

#define checkImageWidth 64
#define checkImageHeight 64

	GLubyte checkImage[checkImageWidth][checkImageHeight][3];

public:

	GLuint texture;
	char* fileLocation;
	unsigned long sizeX;
	unsigned long sizeY;
	char* data;

public:

	Texture3d();
	Texture3d(char* _fileLocation);
	void setFileLocation(char* _fileLocation);
	void makeCheckImage(void);
	void loadTexture(void);
	void useTexture(void);
	int ImageLoad(char* filename);
	void clearTexture(void);
	~Texture3d();
};
