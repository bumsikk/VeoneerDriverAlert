#ifndef GINDICATOR_H
#define GINDICATOR_H

#include <QGraphicsObject>

class GArrow;
class GNeedle;

class GIndicator : public QGraphicsObject
{
    Q_OBJECT
public:
    int FIRST_POS = 0;
    GIndicator(QGraphicsItem *parent = nullptr);
    double mAngle;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
private:
    int mPosition;
    GArrow *mArrow;
    GNeedle *mNeedle;


    QColor getArrowColor();
    QPointF getSecondPoint(double &angle) const;
    QPointF getSecondPoint() const;
    void fillCircle(QPainter *painter);

    static QPointF sFirstPoint;
};

#endif // GINDICATOR_H
