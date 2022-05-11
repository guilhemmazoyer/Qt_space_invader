#include "explosion.h"
#include "game.h"

extern Game * game;

Explosion::Explosion() {
    setPixmap(QPixmap(":/images/explosion.png"));
}
