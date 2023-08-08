#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QString>
#include <QPropertyAnimation>
#include <QPointF>
#include "player.h"

class Rectangle : public QGraphicsItem
{
public:
    Rectangle(QString path, TypeOfPlayer playersType);
    TypeOfPlayer getPlayerType() { return m_playerType ;}
    void setNewPath(QString);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    //void drawRectangle();
    QGraphicsScene* m_scene;
    QRect m_rect;
    QPixmap m_pixmap;
    TypeOfPlayer m_playerType;

};

#endif // RECTANGLE_H
