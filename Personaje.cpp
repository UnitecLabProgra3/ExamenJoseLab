#include "Personaje.h"

Personaje::Personaje(int x, int y)
{
    this->current_frame=0;
    this->current_iteration=0;
    got_hit=false;
    hit_anim=false;
    HP=3;
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
    personaje.push_back(NULL);
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
    }else if(!moving)
    {
        current_frame=0;
    }
    current_iteration++;
    if(got_hit)
    {
        if(in_battle)
        {
            current_frame=0;
            in_battle = false;
        }
        this->x=0;
        this->y=0;
        hit_anim=true;
        got_hit=false;
        HP--;
        current_iteration=0;
    }
    if(hit_anim)
    {
        if(current_iteration % 2 == 0)
        {
            last_frame=current_frame;
            current_frame=13;
        }else
        {
            current_frame=last_frame;
        }
        if(current_iteration >= 100)
        {
            hit_anim = false;
        }
    }
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
