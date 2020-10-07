#include "basiczombie.h"

BasicZombie::BasicZombie()
{
    hp = 270;   //血量
    atk = 100 * 33 / 1000;   //攻击力
    speed = 80.0 * 33 / 1000 / 4.7*1.5; //速度
    if (qrand() % 2)
        setMovie(":/images/ZombieWalk1.gif");
    else
        setMovie(":/images/ZombieWalk2.gif");
}

void BasicZombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    //僵尸死亡
    if (hp <= 0)     //hp记录
    {
        if (state < 2)
        {
            state = 2;
            setMovie(":/images/ZombieDie.gif");
            setHead(":/images/ZombieHead.gif");
        }
        else if (movie->currentFrameNumber() == movie->frameCount() - 1)
            delete this;
        return;
    }
    //吃植物，先进行碰撞检测
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        //攻击植物,记录  planthp
        Plant *plant = qgraphicsitem_cast<Plant *>(items[0]);
        plant->hp -= atk;
        if (state != 1)
        {
            state = 1;
            setMovie(":/images/ZombieAttack.gif");
        }
        return;
    }
    //行走状态
    if (state) //记录state
    {
        state = 0;
        if (qrand() % 2)
            setMovie(":/images/ZombieWalk1.gif");
        else
            setMovie(":/images/ZombieWalk2.gif");
    }
    //僵尸前进 记录x
    setX(x() - speed);
}
