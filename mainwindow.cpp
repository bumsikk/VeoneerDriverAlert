#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QGraphicsPixmapItem>
#include "htja_switch.h"
#include <QMediaPlayer>
#include "tjpfeaturestate.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   mScene = new GScene(this);
   ui->graphicsView->setScene(mScene);
   QPixmap def("");
   ui->image_alert->setPixmap(def);
   ui->text_alert->setText("");

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
   qRegisterMetaType<Alert>("Alert");

   connect(lcm_thread->V_star(), SIGNAL(speed_int(int)), ui->Speed, SLOT(setNum(int))); //speed
   connect(lcm_thread->V_star(), SIGNAL(sigs(double)), this, SLOT(UpdateSpeed(double))); //speedometer
   connect(lcm_thread->T_star(), SIGNAL(play_alert(Alert)), this, SLOT(PlayAudio(Alert))); //alert audio
   connect(lcm_thread->T_star(), SIGNAL(sigs_pic(QPixmap)), ui->image_alert, SLOT(setPixmap(QPixmap))); //alert images
   connect(lcm_thread->T_star(), SIGNAL(sigs_state(QString)), ui->text_alert, SLOT(setText(QString))); //alert text
   connect(lcm_thread->T_star(), SIGNAL(sigs_htja(QString)), this, SLOT(HtjaState(QString)));//Htja slide

}

void MainWindow::UpdateTime(){
    ui->time->setText(QTime::currentTime().toString(Qt::SystemLocaleShortDate));

}
void MainWindow::UpdatePosition(){
    QFont font = ui->Speed->font();
    if(isAlert){
        ui->time->setGeometry(60,480,117,21);
        ui->htja_icon->setGeometry(ui->time->x()+430,ui->time->y(),81,21);
        mScene->UpdatePos(140,280);
        font.setPointSize(40);
        ui->Speed->setGeometry(ui->time->x()+230,ui->time->y(),81,21);
    }
    else{
        mScene->UpdatePos(0,0);
        ui->time->setGeometry(60,60,117,31);
        ui->htja_icon->setGeometry(290,60,81,31);
    }

}

void MainWindow::UpdateSpeed(double s){
    mScene = new GScene(this);
    //UpdatePosition();
    mScene->speed= s;
    mScene->UpdateIndicator();
    ui->graphicsView->setScene(mScene);
}

void MainWindow::HtjaState(QString h){
    if(h=="Active")
        htjaSwitch->Htja_state(true);
    else{
        htjaSwitch->Htja_state(false);
    }
}

void MainWindow::PlayAudio(Alert _alert){

   QMediaPlayer *audio = new QMediaPlayer();

   switch (_alert) {
   case takeControl:
       isAlert = true;
       audio->setMedia(QUrl("qrc:/audios/alert_sounds/controlAlert.wav"));
       break;
   case pilotUnavailable:
       isAlert = true;
       audio->setMedia(QUrl("qrc:/audios/alert_sounds/pilotAlert.wav"));
       break;
   case eyesOnRoad:
       isAlert = true;
       audio->setMedia(QUrl("qrc:/audios/alert_sounds/eyeAlert.wav"));
       break;
   case noAlert:
       isAlert = false;
       audio->setMedia(QUrl(""));
       audio->stop();
       break;
   }

    if(audio->state()==QMediaPlayer::PlayingState)
        audio->setPosition(0);
    else
        audio->play();

}
