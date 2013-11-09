#include "Gogeta.h"

Gogeta::Gogeta(Personaje*player)
{
    this->player = player;
    this->y = 250;
    this->speedx=speedx*2;
    this->speedy=speedy*2;
    gainx=0;
    gainy=0;
    lock_left=false;
    lock_right=false;
    lock_up=false;
    lock_down=false;
    gogeta_crazy=false;
    phase=0;
    sprites.push_back(IMG_Load("gogeta/GR.png"));
    sprites.push_back(IMG_Load("gogeta/GF.png"));
    sprites.push_back(IMG_Load("gogeta/GB.png"));
}

void Gogeta::logic()
{

    if(gogeta_crazy)
    {
        if(phase==0)
        {
            sourcex=x;
            sourcey=y;
            goalx=player->x;
            goaly=player->y;
            int mainx = goalx-sourcex;
            int mainy = goaly-sourcey;
            double res = pow(mainx, 2.0)+pow(mainy, 2.0);
            double gainx2 = sqrt((pow(mainx, 2.0)/res)*64.0);
            double gainy2 = sqrt((pow(mainy, 2.0)/res)*64.0);
            double moderx = gainx2;
            while(moderx>1.0)
            {
                moderx-=1.0;
            }
            double modery = gainy2;
            while(modery>1.0)
            {
                modery-=1.0;
            }
            gainx = gainx2-moderx;
            gainy = gainy2-modery;
            phase++;
        }
        if(phase==1)
        {
            if(goalx > sourcex)
            {
                lock_right=true;
            }else
            {
                lock_left=true;
            }
            if(goaly > sourcey)
            {
                lock_down=true;
            }else
            {
                lock_up=true;
            }
            phase++;
        }
        if(phase==2)
        {
            if(lock_right)
            {
                x--;
                derecha=false;
            }
            if(lock_left)
            {
                x++;
                derecha=true;
            }
            if(lock_down)
            {
                y--;
                arriba=true;
            }
            if(lock_up)
            {
                y++;
                arriba=false;
            }
            if(iteracion>30 || x<-10 || x > 560 || y <-30 || y > 400 )
            {
                phase++;
            }
        }
        if(phase==3)
        {
            if(lock_right)
            {
                x+=gainx;
                derecha=true;
            }
            if(lock_left)
            {
                x-=gainx;
                derecha=false;
            }
            if(lock_down)
            {
                y+=gainy;
                arriba=false;
            }
            if(lock_up)
            {
                y-=gainy;
                arriba=true;
            }
            if((x-goalx <20 && y-goaly <20) || x<-10 || x > 560 || y <-30 || y > 400 )
            {
                phase++;
            }
        }
        if(phase==4)
        {
            if(lock_right)
            {
                x-=gainx;
                derecha=false;
            }
            if(lock_left)
            {
                x+=gainx;
                derecha=true;
            }
            if(lock_down)
            {
                y-=gainy;
                arriba=true;
            }
            if(lock_up)
            {
                y+=gainy;
                arriba=false;
            }
            if((x-sourcex <20 && y-sourcey <20) || x<-10 || x > 560 || y <-30 || y > 400)
            {
                phase=0;
                iteracion=0;
                gogeta_crazy=false;
                lock_down=false;
                lock_left=false;
                lock_right=false;
                lock_up=false;
            }
        }
        if(x>560)
            derecha=false;
        if(x<-10)
            derecha=true;
        if(y>400)
            arriba=true;
        if(y<200)
            arriba=false;
    }
    if(!gogeta_crazy)
    {
        if(iteracion > 200)
        {
            iteracion = 0;
            gogeta_crazy = true;
        }
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
        if(y<200)
            arriba=false;
    }
    iteracion++;
}

Gogeta::~Gogeta()
{
    //dtor
}
