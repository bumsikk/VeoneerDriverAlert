#include "gscene.h"
#include "gindicator.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

#define XSIZE 500
#define YSIZE 450

double GScene::sWidth = XSIZE;
double GScene::sHeight = YSIZE;

GScene::GScene(QObject *parent) : QGraphicsScene { 0.0, 0.0, XSIZE, YSIZE, parent }
{
    QPixmap circle(":/pictures/icons/Ellipse 15.png");
    mGauge = addPixmap(circle.scaled(GScene::sceneWidth()/2,GScene::sceneHeight()-200,Qt::KeepAspectRatio));

}
void GScene::UpdatePos(int x, int y){
    mGauge->setPos(x,y);
    if(x>0)
        mGauge->setScale(0.50); //smaller speedometer
}

void GScene::UpdateIndicator(){
    mIndicator = new GIndicator;
    mIndicator->mAngle= speed * 1.13;
    addItem(mIndicator);
    update();
}
