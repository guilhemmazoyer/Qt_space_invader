#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>

class Player: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

    bool goLeft;
    bool goRight;

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

public:
    Player();

public slots:
    void spawn();
    void action();
};

#endif // PLAYER_H
