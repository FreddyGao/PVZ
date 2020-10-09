#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "plant.h"
#include "sun.h"

class SunFlower : public Plant
{
public:
    SunFlower();
    SunFlower(int hk,int atk);
    void advance(int phase) override;
};

#endif // SUNFLOWER_H
