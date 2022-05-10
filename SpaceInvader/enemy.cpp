#include "enemy.h"
#include <stdlib.h>

Enemy::Enemy(int sceneWidth) {
    srand(time(NULL));

    setPixmap(QPixmap("./images/missile.png"));
    float x = rand() % sceneWidth;
    float y = 0;
    setPos(x, y);
}
