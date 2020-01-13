#include "arcitem.h"

ArcItem::ArcItem()
{
   kinematic = false;
}

void ArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect());

    if (isKinematic())
    {
        painter->setBrush(Qt::darkBlue);
        painter->drawEllipse(boundingRect());
    }

    // for debug
    painter->setBrush(Qt::red);
    int dotsize = 6;
    for (int i = 0; i < debugColl.size(); i++)
    {
        QPoint top = debugColl[i].top;
        QPoint left = debugColl[i].left;
        QPoint right = debugColl[i].right;
        QPoint bottom = debugColl[i].bottom;
        painter->drawEllipse(top.x()    - pos().x() - dotsize/2, top.y()    - pos().y() - dotsize/2, dotsize, dotsize);
        painter->drawEllipse(left.x()   - pos().x() - dotsize/2, left.y()   - pos().y() - dotsize/2, dotsize, dotsize);
        painter->drawEllipse(right.x()  - pos().x() - dotsize/2, right.y()  - pos().y() - dotsize/2, dotsize, dotsize);
        painter->drawEllipse(bottom.x() - pos().x() - dotsize/2, bottom.y() - pos().y() - dotsize/2, dotsize, dotsize);
    }
    painter->setPen(Qt::green);
    painter->drawLine(width/2, height/2, width/2 + speed.x()*10, height/2 + speed.y()*10);
}

QRectF ArcItem::boundingRect() const
{
    return QRect(0, 0, width, height);
}


void ArcItem::updateItem()
{
    if (isKinematic())
        this->setPos(pos() + speed);
//    this->clearDebugColl();

//    restSpeed = speed;
//    //position += speed;
//    newPosition = position;
}

void ArcItem::invertSpeed(int dir)
{

}
