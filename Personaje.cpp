#include "Personaje.h"

Personaje::Personaje(int x, int y)
{
    this->current_frame=0;
    this->current_iteration=0;
    personaje.push_back(IMG_Load("testpersonaje/NR.png"));
    personaje.push_back(IMG_Load("testpersonaje/NS1.png"));
    personaje.push_back(IMG_Load("testpersonaje/NS2.png"));
    personaje.push_back(IMG_Load("testpersonaje/NS3.png"));
    personaje.push_back(IMG_Load("testpersonaje/NS4.png"));
    personaje.push_back(IMG_Load("testpersonaje/NS4.png"));
    personaje.push_back(IMG_Load("testpersonaje/NS4.png"));
    personaje.push_back(IMG_Load("testpersonaje/NS3.png"));
    personaje.push_back(IMG_Load("testpersonaje/NS2.png"));
    personaje.push_back(IMG_Load("testpersonaje/NS1.png"));
    personaje.push_back(IMG_Load("testpersonaje/NS1.png"));
    personaje.push_back(IMG_Load("testpersonaje/NF.png"));
    personaje.push_back(IMG_Load("testpersonaje/NB.png"));
    this->x = x;
    this->y = x;
    in_battle = false;
    moving = false;
}

void Personaje::logic()
{
    if(in_battle)
    {
        if(current_iteration%10==0)
        {
            current_frame++;
            if(current_frame>10)
                current_frame=1;
        }
    }else
    {
        current_frame=0;
    }
    current_iteration++;
}

void Personaje::dibujar(SDL_Surface* screen)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( personaje[current_frame], NULL, screen, &offset );
}

Personaje::~Personaje()
{
    //dtor
}
