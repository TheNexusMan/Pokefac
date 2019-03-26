/**
@brief Class winTxt, gère les fonctions de bases d'affichage dans un terminal

@author pokeFac team
@file winTxt.h
@version 1.0
@date 19/03/2019

*/
#ifndef WINTXT_H
#define WINTXT_H

//! \brief une fentre texte est un tableau 2D de caractres
class WinTXT {

private:

    int dimx;       //!< \brief largeur
    int dimy;       //!< \brief heuteur
    char* win;      //!< \brief stocke le contenu de la fentre dans un tableau 1D mais on y accede en 2D

public:

    WinTXT (int dx, int dy);
    void clear (char c=' ');
    void print (int x, int y, char c);
    void print (int x, int y, char* c);
    void draw (int x=0, int y=0);
    void pause();
    char getCh();

};

void termClear ();

#endif
