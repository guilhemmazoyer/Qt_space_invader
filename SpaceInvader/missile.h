#ifndef MISSILE_H
#define MISSILE_H

#include <QGraphicsPixmapItem>

class Missile: public QGraphicsPixmapItem, public QObject{
    QPixmap pixmap;

public:
    Missile(float x, float y);
};

#endif // MISSILE_H
