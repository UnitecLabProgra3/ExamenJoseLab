#ifndef GOGETA_H
#define GOGETA_H

#include "Enemigo.h"
#include <cmath>

class Gogeta : public Enemigo
{
    public:
        Gogeta(Personaje*player);
        Personaje*player;
        int goalx, goaly, sourcex, sourcey, phase, gainx, gainy;
        bool gogeta_crazy, lock_left, lock_right, lock_up, lock_down;
        void logic();
        virtual ~Gogeta();
    protected:
    private:
};

#endif // GOGETA_H
