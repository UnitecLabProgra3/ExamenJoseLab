#ifndef KAIYO_H
#define KAIYO_H

#include "Enemigo.h"

class Kaiyo : public Enemigo
{
    public:
        Kaiyo();
        bool round;
        void logic();
        virtual ~Kaiyo();
    protected:
    private:
};

#endif // KAIYO_H
