#ifndef MISSILE_H
#define MISSILE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>

class Missile: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Missile();

public slots:
    void move();
};

#endif // MISSILE_H
