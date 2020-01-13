#ifndef ARCITEM_H
#define ARCITEM_H

#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>

#define SIDE_LEFT 0
#define SIDE_RIGHT 1
#define SIDE_TOP 2
#define SIDE_BOTTOM 3
#define VERTICAL 0
#define HORIZONTAL 1


struct Collision4x
{
    QPoint top;
    QPoint bottom;
    QPoint left;
    QPoint right;

    bool operator ==(const Collision4x& b) const
    {
        if (this->top    == b.top   &&
            this->left   == b.left  &&
            this->right  == b.right &&
            this->bottom == b.bottom)
            return true;
        else
            return false;
    }
};

class ArcItem : public QGraphicsItem
{
public:
    ArcItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    bool collidesWith(QRectF borders);
    void updateItem();

    void updatePosition() { newPosition.setX(pos().x()); newPosition.setY(pos().y()); }

    // Getters
    bool isKinematic() { return kinematic; }
    QPoint getSpeed() { return speed; }
    QPoint getSize() { return QPoint(width, height); }
    int getWidth() { return width; }
    int getHeight() { return height; }
    QPoint getCenter() { return QPoint(x()+ width/2, y()+height/2); }
    void invertSpeed(int dir);

    // for debug
    QList<Collision4x> debugColl;
    void clearDebugColl() { debugColl.clear(); }
    void appendColl(Collision4x coll) { debugColl.append(coll); }

    // Setters
    void setSize (int w, int h) { width = w, height = h; }
    void setSpeed (QPoint p) { speed = p; }
    void setKinematic(bool b) { kinematic = b; }

protected:
    bool kinematic;
    QPoint newPosition;
    QPoint speed;
    QPoint restSpeed;
    int width;
    int height;

};

#endif // ARCITEM_H
