#ifndef SNOWZOMBIE_H
#define SNOWZOMBIE_H
#include "zombie.h"
#include "plant.h"

class SnowZombie:public Zombie
{
public:
    SnowZombie();
    void advance(int phase) override;
};

#endif // SNOWZOMBIE_H
