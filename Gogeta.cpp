#include "Gogeta.h"

Gogeta::Gogeta()
{
    this->y = 250;
    sprites.push_back(IMG_Load("gogeta/GR.png"));
    sprites.push_back(IMG_Load("gogeta/GF.png"));
    sprites.push_back(IMG_Load("gogeta/GB.png"));
}

Gogeta::~Gogeta()
{
    //dtor
}
