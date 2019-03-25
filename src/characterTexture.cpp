#include "CharacterTexture.h"


CharacterTexture::CharacterTexture()
{
	loadImage();
}


CharacterTexture::~CharacterTexture()
{
}

void CharacterTexture::loadImage()
{
	leftSide = IMG_Load("Emplacement à définir");
	rightSide = IMG_Load("Emplacement à définir");
	frontSide = IMG_Load("Emplacement à définir");
	backSide = IMG_Load("Emplacement à définir");
}
