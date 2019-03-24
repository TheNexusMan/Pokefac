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
	leftSide = IMG_Load("Emplacement à définir");
	rightSide = IMG_Load("Emplacement à définir");
	frontSide = IMG_Load("Emplacement à définir");
	backSide = IMG_Load("Emplacement à définir");
}
