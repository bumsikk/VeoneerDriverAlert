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


class TJPFeatureState : public QObject
{
   Q_OBJECT
public:
   TJPFeatureState();
   void handle(const lcm::ReceiveBuffer* rbuf, const std::string &channel);
signals:
   void sigs_state(QString s); //signal for state
   void sigs_pic(QPixmap p); //for icon
   void sigs_htja(QString s); //for htja mode
   void play_alert(Alert a);
private:
   int state; //index of HTJA state
   int hmi_reason; //index of message vector
   int prev_state;



   vector<QString> message = {
       "None",
       "Driver in attentive",
       "No Lead Vehicle",
       "No Barrier",
       "Lane in Adequate",
       "Lane Splitting",
       "Lane Merging",
       "Lane Ending",
       "Curve Ahead",
       "Toll Booth Ahead",
       "Stability Control/Anti Lock Braking Activated",
       "Tow is Enabled",
       "Trunk is Open",
       "Door is Open",
       "Seatbelt Unbuckled",
       "Parking Brake Engaged",
       "Gear Not in Drive",
       "Hood is Open",
       "Above Feature Max Speed",
       "Stability Control System Fault",
       "System Fault Detected",
       "Generic Faults",
       "Driver Misuse",
       "Off or Standby"
   };
   vector<QString> HTJA = {
       "Off",
       "StandBy",
       "Unavailable",
       "Available",
       "Activation in Progress",
       "Active",
       "Reduce Propulsion",
       "Intelligent Stop",
       "Blind Stop",
       "Wheel Lock in Progress",
       "Deactivation in Progress",
       "Driver Caution Request",
       "Driver Deactivation Reqeust"
   };

};

#endif // TJPFEATURESTATE_H

