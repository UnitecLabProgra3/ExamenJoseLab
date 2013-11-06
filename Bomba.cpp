#include "Bomba.h"

Bomba::Bomba()
{
    sprites.push_back(IMG_Load("bomba/01.png"));
    sprites.push_back(IMG_Load("bomba/02.png"));
    sprites.push_back(IMG_Load("bomba/03.png"));
}

Bomba::~Bomba()
{
    //dtor
}
