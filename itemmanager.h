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

    void advance();
    void update();
    void checkCollisions();
};
#endif // COLLISIONMANAGER_H
