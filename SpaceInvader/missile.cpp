#include "missile.h"

Missile::Missile(float x, float y){
    setPixmap(QPixmap("./images/missile.png"));
    setPos(x,y);
}
