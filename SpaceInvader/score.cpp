#include "score.h"
#include "game.h"
#include <QFont>

extern Game * game;

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // Initialize to 0
    score = 0;
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("consolas", 20));
}

void Score::increase(){
    ++score;
    setPlainText(QString("Score: ") + QString::number(getScore()));
    if(getScore()%10 == 0) {
        game->setsound(":/sounds/score.wav", 1, 1);
        game->interfaceJukebox.play();
    }
    if(!game->isUnlimited){
        if(getScore() >= 10+10*(game->difficulty/2)){
            game->displayWin();
        }
    }
}

int Score::getScore(){
    return score;
}
