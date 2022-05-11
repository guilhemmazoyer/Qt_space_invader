#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{

    bool gameOver();
    int health;

public:
    Health(QGraphicsItem * parent=0);
    void decrease();
    int getHealth();
};

#endif // HEALTH_H
