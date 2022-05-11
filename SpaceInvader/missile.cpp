#include "missile.h"
#include "enemy.h"
#include "game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

extern Game * game;

Missile::Missile(){
        setPixmap(QPixmap(":/images/missile.png"));

        QTimer * timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(move()));

        // Set the timer to 30ms
        timer->start(30);
}

void Missile::move(){
    if(game->isPauseMenuClosed){
        QList<QGraphicsItem *> colliding_items = collidingItems();

        for (int id = 0, n = colliding_items.size(); id < n; ++id) {
            bool isEnemy = typeid(*(colliding_items[id])) == typeid(Enemy);
            if (isEnemy) {
                game->score->increase();

                game->setsound(":/sounds/aliendeath.wav", 4, 1);
                game->enemyJukebox.play();

                scene()->removeItem(colliding_items[id]);
                scene()->removeItem(this);

                delete colliding_items[id];
                delete this;

                return;
            }
        }

        setPos(x(), y()-10);

        if (pos().y() + this->pixmap().height() < 0){
            scene()->removeItem(this);
            delete this;
        }
    }
}
