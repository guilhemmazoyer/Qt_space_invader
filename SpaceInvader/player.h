#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>

class Player: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    void keyPressEvent(QKeyEvent * event);

public:
    Player();

public slots:
    void spawn();
};

#endif // PLAYER_H
