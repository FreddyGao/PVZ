#include "mypushbutton.h"

MyPushButton::MyPushButton(QString normalImg, QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    QPixmap pixmap;
    bool ret=pixmap.load(normalImgPath);
    if(!ret){
        qDebug()<<"加载图片失败！";
    }
    //设置不规则按钮和图片的固定尺寸
    pixmap=pixmap.scaled(pixmap.width()*0.22,pixmap.height()*0.22);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pressImgPath!="")
    {
        QPixmap pixmap;
        bool ret=pixmap.load(pressImgPath);
        if(!ret)
            qDebug()<<pressImgPath<<"加载图片失败";
        pixmap=pixmap.scaled(pixmap.width()*0.22,pixmap.height()*0.22);
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    return QPushButton::mousePressEvent(e);
}


void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(pressImgPath!="")
    {
        QPixmap pixmap;
        bool ret=pixmap.load(normalImgPath);
        if(!ret)
            qDebug()<<normalImgPath<<"加载图片失败";
        pixmap=pixmap.scaled(pixmap.width()*0.22,pixmap.height()*0.22);
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
