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
	leftSide = IMG_Load("Emplacement � D�finir");
	rightSide = IMG_Load("Emplacement � D�finir");
	frontSide = IMG_Load("Emplacement � D�finir");
	backSide = IMG_Load("Emplacement � D�finir");
}
