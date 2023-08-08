#ifndef ANIMATIONTHREAD_H
#define ANIMATIONTHREAD_H

#include <QThread>
#include <QCoreApplication>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

class AnimationThread : public QThread
{
public:
    AnimationThread(std::shared_ptr<QGraphicsItemAnimation> animation);

protected:
    void run() override;
    bool event(QEvent *event) override;

private:
    std::shared_ptr<QGraphicsItemAnimation> m_animation;
};

#endif // ANIMATIONTHREAD_H
