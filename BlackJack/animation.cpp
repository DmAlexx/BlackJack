#include "animation.h"

Animation::Animation()
{

}

Animation::Animation(QGraphicsRectItem *rectItem, QGraphicsScene *scene, QObject *parent)
    : QObject(parent), m_rectItem(rectItem), m_scene(scene)
{
}

void Animation::startAnimation(const QRectF &startRect, const QRectF &endRect, int duration)
{
    // Создаем анимацию для свойства "rect" (прямоугольник) объекта
    QPropertyAnimation* animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(duration);
    animation->setStartValue(startRect);
    animation->setEndValue(endRect);

    // Подключаем сигнал завершения анимации к слоту, чтобы очистить анимацию после завершения
    connect(animation, &QPropertyAnimation::finished, animation, &QPropertyAnimation::deleteLater);

    // Запускаем анимацию
    animation->start();
}

void Animation::setScene(QGraphicsScene *scene)
{
    m_scene = scene;
}
