#include <QGraphicsTextItem>
#include <QBrush>
#include "button.h"

Button::Button(QString name, float p_width, float p_height, QGraphicsItem *parent): QGraphicsRectItem(parent){


    // draw the rect
    setRect(0,0,p_width,p_height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    // draw text
    text = new QGraphicsTextItem(name, this);
    text->setDefaultTextColor(Qt::white);
    qreal xPos = rect().width()/2 - text->boundingRect().width()/2;
    qreal yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);

    // allow responding to hover events
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    // change color
    QColor hoverColor(30, 30, 200);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(hoverColor);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    // change color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}
