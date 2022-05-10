#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

class Player: public QGraphicsPixmapItem, public QObject{
    QPixmap pixmap;

public:
    Player(int sceneWidth, int sceneHeight);
};

#endif // PLAYER_H
