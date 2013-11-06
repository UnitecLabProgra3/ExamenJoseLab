#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <string>
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Personaje.h"

class Enemigo
{
    public:
        int x,y, iteracion, frame;
        bool izquierda, derecha, arriba, abajo;
        std::vector<SDL_Surface*> sprites;
        Enemigo();
        virtual void dibujar(SDL_Surface*screen);
        virtual void logic();
        virtual bool collision_logic(Personaje *player);
        virtual ~Enemigo();
    protected:
    private:
};

#endif // ENEMIGO_H
