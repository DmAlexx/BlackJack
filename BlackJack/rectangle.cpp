#include "rectangle.h"
#include "qpainter.h"

Rectangle::Rectangle(QString path, TypeOfPlayer playerType)
    : m_playerType(playerType)
{
    m_rect = QRect(50, 50, 110, 160);
    m_pixmap = QPixmap(path);
}

QRectF Rectangle::boundingRect() const
{
    return QRectF(50, 50, 110, 160);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(m_rect, m_pixmap);
}

void Rectangle::setNewPath(QString path)
{
    m_pixmap = QPixmap(path);
}
