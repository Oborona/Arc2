#include "itemmanager.h"

ItemManager::ItemManager()
{
    borders = QRect(0, 0, 600, 600);
}

void ItemManager::advance()
{
    for (int i = 0; i < actors.size(); i++)
        actors[i]->moveItem();

    checkCollisions();
}

void ItemManager::update()
{
    for (int i = 0; i < actors.size(); i++)
        actors[i]->updateItem();
}

void ItemManager::checkCollisions()
{
    for (int i = 0; i < actors.size(); i++)
    {
        if (!actors[i]->gotSetting("Kinematic"))
            continue;
        for (int j = 0; j < actors.size(); j++)
        {
            if (j == i)
                continue;
            if (!actors[j]->isVisible())
                continue;
            if (actors[j]->gotSetting("Kinematic"))
                continue;
            actors[j]->updateItem();
            int res = actors[i]->checkCollision(actors[j]);
            if (res == -1)
                continue;
            else
            {
                qDebug() << res;
                actors[i]->interact(actors[j]);
            }
        }
    }
}
