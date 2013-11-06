#include "Fantasmita.h"

Fantasmita::Fantasmita()
{
    sprites.push_back(IMG_Load("fantasmita/01.png"));
    sprites.push_back(IMG_Load("fantasmita/02.png"));
    sprites.push_back(IMG_Load("fantasmita/03.png"));
}

Fantasmita::~Fantasmita()
{
    //dtor
}
