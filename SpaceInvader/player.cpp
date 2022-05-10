#include "player.h"

Player::Player(int sceneWidth, int sceneHeight) {
    setPixmap(QPixmap("../assets/images/missile.png"));
    setPos(sceneWidth, sceneHeight);
}
