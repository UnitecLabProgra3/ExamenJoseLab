#include "Kaiyo.h"

Kaiyo::Kaiyo()
{
    round = true;
    this->y=380;
    this->x=530;
    sprites.push_back(IMG_Load("kaiyo/KR.png"));
    sprites.push_back(IMG_Load("kaiyo/KF.png"));
    sprites.push_back(IMG_Load("kaiyo/KB.png"));
}

void Kaiyo::logic()
{
    if(round)
    {
        if(arriba)
            this->y-=speedy;
        else
            this->y+=speedy;
        if(y>380)
        {
            arriba=true;
            round = false;
            abajo = false;
        }
        if(y<-10)
        {
            arriba=false;
            abajo=true;
        }
    }else
    {
        if(derecha)
            this->x+=speedx;
        else
            this->x-=speedx;
        if(x>530)
        {
            derecha=false;
            round = true;
        }
        if(x<10)
            derecha=true;
    }
}

Kaiyo::~Kaiyo()
{
    //dtor
}
