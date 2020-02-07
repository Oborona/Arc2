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




struct Collision4x
{
    QList<QPoint> points;

//    bool operator ==(const Collision4x& b) const
//    {
//        if (this->top    == b.top   &&
//            this->left   == b.left  &&
//            this->right  == b.right &&
//            this->bottom == b.bottom)
//            return true;
//        else
//            return false;
//    }
};

QPoint linesCross(QPoint p11, QPoint p12, QPoint p21, QPoint p22, bool &ok);

class ArcItem : public QGraphicsItem
{
public:
    ArcItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    int checkCollision(ArcItem* other);
    void updateItem();
    void moveItem();


    // Getters
    QString getName() { return name; }
    bool isKinematic() { return kinematic; }
    QPoint getSpeed() { return speed; }
    QPoint getSize() { return QPoint(width, height); }
    int getWidth() { return width; }
    int getHeight() { return height; }
    QPoint getCenter() { return QPoint(x()+ width/2, y()+height/2); }
    void invertSpeed(int dir);
    int speedModule() { return qSqrt(speed.x()*speed.x() + speed.y()*speed.y()); }

    // for debug
    QString name;
    QPoint speedEndPos;
    QPoint speedEdge;
    QPoint center;
    QList<QPoint> colls;

    // Setters
    void setName(QString nn) { name = nn; }
    void setSize (int w, int h) { width = w, height = h; center.setX(width/2); center.setY(height/2); }
    void setSpeed (QPoint p) { speed = p; }
    void setKinematic(bool b) { kinematic = b; }

    // Misc
    void clearColls() { colls.clear(); }
    void addColl (QPoint c) { colls.append(c); }

protected:
    bool kinematic;
    QPoint newPos;
    QPoint speed;
    QPoint restSpeed;
    int width;
    int height;

};


//class ArcItem : public QGraphicsItem
//{
//public:
//    ArcItem();

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    QRectF boundingRect() const;
//    bool collidesWith(QRectF borders);
//    void updateItem();
//    void calcSpeedPoints();

//    int collIsInRect(QRectF borders);

//    // Getters
//    QString getName() { return name; }
//    bool isKinematic() { return kinematic; }
//    QPoint getSpeed() { return speed; }
//    QPoint getSize() { return QPoint(width, height); }
//    int getWidth() { return width; }
//    int getHeight() { return height; }
//    QPoint getCenter() { return QPoint(x()+ width/2, y()+height/2); }
//    void invertSpeed(int dir);
//    int speedModule() { return qSqrt(speed.x()*speed.x() + speed.y()*speed.y()); }

//    // for debug
//    QString name;
//    QList<Collision4x> debugColl;
//    QPoint speedEdgePos;
//    QPoint speedEndPos;
//    void clearDebugColl() { debugColl.clear(); }
//    void appendColl(Collision4x coll) { debugColl.append(coll); }

//    // Setters
//    void setName(QString nn) { name = nn; }
//    void setSize (int w, int h) { width = w, height = h; }
//    void setSpeed (QPoint p) { speed = p; }
//    void setKinematic(bool b) { kinematic = b; }

//protected:
//    bool kinematic;
//    QPoint newPos;
//    QPoint speed;
//    QPoint restSpeed;
//    int width;
//    int height;

//};

#endif // ARCITEM_H
