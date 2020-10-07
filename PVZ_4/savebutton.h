#ifndef SAVEBUTTON_H
#define SAVEBUTTON_H
#include<other.h>
#include<QTimer>
#include<QSound>
class saveButton : public Other
{
public:
    saveButton(QSound *s,QTimer *t);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QSound *sound;
    QTimer *timer;//全局的计时器
};

#endif // SAVEBUTTON_H


