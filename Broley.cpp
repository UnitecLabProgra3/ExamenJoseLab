#include "Broley.h"

Broley::Broley()
{
    this->y=300;
    moving = true;
    sprites.push_back(IMG_Load("Broley/BR1.png"));
    sprites.push_back(IMG_Load("Broley/BR2.png"));
    sprites.push_back(IMG_Load("Broley/BR3.png"));
    sprites.push_back(IMG_Load("Broley/BF.png"));
    sprites.push_back(IMG_Load("Broley/BB.png"));
}

void Broley::dibujar(SDL_Surface*screen)
{
    SDL_Rect offset;

    offset.x=this->x;
    offset.y=this->y;
    if(derecha)
    {
        frame = 4;
    }else
    {
        frame = 3;
    }
    SDL_BlitSurface(this->sprites[frame], NULL, screen, &offset);
    iteracion++;
}

void Broley::logic()
{
    if(moving)
    {
        x-=speedx;
        y-=speedy;
    }
}

bool Broley::collision_logic(Personaje* player)
{
    int x1 = this->x+25;
    int y1 = this->y+25;
    int x2 = this->x+60;
    int y2 = this->y+80;
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

Broley::~Broley()
{
    //dtor
}
