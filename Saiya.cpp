#include "Saiya.h"

Saiya::Saiya(int x, int y)
{
    if(x != NULL && y != NULL)
    {
        this->y=y;
        this->x=x;
    }else
    {
        this->y=150;
        this->x=200;
    }
    sprites.push_back(IMG_Load("saiya/SR.png"));
    sprites.push_back(IMG_Load("saiya/SF.png"));
    sprites.push_back(IMG_Load("saiya/SB.png"));
}

Saiya::~Saiya()
{
    //dtor
}
