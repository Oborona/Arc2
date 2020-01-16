#include "itemmanager.h"

ItemManager::ItemManager()
{
    borders = QRect(0, 0, 600, 600);
}


Collision4x ItemManager::getItemCollision(ArcItem* still, ArcItem* moving)
{
    Collision4x coll;
    coll.left   = calcPoint(still, moving, SIDE_LEFT);
    coll.right  = calcPoint(still, moving, SIDE_RIGHT);
    coll.top    = calcPoint(still, moving, SIDE_TOP);
    coll.bottom = calcPoint(still, moving, SIDE_BOTTOM);

    return coll;
}

// variation with sides and two objects, instead of line formula
QPoint ItemManager::calcPoint(ArcItem* still, ArcItem* moving, int side)
{
    QPoint first = moving->getCenter();
    QPoint second = first + moving->getSpeed();

    // Line formula of moving item
    float A = first.y() - second.y();
    float B = second.x() - first.x();
    float C = first.x()*second.y() - first.y()*second.x();

    QPoint p;
    // horizontal line
    if (A == 0)
    {
        p.setY(-C/B);
        if (side == SIDE_LEFT)
            p.setX(still->x());
        if (side == SIDE_RIGHT)
            p.setX(still->x() + still->getWidth());
        if (side == SIDE_TOP || side == SIDE_BOTTOM)
            p = QPoint(-100, -100);
        return p;
    }
    // vertical line
    if (B == 0)
    {
        p.setX(-C/A);
        if (side == SIDE_TOP)
            p.setY(still->y());
        if (side == SIDE_BOTTOM)
            p.setY(still->y() + still->getHeight());
        if (side == SIDE_LEFT || side == SIDE_RIGHT)
            p = QPoint(-100, -100);
        return p;
    }

    int var;
    if (side == SIDE_LEFT)
    {
        var = still->x();
        p.setX(var);
        p.setY((-C - A*var)/B);
        if (p.y() <= still->y() || p.y() >= still->y() + still->getHeight())
            p = QPoint(-100, -100);
        return p;
    }

    if (side == SIDE_RIGHT)
    {
        var = still->x() + still->getWidth();
        p.setX(var);
        p.setY((-C - A*var)/B);
        if (p.y() <= still->y() || p.y() >= still->y() + still->getHeight())
            p = QPoint(-100, -100);
        return p;
    }

    if (side == SIDE_TOP)
    {
        var = still->y();
        p.setY(var);
        p.setX((-C - B*var)/A);
        if (p.x() <= still->x() || p.x() >= still->x() + still->getWidth())
            p = QPoint(-100, -100);
        return p;
    }

    if (side == SIDE_BOTTOM)
    {
        var = still->y() + still->getHeight();
        p.setY(var);
        p.setX((-C - B*var)/A);
        if (p.x() <= still->x() || p.x() >= still->x() + still->getWidth())
            p = QPoint(-100, -100);
        return p;
    }
    return QPoint(-100, -100);

}

void ItemManager::checkCollisions()
{
    QList<Collision4x> colls;
    for (int i = 0; i < actors.size(); i++)
    {
        if (actors[i]->isKinematic())
        {
            for (int j = 0; j < actors.size(); j++)
            {
                if (i == j)
                    continue;
                if (!actors[j]->isKinematic())
                {
                    // Seems weird
                    QRect rect;
                    rect.setX(actors[i]->x());
                    rect.setY(actors[i]->y());
                    rect.setWidth(actors[i]->getWidth());
                    rect.setHeight(actors[i]->getHeight());
                    actors[i]->invertSpeed(actors[j]->gotPoint(rect));
                }
            }
            continue;
        }
        actors[i]->clearDebugColl();
        for (int j = 0; j < actors.size(); j++)
        {
            if (i == j)
                continue;
            if (!actors[j]->isKinematic())
                continue;
            Collision4x c = getItemCollision(actors[i], actors[j]);
            actors[i]->appendColl(c);
            qDebug() << actors[i]->name << c.top << c.bottom << c.left << c.right;
        }
    }
}




void ItemManager::advance()
{
    for (int i = 0; i < actors.size(); i++)
        actors[i]->updateItem();
}
