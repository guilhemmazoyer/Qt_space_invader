#include "player.h"
#include "missile.h"
#include "game.h"
#include "qevent.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPixmap>

extern Game * game;

Player::Player(){
    setPixmap(QPixmap(":/images/player.png"));

    goLeft = false;
    goRight = false;

    float random_positon = rand() % 20;
    random_positon *= game->sceneWidth/20;
    setPos(random_positon, game->scene->height() - pixmap().height());
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void Player::keyPressEvent(QKeyEvent *event){
    // Move left
    if ((event->key() == Qt::Key_Q) || (event->key() == Qt::Key_Left)) {
        goLeft = true;
    }

    // Move right
    else if ((event->key() == Qt::Key_D) || (event->key() == Qt::Key_Right)) {
        goRight = true;
    }

    else if ((event->key() == Qt::Key_Space)) {
        // Create a bullet
        Missile * missile = new Missile();
        missile->setPos(x() + game->spaceshipWidthOffset, y()-50);
        scene()->addItem(missile);
        game->setsound(":/sounds/blaster.wav", 3, 1);
        game->playerJukebox.play();
    }

    else if ((event->key() == Qt::Key_Escape)) {
        // Pause the game
        game->setsound(":/sounds/click2.wav", 1, 1);
        game->interfaceJukebox.play();
        game->displayPause();
    }
}

void Player::keyReleaseEvent(QKeyEvent *event){
    // Move left
    if ((event->key() == Qt::Key_Q) || (event->key() == Qt::Key_Left)) {
        goLeft = false;
    }
    // Move right
    else if ((event->key() == Qt::Key_D) || (event->key() == Qt::Key_Right)) {
        goRight = false;
    }
}

void Player::action(){
    if(game->isPauseMenuClosed){
        // go Left
        if(goLeft){
            if (pos().x() > 0)
                setPos(x()-(game->sceneWidth/20), y());
        }

        // go Right
        if(goRight){
            if (pos().x() + 150 < (game->sceneWidth)){
                setPos(x()+(game->sceneWidth/20), y());
            }
        }
    }
}

void Player::spawn(){
    if(game->isPauseMenuClosed){
        // focus on the player to make him able to move
        setFocus();
        // create enemy
        Enemy * enemy = new Enemy();
        scene()->addItem(enemy);
    }
}
