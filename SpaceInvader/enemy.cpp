#include "enemy.h"
#include "game.h"
#include <stdlib.h>
#include <QTimer>
#include <QGraphicsScene>

extern Game * game;

Enemy::Enemy(){
    srand(time(0));

    setPixmap(QPixmap(":/images/enemy.png"));

    // set random postion
    float random_positon = rand() % 19;
    random_positon *= game->sceneWidth/20;
    setPos(random_positon+20 , 0);

    int extraSpeed = rand() % 2;
    Enemy::speed = 3 + extraSpeed;

    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    int move_time = (rand() % 2)+1;
    timer->start(move_time*30 - (game->difficulty/2));
}

void Enemy::move(){
    if(game->isPauseMenuClosed){

        QList<QGraphicsItem *> colliding_items = collidingItems();

        for (int id = 0, n = colliding_items.size(); id < n; ++id) {
            bool isPlayer = typeid(*(colliding_items[id])) == typeid(Player);
            if (isPlayer) {
                game->setsound(":/sounds/explosion.wav", 3, 1);
                game->playerJukebox.play();
                game->displayGameOver(0);
                return;
            }
        }

        // Move enemy down
        setPos(x(), y()+Enemy::speed);
        if (pos().y() > (game->sceneHeight)){
            game->setsound(":/sounds/hurt.wav", 2, 1);
            game->voiceJukebox.play();

            game->health->decrease();

            scene()->removeItem(this);
            delete this;
        }
    }
}
