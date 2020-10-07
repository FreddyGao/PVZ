#include "mainwindow.h"
#include"mypushbutton.h"
#include<QPixmap>
#include<QSound>
#include<QPushButton>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
    sound = new QSound(":/res/Laura Shigihara - Grasswalk IN-GAME.wav");
    sound->setLoops(QSound::Infinite);
    timer = new QTimer;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(225, 0, 1350, 900);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);//如果你的场景中使用了很多动画，可以禁用下标
    Shop *shop = new Shop;
    shop->setPos(780, 67.5);
    scene->addItem(shop);
    Shovel *shovel = new Shovel;
    shovel->setPos(1245, 60);
    scene->addItem(shovel);
    Button *button = new Button(sound, timer);
    //Button *sButton=new Button(sound,timer);
    saveButton *sButton=new saveButton (sound,timer);
    sButton->setPos(1455,100);
    button->setPos(1455, 30);
    //返回按钮
    //    MyPushButton *fourthchoosebutton=new MyPushButton(":/res/close2.png",":/res/close1.png");
    //    fourthchoosebutton->setParent(this);
    //    fourthchoosebutton->move(500,500);
    //    fourthchoosebutton->setWindowFlags(Qt::WindowStaysOnTopHint);
    scene->addItem(sButton);
    scene->addItem(button);
    Map *map = new Map;
    map->setPos(927, 489);
    scene->addItem(map);
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
        if (type < 30)
            zombie = new BasicZombie;
        else if (type < 50)
            zombie = new JackinTheBoxZombie;
        else if( type< 60 )
            zombie=new SnowZombie;
        else if (type < 70)
            zombie = new ConeZombie;
        else if (type < 80)
            zombie = new BucketZombie;
        else if (type < 90)
            zombie = new ScreenZombie;
        else
            zombie = new FootballZombie;
        zombie->setPos(1028*1.5, 130*1.5 + 98*1.5 * i);
        scene->addItem(zombie);
        //this->putZombie(zombie);
    }
}
void MainWindow::putZombie(Zombie* z){
    this->zBox.push_back(z);
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
