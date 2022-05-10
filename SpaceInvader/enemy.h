#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>

class Enemy: public QGraphicsPixmapItem, public QObject{
    QPixmap pixmap;

public:
    Enemy(int sceneWidth);
};

#endif // ENEMY_H
