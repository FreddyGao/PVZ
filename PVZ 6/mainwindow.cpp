#include "mainwindow.h"
#include"mypushbutton.h"
#include<QPixmap>
#include<QSound>
#include<QPushButton>
#include<QDebug>
#include"fstream"
using namespace std;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
    sound = new QSound(":/res/Laura Shigihara - Grasswalk IN-GAME.wav");
    sound->setLoops(QSound::Infinite);
    timer = new QTimer;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(225, 0, 1350, 900);
    Shop* shop = new Shop;
    shop->setPos(780, 67.5);
    scene->addItem(shop);
    Shovel *shovel = new Shovel;
    shovel->setPos(1245, 60);
    scene->addItem(shovel);
    this->bt=new Button(sound,timer);
    this->bt->setPos(1455, 30);
    this->bt->setShop(shop);
    Map *map = new Map;
    map->setPos(927, 489);
    scene->addItem(map);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);//如果你的场景中使用了很多动画，可以禁用下标
   /*string path="/Users/gaofei/Desktop/stat/2.txt";
    ifstream mcfile; //创建个对象
    mcfile.open("/Users/gaofei/Desktop/stat/2.txt"); //创建文件
    int num;
    mcfile>>num;
    int hp,atk;
    int type;
    qreal speed;
    double xP,yP;
    for(int i=0;i<num;i++){
        mcfile>>hp;
        mcfile>>atk;
        mcfile>>speed;
        mcfile>>xP;
        mcfile>>yP;
        mcfile>>type;
         if(type==0&&hp!=0){
        Zombie* zombie = new BasicZombie(hp,atk,speed);
         zombie->setPos(xP, yP);
         scene->addItem(zombie);
        }
        if(type==1&&hp!=0){
           Zombie* zombie=new BucketZombie(hp,atk,speed);
          zombie->setPos(xP,yP);
          scene->addItem(zombie);
        }
        if(type==2&&hp!=0){
             Zombie* zombie=new ConeZombie(hp,atk,speed);
            zombie->setPos(xP,yP);
            scene->addItem(zombie);
        }
        if(type==3&&hp!=0){
            Zombie* zombie=new FootballZombie(hp,atk,speed);
            zombie->setPos(xP,yP);
            scene->addItem(zombie);
        }
        if(type==4&&hp!=0){
             Zombie* zombie=new JackinTheBoxZombie(hp,atk,speed);
            zombie->setPos(xP,yP);
            scene->addItem(zombie);
        }
        if(type==5&&hp!=0){
             Zombie* zombie=new SnowZombie(hp,atk,speed);
            zombie->setPos(xP,yP);
            scene->addItem(zombie);
        }
    }
    int ss;
    mcfile>>ss;
    int state;
     QPointF pos;
    for(int i=0;i<ss;i++){
        mcfile>>hp;
        mcfile>>state;
        mcfile>>atk;
        mcfile>>num;
        mcfile>>xP;
        mcfile>>yP;
        if(num==0&&hp!=0){
           Plant* plant=new SunFlower(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==1&&hp!=0){
           Plant* plant=new Peashooter(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==2&&hp!=0){
           Plant* plant=new CherryBomb(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==3&&hp!=0){
           Plant* plant=new WallNut(hp);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==4&&hp!=0){
           Plant* plant=new SnowPea(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==5&&hp!=0){
           Plant* plant=new PotatoMine(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==6&&hp!=0){
           Plant* plant=new Repeater(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
    }
 */


    //返回按钮
    //    MyPushButton *fourthchoosebutton=new MyPushButton(":/res/close2.png",":/res/close1.png");
    //    fourthchoosebutton->setParent(this);
    //    fourthchoosebutton->move(500,500);
    //    fourthchoosebutton->setWindowFlags(Qt::WindowStaysOnTopHint);

    scene->addItem(this->bt);

    for (int i = 0; i < 5; ++i)//放置最左边五个铲车
    {
        Mower *mower = new Mower;
        mower->setPos(315, 195 + 147 * i);
        scene->addItem(mower);
    }
    view = new QGraphicsView(scene, this);
    view->resize(1352, 902);
    view->setRenderHint(QPainter::Antialiasing);//绘图抗锯齿设置
    QPixmap pix;
    bool ret=pix.load(":/images/Background.jpg");
    if(!ret)
        qDebug()<<"加载图片失败";
    pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
//    view->setBackgroundBrush(QPixmap(":/images/Background.jpg"));
    view->setBackgroundBrush(pix);
    view->setCacheMode(QGraphicsView::CacheBackground);//设置缓存背景模式
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);
    connect(timer, &QTimer::timeout, this, &MainWindow::check);
    sound->play();
    timer->start(33);
    view->show();
}
MainWindow::MainWindow(string path,QWidget* parent): QMainWindow(parent){
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
    sound = new QSound(":/res/Laura Shigihara - Grasswalk IN-GAME.wav");
    sound->setLoops(QSound::Infinite);
    timer = new QTimer;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(225, 0, 1350, 900);
    Shop* shop = new Shop;
    shop->setPos(780, 67.5);
    scene->addItem(shop);
    Shovel *shovel = new Shovel;
    shovel->setPos(1245, 60);
    scene->addItem(shovel);
    this->bt=new Button(sound,timer);
    this->bt->setPos(1455, 30);
    this->bt->setShop(shop);
    Map *map = new Map;
    map->setPos(927, 489);
    scene->addItem(map);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);//如果你的场景中使用了很多动画，可以禁用下标
   //string path="/Users/gaofei/Desktop/stat/2.txt";
    ifstream mcfile; //创建个对象
    mcfile.open(path); //创建文件
    int num;
    mcfile>>num;
    int hp,atk;
    int type;
    qreal speed;
    double xP,yP;
    for(int i=0;i<num;i++){
        mcfile>>hp;
        mcfile>>atk;
        mcfile>>speed;
        mcfile>>xP;
        mcfile>>yP;
        mcfile>>type;
         if(type==0&&hp!=0){
        Zombie* zombie = new BasicZombie(hp,atk,speed);
         zombie->setPos(xP, yP);
         scene->addItem(zombie);
        }
        if(type==4&&hp!=0){
           Zombie* zombie=new BucketZombie(hp,atk,speed);
          zombie->setPos(xP,yP);
          scene->addItem(zombie);
        }
        if(type==3&&hp!=0){
             Zombie* zombie=new ConeZombie(hp,atk,speed);
            zombie->setPos(xP,yP);
            scene->addItem(zombie);
        }
        if(type==6&&hp!=0){
            Zombie* zombie=new FootballZombie(hp,atk,speed);
            zombie->setPos(xP,yP);
            scene->addItem(zombie);
        }
        if(type==1&&hp!=0){
             Zombie* zombie=new JackinTheBoxZombie(hp,atk,speed);
            zombie->setPos(xP,yP);
            scene->addItem(zombie);
        }
        if(type==2&&hp!=0){
             Zombie* zombie=new SnowZombie(hp,atk,speed);
            zombie->setPos(xP,yP);
            scene->addItem(zombie);
        }
        if(type==5&&hp!=0){
             Zombie* zombie=new ScreenZombie(hp,atk,speed);
            zombie->setPos(xP,yP);
            scene->addItem(zombie);
        }
    }
    int ss;
    mcfile>>ss;
    int state;
     QPointF pos;
    for(int i=0;i<ss;i++){
        mcfile>>hp;
        mcfile>>state;
        mcfile>>atk;
        mcfile>>num;
        mcfile>>xP;
        mcfile>>yP;
        if(num==0&&hp!=0){
           Plant* plant=new SunFlower(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==1&&hp!=0){
           Plant* plant=new Peashooter(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==2&&hp!=0){
           Plant* plant=new CherryBomb(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==3&&hp!=0){
           Plant* plant=new WallNut(hp);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==4&&hp!=0){
           Plant* plant=new SnowPea(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==5&&hp!=0){
           Plant* plant=new PotatoMine(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
        if(num==6&&hp!=0){
           Plant* plant=new Repeater(hp,atk);
           pos.setX(xP);
           pos.setY(yP);
           plant->setPos(pos);
           scene->addItem(plant);
        }
    }
    mcfile>>shop->sun;



    //返回按钮
    //    MyPushButton *fourthchoosebutton=new MyPushButton(":/res/close2.png",":/res/close1.png");
    //    fourthchoosebutton->setParent(this);
    //    fourthchoosebutton->move(500,500);
    //    fourthchoosebutton->setWindowFlags(Qt::WindowStaysOnTopHint);

    scene->addItem(this->bt);

    for (int i = 0; i < 5; ++i)//放置最左边五个铲车
    {
        Mower *mower = new Mower;
        mower->setPos(315, 195 + 147 * i);
        scene->addItem(mower);
    }
    view = new QGraphicsView(scene, this);
    view->resize(1352, 902);
    view->setRenderHint(QPainter::Antialiasing);//绘图抗锯齿设置
    QPixmap pix;
    bool ret=pix.load(":/images/Background.jpg");
    if(!ret)
        qDebug()<<"加载图片失败";
    pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
//    view->setBackgroundBrush(QPixmap(":/images/Background.jpg"));
    view->setBackgroundBrush(pix);
    view->setCacheMode(QGraphicsView::CacheBackground);//设置缓存背景模式
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);
    connect(timer, &QTimer::timeout, this, &MainWindow::check);
    sound->play();
    timer->start(33);
    view->show();
}
MainWindow::~MainWindow()
{
    delete sound;
    delete timer;
    delete scene;
    delete view;
}

void MainWindow::addZombie()//随机生成僵尸
{
    static int low = 4;
    static int high = 8;
    static int maxtime = 20 * 1000 / 33;
    static int time = maxtime / 2;
    static int counter = 0;
    if (++counter >= time)
    {
        if (++low > high)
        {
            maxtime /= 1.3;
            high *= 2;
        }
        counter = 0;
        time = qrand() % (2 * maxtime / 3) + maxtime / 3;
        int type = qrand() % 100;
        int i = qrand() % 5;
        Zombie *zombie;
        if (type < 30){
         zombie = new BasicZombie;
         zombie->setNum(0);}
         else if (type < 50){
           zombie = new JackinTheBoxZombie;
                    zombie->setNum(1);}
                else if( type< 60 ){
                    zombie=new SnowZombie;
                    zombie->setNum(2);}
                else if (type < 70){
                    zombie = new ConeZombie;
                    zombie->setNum(3);}
                else if (type < 80){
                    zombie = new BucketZombie;
                    zombie->setNum(4);}
                else if (type < 90){
                    zombie = new ScreenZombie;
                    zombie->setNum(5);}
                else{
                    zombie = new FootballZombie;
                    zombie->setNum(6);}
        zombie->setXP(1028*1.5);
        zombie->setYP(130*1.5 + 98*1.5 * i);
        zombie->setPos(1028*1.5, 130*1.5 + 98*1.5 * i);
        this->bt->addZombie(zombie);
        scene->addItem(zombie);
    }
}

void MainWindow::check()//判断是否胜利
{
    static int time = 1 * 1000 / 33;
    static int counter = 0;
    if (++counter >= time)
    {
        counter = 0;
        const QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items)//for each 遍历每一项
            if (item->type() == Zombie::Type && item->x() < 250)//僵尸坐标到达铲车左边，游戏失败
            {
                QPixmap pix(":/images/ZombiesWon.png");
                pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
                scene->addPixmap(pix)->setPos(336, 92);
                scene->advance();
                timer->stop();
                return;
            }
    }
}
