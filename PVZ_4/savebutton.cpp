#include "savebutton.h"

saveButton::saveButton(QSound *s,QTimer *t)
{
    sound = s;
    timer = t;
}
QRectF saveButton::boundingRect() const
{
    return QRectF(-120, -30, 240, 60);
}
void saveButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPixmap pix(":/images/Button.png");
    pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
    painter->drawPixmap(QRect(-120, -30, 240, 60), pix);
    painter->setPen(Qt::white);
    QFont font("Calibri", 27, QFont::Bold, true);
    painter->setFont(font);
    painter->drawText(boundingRect(), Qt::AlignCenter, "Save");
    update();
}

void saveButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //控制全局计时器的开启与关闭
    if (event->button() == Qt::LeftButton)
    {
        if (timer->isActive())
        {
            sound->stop();
            timer->stop();
        }
        else
        {
            sound->play();
            timer->start();
        }
    }
    update();
}
