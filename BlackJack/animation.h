#ifndef ANIMATION_H
#define ANIMATION_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPropertyAnimation>

class Animation : public QObject
{
    Q_OBJECT

public:
    Animation(QGraphicsRectItem* rectItem, QGraphicsScene* scene, QObject* parent = nullptr);
    void startAnimation(const QRectF& startRect, const QRectF& endRect, int duration);
    void setScene(QGraphicsScene* scene);

private:
    QGraphicsRectItem* m_rectItem;      // Прямоугольник для анимации
    QGraphicsScene* m_scene;            // Графическая сцена
};

#endif // ANIMATION_H



