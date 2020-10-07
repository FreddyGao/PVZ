#include "zombievector.h"

zombieVector::zombieVector()
{

}
void zombieVector::addZombie(Zombie* z){
    this->zBox.push_back(z);
}
