#include "Roshi.h"

Roshi::Roshi(int x, int y)
{
    this->x=x;
    this->y=y;
    frame = 0;
    iteration = 0;
    roshi_sprite.push_back(IMG_Load("roshi/Roshi1.png"));
    roshi_sprite.push_back(IMG_Load("roshi/Roshi2.png"));
    roshi_sprite.push_back(IMG_Load("roshi/Roshi3.png"));
    roshi_sprite.push_back(IMG_Load("roshi/Roshi4.png"));
}

void Roshi::dibujar(SDL_Surface*screen)
{
    SDL_Rect offset;

    offset.x=this->x;
    offset.y=this->y;
    if(iteration%600==0 && frame == 0)
    {
        frame++;
        iteration = 1;

    }
    if(iteration%100==0 && frame != 0)
    {
        frame = 0;
    }
    if(iteration%10==0 && frame != 0)
    {
        frame++;
        if(frame>3)
        {
            frame=1;
        }

    }
    SDL_BlitSurface(this->roshi_sprite[frame], NULL, screen, &offset);
    iteration++;
}

bool Roshi::collision_logic(Personaje *player)
{
    int x1 = this->x+25;
    int y1 = this->y+30;
    int x2 = this->x+55;
    int y2 = this->y+70;
    int px1 = player->x+25;
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

Roshi::~Roshi()
{
    //dtor
}
