#ifndef ZOMBIEVECTOR_H
#define ZOMBIEVECTOR_H
#include<zombie.h>
#include<vector>
using namespace std;
class zombieVector
{
public:
    zombieVector();
    vector <Zombie*> zBox;
    void addZombie(Zombie*);
};

#endif // ZOMBIEVECTOR_H
