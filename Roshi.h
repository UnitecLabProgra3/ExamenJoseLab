#ifndef ROSHI_H
#define ROSHI_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <vector>
#include <string>
#include "Personaje.h"
using namespace std;

class Roshi
{
    public:
        Roshi(int x, int y);
        int x, y, frame, iteration;
        vector <SDL_Surface*>roshi_sprite;
        void dibujar(SDL_Surface*screen);
        bool collision_logic(Personaje *player);
        virtual ~Roshi();
    protected:
    private:
};

#endif // ROSHI_H
