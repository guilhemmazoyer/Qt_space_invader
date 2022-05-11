#include "health.h"
#include "game.h"
#include <QFont>
#include <QApplication>

extern Game * game;

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // Initialize to 3
    health = 3;
    setPlainText(QString("Health: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("consolas", 20));
}

void Health::decrease(){
    health--;
    setPlainText(QString("Health: ") + QString::number(health));
    if(getHealth() < 1){
        game->displayGameOver(1);
    }
}

int Health::getHealth(){
    return health;
}

bool Health::gameOver(){
    return health < 1;
}
