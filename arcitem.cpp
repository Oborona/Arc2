#include "arcitem.h"

ArcItem::ArcItem()
{
    setHp(10);
}

void ArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if (!gotSetting("Kinematic"))
    {
        if (gotSetting("Indestructible"))
        {
            painter->setPen(Qt::black);
            painter->setBrush(Qt::green);
            painter->drawRect(boundingRect());
        }
        else
        {
            QColor col;
            col.setRgb(155-10*hp, 155-10*hp, 255);
            painter->setPen(Qt::black);
            painter->setBrush(col);
            painter->drawRect(boundingRect());

        }
        QPen pen;
        pen.setStyle(Qt::DotLine);
        pen.setColor(Qt::black);
        painter->setPen(pen);
        painter->setBrush(Qt::transparent);
        painter->drawRect(width, 0, 5, height);
        painter->drawRect(-5, 0, 5, height);
        painter->drawRect(0, -5, width, 5);
        painter->drawRect(0, height, width, 5);
    }
    if (gotSetting("Kinematic"))
    {
        painter->setBrush(Qt::darkBlue);
        painter->drawEllipse(boundingRect());
        painter->setPen(Qt::green);
        painter->drawLine(center, speed + center);

        QPen pen;
        pen.setStyle(Qt::DotLine);
        pen.setColor(Qt::black);
        painter->setPen(pen);
        painter->setBrush(Qt::transparent);
        painter->drawRect(speedEnd.x(), speedEnd.y(), width, height);

        painter->setPen(Qt::magenta);
        painter->drawLine(center, speedEdge + center);
        painter->setPen(Qt::black);
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
    int ax = int(x());
    int ay = int(y());
    int bx = int(other->x());
    int by = int(other->y());
    int bwidth = other->getWidth();
    int bheight = other->getHeight();
    int diffx = width/2;
    int diffy = height/2;
    int speedLength = int(vectorLength(QPoint(0,0), speed));

    QPoint fieldCenter(ax + diffx, ay + diffy);
    QPoint p;
    bool ok;

    int side = -1;

    if (fieldCenter.x() + speed.x() < bx - diffx || fieldCenter.x() + speed.x() > bx + bwidth + diffx) return  -1;
    if (fieldCenter.y() + speed.y() < by - diffy || fieldCenter.y() + speed.y() > by + bheight + diffy) return  -1;

    if (bx + bwidth/2 + diffx < fieldCenter.x())
    {
        p = linesCross(fieldCenter, speed + fieldCenter, QPoint(bx + diffx + bwidth, by), QPoint(bx + diffx + bwidth, by + bheight), ok);
        if (ok == true && vectorLength(p, fieldCenter) <= speedLength)
            side = SIDE_RIGHT;
    }
    if (bx + bwidth/2 - diffx > fieldCenter.x())
    {
        p = linesCross(fieldCenter, speed + fieldCenter, QPoint(bx - diffx, by), QPoint(bx - diffx, by + bheight), ok);
        if (ok == true && vectorLength(p, fieldCenter) <= speedLength)
            side = SIDE_LEFT;
    }
    if (by + bheight/2 + diffy < fieldCenter.y())
    {
        p = linesCross(fieldCenter, speed + fieldCenter, QPoint(bx, by + diffy + bheight), QPoint(bx + bwidth, by + diffy + bheight), ok);
        if (ok == true && vectorLength(p, fieldCenter) <= speedLength)
            side = SIDE_BOTTOM;
    }
    if (by + bheight/2 - diffy > fieldCenter.y())
    {
        p = linesCross(fieldCenter, speed + fieldCenter, QPoint(bx, by - diffy), QPoint(bx + bwidth, by - diffy), ok);
        if (ok == true && vectorLength(p, fieldCenter) <= speedLength)
            side = SIDE_TOP;
    }

    calcSpeedEnd(other, side);
    return 1;
}

void ArcItem::calcSpeedEnd(ArcItem *other, int side)
{
    int ax = int(x());
    int ay = int(y());
    int bx = int(other->x()); // brick coords
    int by = int(other->y());
    int bwidth = other->getWidth(); // brick size
    int bheight = other->getHeight();
    int diffx = width/2; // halfsize of kinematic
    int diffy = height/2;
    int centerx = ax + diffx;
    int centery = ay + diffy;
    int partx, party; // part of speed after collision
    int collx, colly;

    int sign = speed.y()/abs(speed.y());
    if (side == SIDE_RIGHT)
    {
        float coeff = float(speed.x())/speed.y();
        collx = bx + bwidth + diffx;
        colly = int(centery + (collx - centerx)/coeff);
        qDebug() << other->getName() << coeff << collx << colly << float(ax - collx + diffx);
        speedEdge.setX(collx - centerx);
        speedEdge.setY(colly - centery);

        partx =  (collx - centerx) - speed.x();  //int(x() + diffx) - collx;
        party = int(float(partx)/coeff);
        qDebug() << partx << party;

        speedEnd.setX(speedEdge.x() + partx);
        speedEnd.setY(speedEdge.y() - party);
        speed.setX(-speed.x());
    }
    if (side == SIDE_LEFT)
    {
        float coeff = float(speed.x())/speed.y();
        collx = bx - diffx;
        colly = int(centery + (collx - centerx)/coeff); //-  int((int(x() + diffx) - collx)/coeff);
        qDebug() << other->getName() << coeff << collx << colly << sign;
        speedEdge.setX(collx - centerx);
        speedEdge.setY(colly - centery);

        partx = speed.x() - (collx - centerx);
        party = int(float(partx)/coeff);

        speedEnd.setX(speedEdge.x() - partx);
        speedEnd.setY(speedEdge.y() + party);
        speed.setX(-speed.x());
    }
    if (side == SIDE_BOTTOM)
    {
        float coeff = float(speed.x())/speed.y();
        colly = by + bheight + diffy;
        collx = int(centerx + (colly - centery)*coeff);
        qDebug() << other->getName() << coeff << collx << colly << sign;
        speedEdge.setY(colly - centery);
        speedEdge.setX(collx - centerx);

        party = (colly - centery) - speed.y();
        partx = int(float(party)*coeff);

        speedEnd.setY(speedEdge.y() + party);
        speedEnd.setX(speedEdge.x() - partx);
        speed.setY(-speed.y());
    }
    if (side == SIDE_TOP)
    {
        float coeff = float(speed.x())/speed.y();
        colly = by - diffy;
        collx = int(centerx + (colly-centery)*coeff);
        qDebug() << other->getName() << coeff << collx << colly << sign;
        speedEdge.setY(colly - centery);
        speedEdge.setX(collx - centerx);

        party = (colly - centery) - speed.y();
        partx = int(float(party)*coeff);

        speedEnd.setY(speedEdge.y() + party);
        speedEnd.setX(speedEdge.x() - partx);
        speed.setY(-speed.y());
    }

}

void ArcItem::updateItem()
{
    if (hp == 0) this->hide();
}

void ArcItem::moveItem()
{
    if (gotSetting("Kinematic"))
        setPos(speedEnd + QPoint(int(x()), int(y())));
    speedEnd = speed;
    speedEdge = speed;
}

void ArcItem::interact(ArcItem *other)
{
    if (!other->gotSetting("Indestructible"))
    {
        qDebug() << "Damaged" << other->getName();
        other->damage(1);
    }
}

bool ArcItem::gotSetting(QString str)
{
    if (settings.contains(str))
        return true;
    else
        return false;
}

int ArcItem::addSetting(QString str)
{
    if (!settings.contains(str))
    {
        settings.append(str);
        return 0;
    }
    else
        return -1;
}

int ArcItem::removeSetting(QString str)
{
    return settings.removeAll(str);
}

void ArcItem::damage(int d)
{
    hp -= d;
    if (hp < 0) hp = 0;
}

double vectorLength(QPoint p1, QPoint p2)
{
    int x = qMax(p1.x(), p2.x()) - qMin(p1.x(), p2.x());
    int y = qMax(p1.y(), p2.y()) - qMin(p1.y(), p2.y());
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

    if (int(k1*100) == int(k2*100))// && b1 != b2) we assume that complete match is very very rare
    {
        ok = false;
        return QPoint(-1, -1);
    }

    if (p11x == p12x)
    {
        float crossy = k2*p12x + b2;
        if (debug) qDebug() << "Crossy (1-vertical):" << QPoint(p12x, int(crossy));
        if (debug) qDebug() << "miny, maxy:" << qMin(p21y, p22y) << qMax(p21y, p22y);
        ok = true;
        return QPoint(p11.x(), int(crossy));
    }
    if (p21x == p22x)
    {
        float crossy = k1*p22x + b1;
        if (debug) qDebug() << "Crossy (2-vertical):" << QPoint(p22x, int(crossy));
        ok = true;
        return QPoint(p21.x(), int(crossy));
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

