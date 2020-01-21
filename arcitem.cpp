#include "arcitem.h"

ArcItem::ArcItem()
{
   kinematic = false;
   speedEndPos.setX(pos().x());
   speedEndPos.setY(pos().y());
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
    qDebug() << name << boundingRect() << pos() << speedEndPos;
    painter->setPen(Qt::green);
    painter->drawLine(center, speedEndPos + center);


    if (isKinematic())
    {
        QPen pen;
        pen.setStyle(Qt::DotLine);
        pen.setColor(Qt::black);
        painter->setPen(pen);
        painter->setBrush(Qt::transparent);
        painter->drawRect(speedEndPos.x(), speedEndPos.y(), width, height);
    }
}

QRectF ArcItem::boundingRect() const
{
    return QRect(0, 0, width, height);
}

int ArcItem::checkCollision(QRectF coords)
{
    int xDistance = 0;
    xDistance = qAbs(coords.x() - x()) - width;
    if (xDistance > qAbs(speed.x()))
        return -1;

    int yDistance = 0;
    yDistance = qAbs(coords.y() - y()) - height;
    if (yDistance > qAbs(speed.y()))
        return -1;
}

void ArcItem::updateItem()
{
    speedEndPos = speed;
}

void ArcItem::moveItem()
{
    setPos(QPoint(x(), y()) + speed);
}
//void ArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    Q_UNUSED(option);
//    Q_UNUSED(widget);
//    painter->setPen(Qt::black);
//    painter->setBrush(Qt::blue);
//    painter->drawRect(boundingRect());

//    if (isKinematic())
//    {
//        painter->setBrush(Qt::darkBlue);
//        painter->drawEllipse(boundingRect());
//    }

//    // for debug
//    painter->setBrush(Qt::red);
//    int dotsize = 6;
//    for (int i = 0; i < debugColl.size(); i++)
//    {
//        QPoint top = debugColl[i].points[SIDE_TOP];
//        QPoint left = debugColl[i].points[SIDE_LEFT];
//        QPoint right = debugColl[i].points[SIDE_RIGHT];
//        QPoint bottom = debugColl[i].points[SIDE_BOTTOM];
//        painter->drawEllipse(top.x()    - pos().x() - dotsize/2, top.y()    - pos().y() - dotsize/2, dotsize, dotsize);
//        painter->drawEllipse(left.x()   - pos().x() - dotsize/2, left.y()   - pos().y() - dotsize/2, dotsize, dotsize);
//        painter->drawEllipse(right.x()  - pos().x() - dotsize/2, right.y()  - pos().y() - dotsize/2, dotsize, dotsize);
//        painter->drawEllipse(bottom.x() - pos().x() - dotsize/2, bottom.y() - pos().y() - dotsize/2, dotsize, dotsize);
//    }

//    painter->setPen(Qt::green);
////    painter->drawLine(width/2, height/2, width/2 + speed.x()*10, height/2 + speed.y()*10);
//    painter->drawLine(QPoint(width/2, height/2), speedEdgePos);
//    painter->drawLine(speedEdgePos, speedEndPos);
//    painter->setBrush(Qt::darkGreen);
//    painter->drawEllipse(speedEndPos, dotsize/2, dotsize/2);

//    // Future pos
////    QPen pen;
////    pen.setColor(Qt::black);
////    pen.setStyle(Qt::DotLine);
////    painter->drawRect(speedEndPos.x()-width/2, speedEndPos.y()-width/2, width, height);


//}

//QRectF ArcItem::boundingRect() const
//{
//    return QRect(0, 0, width, height);
//}


//void ArcItem::updateItem()
//{
//    if (isKinematic())
//    {
//        newPos = speed + QPoint(this->x(), this->y());
//        this->setPos(newPos);
//    }
//}

//void ArcItem::calcSpeedPoints()
//{
//    // parts of speed before and after collision
//    QPoint vecBefore;
//    QPoint vecAfter;
//    for (int i = 0; i < debugColl.size(); i++)
//    {
//        for (int j = 0; j < 4; j++)
//        {
//            QPoint p = debugColl.at(i).points[j];
////            int length = ;
//        }
//    }
//}

//int ArcItem::collIsInRect(QRectF borders)
//{
//    for (int i = 0; i < debugColl.size(); i++)
//    {
//        if (borders.contains(debugColl.at(i).points[SIDE_TOP]))
//            return HORIZONTAL;
//        if (borders.contains(debugColl.at(i).points[SIDE_BOTTOM]))
//            return HORIZONTAL;
//        if (borders.contains(debugColl.at(i).points[SIDE_LEFT]))
//            return VERTICAL;
//        if (borders.contains(debugColl.at(i).points[SIDE_RIGHT]))
//            return VERTICAL;
//    }
//    return -1;
//}

//void ArcItem::invertSpeed(int dir)
//{
//    if (dir == VERTICAL)
//        speed.setX(-speed.x());
//    if (dir == HORIZONTAL)
//        speed.setY(-speed.y());
//}
