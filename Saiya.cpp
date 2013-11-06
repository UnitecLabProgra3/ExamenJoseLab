#include "Saiya.h"

Saiya::Saiya()
{
    this->y=150;
    sprites.push_back(IMG_Load("saiya/SR.png"));
    sprites.push_back(IMG_Load("saiya/SF.png"));
    sprites.push_back(IMG_Load("saiya/SB.png"));
}

Saiya::~Saiya()
{
    //dtor
}
