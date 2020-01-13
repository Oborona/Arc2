#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "arcitem.h"

class ItemManager
{
public:
    ItemManager();

private:
    QList<ArcItem*> actors;
    QRect borders;

public:
    void addActor(ArcItem* na) { actors.append(na); }
    void setupBorders();
    Collision4x getItemCollision(ArcItem* still, ArcItem* second);
    QPoint calcPoint(ArcItem *still, ArcItem *moving, int side);
    void setBorders(QRect nb) { borders = nb; }
    void checkCollisions();

    void advance();

};

#endif // COLLISIONMANAGER_H
