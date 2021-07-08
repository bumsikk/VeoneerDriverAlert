#include "gindicator.h"
#include "gscene.h"
#include "garrow.h"
#include "gneedle.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>


QPointF GIndicator::getFirstPoint()
{
    return center;
}


GIndicator::GIndicator(bool isAlert, QGraphicsItem *parent) : QGraphicsObject { parent }
{
    mNeedle = new GNeedle(this);
    mArrow = new GArrow(this);
    mPosition = FIRST_POS;

    if(isAlert){
        center = QPointF(140,350);
        radius = 35;
    }
    else{
        center = QPointF(125,120);
        radius = 90;
    }
    sFirstPoint = getFirstPoint();

}


QColor GIndicator::getArrowColor()
{
   return Qt::white;
}

void GIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void) option;
    (void) widget;
    QPointF secondPoint = getSecondPoint();
    mNeedle->setWidth(5);
    mNeedle->setColor(Qt::white);
    mNeedle->setFirstPoint(sFirstPoint);
    mNeedle->setSecondPoint(secondPoint);
    mArrow->setSize(18.0);
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
    double x = center.x()-radius*cos(qDegreesToRadians(mAngle));
    double y = center.y()-radius*sin(qDegreesToRadians(mAngle));
    return QPointF(x,y);

}
