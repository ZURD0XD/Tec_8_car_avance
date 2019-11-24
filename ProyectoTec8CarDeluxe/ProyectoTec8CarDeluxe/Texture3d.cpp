#include "Texture.h"

Texture3d::Texture3d()
{
	fileLocation = (char*)"";
}

Texture3d::Texture3d(char* _fileLocation)
{
	fileLocation = _fileLocation;
}

void Texture3d::setFileLocation(char* _fileLocation)
{
	fileLocation = _fileLocation;
}

void Texture3d::makeCheckImage() {

	int i, j, c;
	for (i = 0; i < checkImageWidth; i++) {
		for (j = 0; j < checkImageHeight; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) * 255;

			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
		}
	}
}

void Texture3d::loadTexture()
{
	if ((!ImageLoad(fileLocation))) {
		system("PAUSE");
		exit(1);
	}

	makeCheckImage();
}

void Texture3d::useTexture()
{
	/*glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);*/

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	/*glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);*/
}

int Texture3d::ImageLoad(char* filename) {
	FILE* file;
	unsigned long size; // size of the image in bytes.
	unsigned long i; // standard counter.
	unsigned short int planes; // number of planes in image (must be 1)
	unsigned short int bpp; // number of bits per pixel (must be 24)
	char temp; // temporary color storage for bgr-rgb conversion.

	file = fopen(filename, "rb");
  	fseek(file, 18, SEEK_CUR);
	i = fread(&sizeX, 4, 1, file);
	i = fread(&sizeY, 4, 1, file);
	size = sizeX * sizeY * 3;
	fread(&planes, 2, 1, file);

	if (planes != 1) {
		//printf("Planes from %s is not 1: %u\n", filename, planes);
		system("PAUSE");
		return 0;
	}

	i = fread(&bpp, 2, 1, file);
	fseek(file, 24, SEEK_CUR);
	data = (char*)malloc(size);

	if (data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		system("PAUSE");
		return 0;
	}

	if ((i = fread(data, size, 1, file)) != 1) {
		//		printf("Error reading image data from %s.\n", filename);
		system("PAUSE");
		return 0;
	}

	for (i = 0; i < size; i += 3) { // reverse all of the colors. (bgr -> rgb)
		temp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = temp;
	}
	return 1;
}

void Texture3d::clearTexture()
{
	glDeleteTextures(1, &texture);
	fileLocation = (char*)"";
}

Texture3d::~Texture3d()
{
	clearTexture();
}