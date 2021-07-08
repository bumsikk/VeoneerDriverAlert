#ifndef TJPFEATURESTATE_H
#define TJPFEATURESTATE_H

#include <QObject>
#include <QString>
#include "lcm/lcm-cpp.hpp"
#include "generated/HMI_TjpFeatureState_INFORMATION/FeatureState.hpp"
#include "generated/HMI_Vehicle_INFORMATION/Vehicle.hpp"
#include <QPixmap>
#include <QMediaPlayer>


using namespace std;

enum Alert{
    takeControl,
    pilotUnavailable,
    eyesOnRoad,
    noAlert
};

enum HTJA{
    Off,
    StandBy,
    Unavailable,
    Available,
    ActivationInProgress,
    Active,
    ReducePropulsion,
    IntelligentStop,
    BlindStop,
    WheelLockinProgress,
    DeactivationInProgress,
    DriverCautionRequest,
    DriverDeactivationReqeust
};


class TJPFeatureState : public QObject
{
   Q_OBJECT
public:
   TJPFeatureState();
   void handle(const lcm::ReceiveBuffer* rbuf, const std::string &channel);
signals:
   void sigs_state(QString s); //signal for state
   void sigs_pic(QPixmap p); //for icon
   void sigs_htja(HTJA s); //for htja mode
   void play_alert(Alert a); //play audio
private:
   int state; //index of HTJA state
   int hmi_reason; //index of message vector
   int prev_state;
   Alert curAlert;



   vector<QString> message = {
       " ",
       "Driver inattentive",
       "No lead vehicle",
       "No barrier",
       "Lane indequate",
       "Lane splitting",
       "Lane merging",
       "Lane ending",
       "Curve ahead",
       "Toll booth ahead",
       "Vehicle not centered in lane",
       "Lane width too narrow or wide",
       "Stability Control or \n Anti Lock Braking Activated",
       "Tow is enabled",
       "Trunk is open",
       "Door is open",
       "Seatbelt unbuckled",
       "Parking brake engaged",
       "Gear not in drive",
       "Hood is open",
       "Above feature max speed",
       "Stability control system fault",
       "System fault detected",
       "Driver initiated deactivation",
       "Stop and Go time expiration",
       "Driver Misuse",
       "Accident detected",
       "Off or Standby"
   };

};

#endif // TJPFEATURESTATE_H

