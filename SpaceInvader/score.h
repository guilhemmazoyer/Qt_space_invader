#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{

    int score;

public:
    Score(QGraphicsItem * parent=0);
    void increase();
    int getScore();
};

#endif // SCORE_H
