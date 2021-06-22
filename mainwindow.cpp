#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <iostream>
#include <QGraphicsPixmapItem>
#include "gscene.h"
#include "htja_switch.h"



MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);



   mScene = new GScene(this);
   ui->graphicsView->setScene(mScene);

   QPixmap def("");
   ui->label->setPixmap(def);
   ui->label_2->setText("");

   time = new QTimer(this);
   QObject::connect(time,SIGNAL(timeout()),this,SLOT(UpdateTime()));
   time->start(1000);

}

MainWindow::~MainWindow()
{
   delete ui;
}


void MainWindow::setLCM(LCM_thread *lcm){
   lcm_thread = lcm;

   htjaSwitch = new HtjaSwitch(this);
   layout()->addWidget(htjaSwitch);
   htjaSwitch->setGeometry((ui->time->x())+300,ui->time->y(),100,100);

   connect(lcm_thread->V_star(), SIGNAL(speed_int(int)), ui->Speed, SLOT(setNum(int))); //speed
   connect(lcm_thread->V_star(), SIGNAL(sigs(double)), this, SLOT(UpdateSpeed(double))); //speedometer
   connect(lcm_thread->T_star(), SIGNAL(sigs_pic(QPixmap)), ui->label, SLOT(setPixmap(QPixmap)));
   connect(lcm_thread->T_star(), SIGNAL(sigs_state(QString)), ui->label_2, SLOT(setText(QString)));
   connect(lcm_thread->T_star(), SIGNAL(sigs_htja(QString)), this, SLOT(HtjaState(QString))); //for Htja slide
}

void MainWindow::UpdateTime(){
    ui->time->setText(QTime::currentTime().toString(Qt::SystemLocaleShortDate));
}

void MainWindow::UpdateSpeed(double s){
    mScene = new GScene(this);

    mScene->speed= s;
    mScene->UpdateIndicator();
    ui->graphicsView->setScene(mScene);
}

void MainWindow::HtjaState(QString h){
    if(h=="Active")
        htjaSwitch->Htja_state(true);
    else
        htjaSwitch->Htja_state(false);
}
