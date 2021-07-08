#ifndef GSCENE_H
#define GSCENE_H

#include <QGraphicsScene>

class GIndicator;

class GScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GScene(QObject *parent = nullptr);

    static double sceneWidth()
    {
        return sWidth;
    }

    static double sceneHeight()
    {
        return sHeight;
    }
    double speed;

    void UpdateIndicator(bool is_alert);
    void UpdatePos(int x, int y);

private:
    QGraphicsPixmapItem *mGauge;
    GIndicator *mIndicator;
    static double sWidth;
    static double sHeight;
};

#endif // GSCENE_H
