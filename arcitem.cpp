#include "arcitem.h"

const int DOTSIZE = 4;

ArcItem::ArcItem()
{
   kinematic = false;
}

void ArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setPen(Qt::black);
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect());

    if (isKinematic())
    {
        painter->setBrush(Qt::darkBlue);
        painter->drawEllipse(boundingRect());
        painter->setPen(Qt::green);
        painter->drawLine(center, speed + center);
    }

    if (colls.size() > 0)
    {
        painter->setBrush(Qt::darkRed);
        for (int i = 0; i < colls.size(); i++)
            painter->drawEllipse(colls.at(i) - QPoint(int(x()), int(y())), DOTSIZE, DOTSIZE);

    }
    painter->setBrush(Qt::blue);
    painter->drawEllipse(speedEdge - pos(), DOTSIZE, DOTSIZE);

    if (isKinematic())
    {
        QPen pen;
        pen.setStyle(Qt::DotLine);
        pen.setColor(Qt::black);
        painter->setPen(pen);
        painter->setBrush(Qt::transparent);
        painter->drawRect(speedEnd.x(), speedEnd.y(), width, height);

        painter->setPen(Qt::magenta);
        painter->drawLine(center, speedEdge + center);
        painter->setPen(Qt::yellow);
        painter->drawLine(speedEdge + center, speedEnd + center);

    }
//    painter->drawLine(speedEdge, speedEnd);

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
    int bx = int(other->x());
    int by = int(other->y());
    int bwidth = other->getWidth();
    int bheight = other->getHeight();

    {
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
    }

    QPoint center(int(x() + width/2), int(y() + height/2));
    QPoint p;
    // checking rect flanks
    bool ok = false;
    p = linesCross(center, speedEnd + center, QPoint(bx, by), QPoint(bx, by + bheight), ok);
    if (ok == true)
        other->addColl(p);
    p = linesCross(center, speedEnd + center, QPoint(bx, by), QPoint(bx + bwidth, by), ok);
    if (ok == true)
        other->addColl(p);
    p = linesCross(center, speedEnd + center, QPoint(bx + bwidth, by), QPoint(bx + bwidth, by + bheight), ok);
    if (ok == true)
        other->addColl(p);
        qDebug() << "p:" << p;
    p = linesCross(center, speedEnd + center, QPoint(bx, by + bheight), QPoint(bx, by + bheight), ok);
    if (ok == true)
        other->addColl(p);

    if (!other->colls.isEmpty())
        calcSpeedEnd(other);
    else
    {
        speedEnd = speed;
        speedEdge = speedEnd;
    }


    return 1;
}

void ArcItem::calcSpeedEnd(ArcItem *other)
{
    double distance = -1;
    QPoint fin;
    for (int i = 0; i < other->getColls()->size(); i++)
    {
        double d = vectorLength(other->getColls()->at(i), this->center);
        if (i == 0)
        {
            distance = d;
            fin = other->getColls()->at(i);
        }
        if (d < distance)
        {
            distance = d;
            fin = other->getColls()->at(i);
        }
    }
    speedEdge = fin - QPoint(int(x()), int(y())) - center;

    if (other->collSide(fin) == SIDE_RIGHT)
    {

        int diff = abs(speed.x()) - abs(speedEdge.x());
//        qDebug() << "diff:" << diff;
        if (speed.y() == 0)
        {
            speedEnd.setX(speedEdge.x());
            speedEnd.setY(speedEdge.y());
        }
        else
        {
            float coef = qAbs(speed.x()/speed.y());
            speedEnd.setX(speedEdge.x() + diff);
            speedEnd.setY(speedEdge.y() + int(speed.y()/coef));
        }
        speed.setX(-speed.x());

    }
    if (other->collSide(fin) == SIDE_LEFT)
    {
        int diff = abs(speed.x()) - abs(speedEdge.x());
        qDebug() << "diff:" << diff;
        if (speed.y() == 0)
        {
            speedEnd.setX(speedEdge.x());
            speedEnd.setY(speedEdge.y());
        }
        else
        {
            float coef = qAbs(speed.x()/speed.y());
            speedEnd.setX(speedEdge.x() + diff);
            speedEnd.setY(speedEdge.y() + int(speed.y()/coef));
        }
    }
//    qDebug() << "Distance:" << distance << "Point:" << fin;

}

void ArcItem::updateItem()
{
    speedEnd = speed;
    speedEdge = speed;
}

void ArcItem::moveItem()
{
    if (isKinematic())
        setPos(speedEnd + QPoint(int(x()), int(y())));
//    setPos(QPoint(int(x()), int(y())) + speed);
}

int ArcItem::collSide(QPoint p)
{
    if (p.x() == int(x()) + width)
        return SIDE_RIGHT;
    if (p.x() == int(this->x()))
        return SIDE_LEFT;
    if (p.y() == int(this->y()) + height)
        return SIDE_BOTTOM;
    if (p.y() == int(this->y()))
        return SIDE_TOP;
    return -1;
}

//int

double vectorLength(QPoint p1, QPoint p2)
{
    int x = p1.x() - p2.x();
    int y = p1.y() - p2.y();
    return qSqrt(x*x + y*y);
}

QPoint linesCross(QPoint p11, QPoint p12, QPoint p21, QPoint p22, bool &ok)
{
    int debug = 0;
    // Line formula of moving item
    int p11x = p11.x(), p11y = p11.y();
    int p12x = p12.x(), p12y = p12.y();
    int p21x = p21.x(), p21y = p21.y();
    int p22x = p22.x(), p22y = p22.y();

    float k1 = (p11y - p12y)/float(p11x - p12x);
    float b1 = (p11x*p12y - p12x*p11y)/float(p11x - p12x);
    float k2 = (p21y - p22y)/float(p21x - p22x);
    float b2 = (p21x*p22y - p22x*p21y)/float(p21x - p22x);

    if (debug) qDebug () << "p1" << "k1, b1 =" << k1 << b1;
    if (debug) qDebug () << "p2" << "k2, b2 =" << k2 << b2;

    // Got some glitch with horizontal speed, but it's may be impossible

    if (int(k1) == int(k2))// && b1 != b2) we assume that complete match is very very rare
    {
        ok = false;
        return QPoint(-1, -1);
    }

    if (p11x == p12x)
    {
        float crossy = k2*p12x + b2;
        if (debug) qDebug() << "Crossy (1-vertical):" << QPoint(p12x, int(crossy));
        if (debug) qDebug() << "miny, maxy:" << qMin(p21y, p22y) << qMax(p21y, p22y);
        if (crossy >= qMin(p21y, p22y) && crossy <= qMax(p21y, p22y))
        {
            ok = true;
            return QPoint(p11.x(), int(crossy));
        }
        else
        {
            ok = false;
            return QPoint(-1, -1);
        }
    }
    if (p21x == p22x)
    {
        float crossy = k1*p22x + b1;
        if (debug) qDebug() << "Crossy (2-vertical):" << QPoint(p22x, int(crossy));
        if (crossy >= qMin(p11y, p12y) && crossy <= qMax(p11y, p12y))
        {
            ok = true;
            return QPoint(p21.x(), int(crossy));
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
    res.setX(int(cx));
    res.setY(int(cy));
    ok = true;
    return res;
}

