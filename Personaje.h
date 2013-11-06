#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <vector>
#include <string>
using namespace std;


class Personaje
{
    public:
        Personaje(int x, int y);
        int current_frame;
        int current_iteration;
        int x;
        int y;
        vector <SDL_Surface*>personaje;
        bool in_battle;
        bool moving;
        virtual void logic();
        void dibujar(SDL_Surface*screen);
        virtual ~Personaje();
    protected:
    private:
};

#endif // PERSONAJE_H
