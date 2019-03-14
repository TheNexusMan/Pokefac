#include "characterTexture.h"


characterTexture::characterTexture()
{
	loadImage();
}


characterTexture::~characterTexture()
{
}

void characterTexture::loadImage()
{
	leftSide = IMG_Load("Emplacement à Définir");
	rightSide = IMG_Load("Emplacement à Définir");
	frontSide = IMG_Load("Emplacement à Définir");
	backSide = IMG_Load("Emplacement à Définir");
}
