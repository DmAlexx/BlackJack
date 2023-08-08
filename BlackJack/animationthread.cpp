#include "animationthread.h"


AnimationThread::AnimationThread(std::shared_ptr<QGraphicsItemAnimation> animation)
    : m_animation(animation)
{

}

void AnimationThread::run()
{
    QCoreApplication::postEvent(this, new QEvent(QEvent::User));  // Запуск анимации после запуска потока
    exec();  // Запуск цикла обработки событий для потока
}

bool AnimationThread::event(QEvent *event)
{
    if (event->type() == QEvent::User)
    {
        m_animation->timeLine()->start();  // Запуск анимации
        return true;
    }
    return QThread::event(event);
}



