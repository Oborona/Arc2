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
    painter->setPen(Qt::green);
    painter->drawLine(center, speedEndPos + center);
    qDebug() << name;
    if (colls.size() > 0)
    {
        qDebug() << "Colls";
        for (int i = 0; i < colls.size(); i++)
            qDebug() << colls[i];
    }

    for (int i = 0; i < colls.size(); i++)
        painter->drawEllipse(colls.at(i) - QPoint(3, 3), 6, 6);

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

int ArcItem::checkCollision(ArcItem *other)
{

////    qDebug() << "checking collisions" << this->name << other->name;
    // to not to collect extra points
    other->clearColls();
    int bx = other->x();
    int by = other->y();
    int bwidth = other->getWidth();
    int bheight = other->getHeight();
//    qDebug() << name << bx << by << "this" << x() << y();

    // If too far -- exit
//    int xDistance = 0;
//    xDistance = qAbs(bx - x());
//    if (xDistance > qAbs(speed.x()))
//        return -1;

//    int yDistance = 0;
//    yDistance = qAbs(by - y());
//    if (yDistance > qAbs(speed.y()))
//        return -1;

    QPoint p;
    // checking rect flanks
    bool ok = false;
    p = linesCross(QPoint(x(), y()), speedEndPos + QPoint(x(), y()), QPoint(bx, by), QPoint(bx, by + bheight), ok);
    qDebug() << "1111" << p << ok << "___" << pos() << speedEndPos + QPoint(x(), y()) << QPoint(bx + bwidth, by) << QPoint(bx + bwidth, by + bheight);
    if (ok == true)
        other->addColl(p);
    return 1;
    p = linesCross(QPoint(x(), y()), speedEndPos + QPoint(x(), y()), QPoint(bx, by), QPoint(bx + bwidth, by), ok);
    if (ok == true)
        other->addColl(p);
    p = linesCross(QPoint(x(), y()), speedEndPos + QPoint(x(), y()), QPoint(bx + bwidth, by), QPoint(bx + bwidth, by + bheight), ok);
    if (ok == true)
        other->addColl(p);
    p = linesCross(QPoint(x(), y()), speedEndPos + QPoint(x(), y()), QPoint(bx, by + bheight), QPoint(bx, by + bheight), ok);
    if (ok == true)
        other->addColl(p);
    return 1;
}

void ArcItem::updateItem()
{
    speedEndPos = speed;
}

void ArcItem::moveItem()
{
    setPos(QPoint(x(), y()) + speed);
}

QPoint linesCross(QPoint p11, QPoint p12, QPoint p21, QPoint p22, bool &ok)
{
    int debug = 0;
    // Line formula of moving item
    float p11x = p11.x(), p11y = p11.y();
    float p12x = p12.x(), p12y = p12.y();
    float p21x = p21.x(), p21y = p21.y();
    float p22x = p22.x(), p22y = p22.y();

    float k1 = (p11y - p12y)/float(p11x - p12x);
    float b1 = (p11x*p12y - p12x*p11y)/float(p11x - p12x);
    float k2 = (p21y - p22y)/float(p21x - p22x);
    float b2 = (p21x*p22y - p22x*p21y)/float(p21x - p22x);

    if (debug) qDebug () << "p1" << k1 << b1;
    if (debug) qDebug () << "p2" << k2 << b2;


    if (k1 == k2)// && b1 != b2) we assume that complete match is very very rare
    {
        ok = false;
        return QPoint(-1, -1);
    }

    if (p11x == p12x)
    {
        int crossy = k2*p12x + b2;
        if (debug) qDebug() << "Crossy:" << QPoint(p12x, crossy);
//        if (debug) qDebug() << p11y << p12y << crossy;
        if (crossy > qMin(p21y, p22y) && crossy < qMax(p21y, p22y))
        {
            ok = true;
            return QPoint(p11.x(), crossy);
        }
        else
        {
            ok = false;
            return QPoint(-1, -1);
        }
    }
    if (p21x == p22x)
    {
        int crossy = k1*p22x + b1;
        if (debug) qDebug() << "Cross:" << QPoint(p22x, crossy);
        if (crossy > qMin(p11y, p12y) && crossy < qMax(p11y, p12y))
        {
            ok = true;
            return QPoint(p21.x(), crossy);
        }
        else
        {
            ok = false;
            return QPoint(-1, -1);
        }
     }

    float cx = float((b2 - b1)/(k1-k2));
    float cy = cx*k1 + b1;
    if (debug) qDebug() << "__X()" << cx << qMin(p11x, p12x) << qMax(p11x, p12x);
    if (debug) qDebug() << "__Y()" << cy << qMin(p11y, p12y) << qMax(p11y, p12y);

    if (cx < qMin(p11x, p12x) || cx > qMax(p11x, p12x) ||
        cy < qMin(p11y, p12y) || cy > qMax(p11y, p12y))
    {
        ok = false;
        return QPoint(-1, -1);
    }


    QPoint res;
    res.setX(cx);
    res.setY(cy);
    ok = true;
    return res;
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
