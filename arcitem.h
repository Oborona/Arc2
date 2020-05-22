#ifndef ARCITEM_H
#define ARCITEM_H

#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>
#include <qmath.h>

#define SIDE_TOP 0
#define SIDE_BOTTOM 1
#define SIDE_LEFT 2
#define SIDE_RIGHT 3
#define VERTICAL 0
#define HORIZONTAL 1

int vectorLength(QPoint p);
double vectorLength(QPoint p1, QPoint p2);
QPoint linesCross(QPoint p11, QPoint p12, QPoint p21, QPoint p22, bool &ok);

class ArcItem : public QGraphicsItem
{
public:
    ArcItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    int checkCollision(ArcItem* other);
    void calcSpeedEnd(ArcItem *other, int side);
    void updateItem();
    void moveItem();
    void interact(ArcItem* other);

    // Getters
    QString getName() { return name; }
    QPoint getSpeed() { return speed; }
    QPoint getSize() { return QPoint(width, height); }
    int getWidth() { return width; }
    int getHeight() { return height; }
    QPoint getCenter() { return QPoint(int(x()+ width/2), int(y()+height/2)); }
    double speedModule() { return qSqrt(speed.x()*speed.x() + speed.y()*speed.y()); }
    int getHp() { return hp; }

    // for debug
    QString name;
    QPoint speedEnd;
    QPoint speedEdge;
    QPoint oldSpeedEnd;
    QPoint oldSpeedEdge;
    QPoint center;
    QList<QPoint> colls;

    // Setters
    void setName(QString nn) { name = nn; }
    void setSize (int w, int h) { width = w; height = h; center.setX(width/2); center.setY(height/2); }
    void setSpeed (QPoint p) { speed = p;
                               speedEnd.setX(speed.x());
                               speedEnd.setY(speed.y());
                               speedEdge = speedEnd;
                             }
    void setHp(int nhp) { hp = nhp; }

    // Settings system
    QStringList settings;
    bool gotSetting(QString str);
    int addSetting(QString str);
    int removeSetting(QString str);

    // Misc
    void clearColls() { colls.clear(); }
    void addColl (QPoint c) { colls.append(c); }
    QList<QPoint>* getColls() { return &colls; }

    // Game mechanics
    void damage(int d);

protected:
    QPoint speed;
    QPoint oldSpeed;
    int width;
    int height;
    int hp;

};

#endif // ARCITEM_H
