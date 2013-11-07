#include "Enemigo.h"

Enemigo::Enemigo()
{
    this->x=200;
    this->y=200;
    this->speedx=3;
    this->speedy=3;
    this->iteracion = 0;
    this->frame = 0;
    this->derecha=true;
    this->izquierda = false;
    this->arriba = false;
    this->abajo = false;
}

Enemigo::~Enemigo()
{
    //dtor
}

void Enemigo::dibujar(SDL_Surface*screen)
{
    SDL_Rect offset;

    offset.x=this->x;
    offset.y=this->y;
    if(derecha || abajo)
    {
        frame = 2;
    }else
    {
        frame = 1;
    }
    SDL_BlitSurface(this->sprites[frame], NULL, screen, &offset);
    iteracion++;
}

void Enemigo::logic()
{
    if(derecha)
        this->x+=speedx;
    else
        this->x-=speedx;
    if(arriba)
        this->y-=speedy;
    else
        this->y+=speedy;
    if(x>560)
        derecha=false;
    if(x<-10)
        derecha=true;
    if(y>400)
        arriba=true;
    if(y<-30)
        arriba=false;
}

bool Enemigo::collision_logic(Personaje* player)
{
    int x1 = this->x+25;
    int y1 = this->y+30;
    int x2 = this->x+50;
    int y2 = this->y+70;
    int px1 = player->x+30;
    int py1 = player->y+30;
    int px2 = player->x+55;
    int py2 = player->y+70;
    if(((x1 >= px1 && x1 <= px2) && (y1 >= py1 && y1 <= py2)))
        return true;
    if(((x2 >= px1 && x2 <= px2) && (y2 >= py1 && y2 <= py2)))
        return true;
    if(((x1 >= px1 && x1 <= px2) && (y2 >= py1 && y2 <= py2)))
        return true;
    if(((x2 >= px1 && x2 <= px2) && (y1 >= py1 && y1 <= py2)))
        return true;

    return false;
}
