#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QGraphicsPixmapItem>
#include "htja_switch.h"
#include <QMediaPlayer>
#include "tjpfeaturestate.h"



MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->image_alert->setVisible(false);
   ui->text_alert->setVisible(false);
   ui->text_msg->setVisible(false);
   ui->border->setVisible(false);
   mScene = new GScene(this);
   ui->graphicsView->setScene(mScene);
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
   //htjaSwitch->setGeometry((ui->time->x())+500,ui->time->y()+420,100,100);
   qRegisterMetaType<Alert>("Alert");
   qRegisterMetaType<HTJA>("HTJA");

   connect(lcm_thread->V_star(), SIGNAL(speed_int(int)), ui->Speed, SLOT(setNum(int))); //speed
   connect(lcm_thread->V_star(), SIGNAL(sigs(double)), this, SLOT(UpdateSpeed(double))); //speedometer
   connect(lcm_thread->T_star(), SIGNAL(play_alert(Alert)), this, SLOT(PlayAudio(Alert))); //alert audio
   connect(lcm_thread->T_star(), SIGNAL(sigs_pic(QPixmap)), ui->image_alert, SLOT(setPixmap(QPixmap))); //alert images
   connect(lcm_thread->T_star(), SIGNAL(sigs_state(QString)), ui->text_msg, SLOT(setText(QString))); //alert text
   connect(lcm_thread->T_star(), SIGNAL(sigs_htja(HTJA)), this, SLOT(HtjaState(HTJA)));//Htja slide

}

void MainWindow::UpdateTime(){
    ui->time->setText(QTime::currentTime().toString(Qt::SystemLocaleShortDate));

}
void MainWindow::UpdatePosition(){
    QFont font = ui->Speed->font();
    //all of the sizes/position can be modified after implimenting on HUD screen
    if(isAlert){
        ui->image_alert->setVisible(true);
        ui->text_alert->setVisible(true);
        ui->text_msg->setVisible(true);
        ui->time->setGeometry(60,485,117,21);
        htjaSwitch->setGeometry((ui->time->x())+500,480,100,100);
        ui->htja_icon->setGeometry(ui->time->x()+430,480,81,31);
        mScene->UpdatePos(80,290);
        font.setPointSize(40);
        ui->Speed->setFont(font);
        font.setPointSize(18);
        ui->unit->setFont(font);
        ui->Speed->setGeometry(ui->time->x()+280,ui->htja_icon->y()-10,81,41);
        ui->unit->setGeometry(ui->Speed->x()+80,ui->htja_icon->y(),81,41);
        ui->border->setVisible(true);;
    }
    else{
        ui->image_alert->setVisible(false);
        ui->text_alert->setVisible(false);
        ui->text_msg->setVisible(false);
        ui->border->setVisible(false);
        mScene->UpdatePos(0,0);
        ui->time->setGeometry(60,60,117,31);
        htjaSwitch->setGeometry((ui->time->x())+300,ui->time->y(),100,100);
        ui->htja_icon->setGeometry(290,60,81,31);
        font.setPointSize(55);
        ui->Speed->setFont(font);
        font.setPointSize(24);
        ui->unit->setFont(font);
        ui->Speed->setGeometry(190,300,101,71);
        ui->unit->setGeometry(330,290,61,51);
    }

}

void MainWindow::UpdateSpeed(double s){
    mScene = new GScene(this);
    UpdatePosition();
    mScene->speed= s;
    mScene->UpdateIndicator(isAlert);
    ui->graphicsView->setScene(mScene);
}

void MainWindow::HtjaState(HTJA h){
    if(h== HTJA::Off || h== HTJA::StandBy||h== HTJA::Available || h== HTJA::Unavailable)
        htjaSwitch->Htja_state(false);
    else{
        htjaSwitch->Htja_state(true);
    }
}

void MainWindow::PlayAudio(Alert _alert){
   QMediaPlayer *audio = new QMediaPlayer();

   QPixmap pic;

   switch (_alert) {
   case takeControl:
       isAlert = true;
       pic = QPixmap(":/pictures/border/rAlert.png");
       ui->border->setPixmap(pic.scaled(ui->border->width(),ui->border->height()));
       ui->text_alert->setText("TAKE CONTROL");
       audio->setMedia(QUrl("qrc:/audios/alert_sounds/controlAlert.wav"));
       break;
   case pilotUnavailable:
       isAlert = true;
       pic = QPixmap(":/pictures/border/gAlert.png");
       ui->border->setPixmap(pic.scaled(ui->border->width(),ui->border->height()));
       ui->text_alert->setText("PILOT UNAVAILABLE");
       audio->setMedia(QUrl("qrc:/audios/alert_sounds/pilotAlert.wav"));
       break;
   case eyesOnRoad:
       isAlert = true;
       pic = QPixmap(":/pictures/border/yAlert.png");
       ui->border->setPixmap(pic.scaled(ui->border->width(),ui->border->height()));
       ui->text_alert->setText("EYES ON ROAD");
       audio->setMedia(QUrl("qrc:/audios/alert_sounds/eyeAlert.wav"));
       break;
   case noAlert:
       isAlert = false;
       audio->setMedia(QUrl(""));
       audio->stop();
       break;
   }
   ui->border->setPixmap(pic.scaled(ui->border->width(),ui->border->height()));

    if(audio->state()==QMediaPlayer::PlayingState)
        audio->setPosition(0);
    else
        audio->play();

}
