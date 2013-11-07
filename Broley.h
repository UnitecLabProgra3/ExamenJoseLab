#ifndef BROLEY_H
#define BROLEY_H

#include "Enemigo.h"

class Broley : public Enemigo
{
    public:
        Broley();
        bool moving;
        virtual ~Broley();
        bool collision_logic(Personaje* player);
        void logic();
        void dibujar(SDL_Surface*screen);
    protected:
    private:
};

#endif // BROLEY_H
