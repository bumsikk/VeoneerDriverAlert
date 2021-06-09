#include "gindicator.h"
#include "gscene.h"
#include "garrow.h"
#include "gneedle.h"
#include <QPainter>
#include <QtMath>


static QPointF getFirstPoint()
{
    //these two check the position
    const double sWidth = GScene::sceneWidth();
    const double sHeight = GScene::sceneHeight()+30;
    const double x = sWidth / 4.0;
    const double y = sHeight / 4.0;
    return QPointF(x, y);
}


QPointF GIndicator::sFirstPoint = getFirstPoint();

GIndicator::GIndicator(QGraphicsItem *parent) : QGraphicsObject { parent }
{
    mNeedle = new GNeedle(this);
    mArrow = new GArrow(this);
    mPosition = FIRST_POS;

}


void GIndicator::fillCircle(QPainter *painter)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(sFirstPoint, 10.0, 10.0);
}

QColor GIndicator::getArrowColor()
{
   return Qt::white;
}

void GIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void) option;
    (void) widget;
    fillCircle(painter);
    QPointF secondPoint = getSecondPoint();
    mNeedle->setWidth(8);
    mNeedle->setColor(Qt::white);
    mNeedle->setFirstPoint(sFirstPoint);
    mNeedle->setSecondPoint(secondPoint);
    mArrow->setSize(20.0);
    mArrow->setColor(getArrowColor());
    mArrow->setFirstPoint(sFirstPoint);
    mArrow->setSecondPoint(secondPoint);

}

QRectF GIndicator::boundingRect() const
{
    return QRectF();
}

QPointF GIndicator::getSecondPoint() const
{
    //center = 125,120... r = 95
    double x = 125-95*cos(qDegreesToRadians(mAngle));
    double y = 120-95*sin(qDegreesToRadians(mAngle));
    return QPointF(x,y);

}
