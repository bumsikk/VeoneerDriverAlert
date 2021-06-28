#include "tjpfeaturestate.h"
#include <QDebug>
#include <iostream>


TJPFeatureState::TJPFeatureState()
{

}

void TJPFeatureState::handle(const lcm::ReceiveBuffer *rbuf, const std::string &channel){
   HMI_TjpFeatureState_INFORMATION::FeatureState f;
   int result = f.decode(rbuf->data, 0 ,static_cast<int>(rbuf->data_size));
   if(result<0){
       qDebug()<<"failed to decode TJPFeature info "<<endl;
       return;
   }
   prev_state = state;
   state = int(f.state);
   hmi_reason = int(f.hmiReason);
   QString htja_status = HTJA[state];

   if(prev_state==state){
       return;
   }

   emit sigs_htja(htja_status);

   if(hmi_reason == 16 || //gear not in drive
      hmi_reason == 6 ||  //lane merging
      hmi_reason == 8 ||  //road curvature ahead
      hmi_reason == 11 || //tow is enabled
      hmi_reason == 5 ||  //lane splitting
      hmi_reason == 12 || //trunk is open
      hmi_reason == 7 ||  //lane ending
      hmi_reason == 15 || //Parking brake engaged
      hmi_reason == 3 ||  //no adjacent barrier
      hmi_reason == 4 ||  //lane markings not visible
      hmi_reason == 17 || //hood open
      hmi_reason == 9 ){  //toll booth ahead

      QPixmap takeControlAlert(":/pictures/icons/controlAlert.png");
      QString output = "Take Control\nConditions out of ODD\n" + message[hmi_reason];
      emit play_alert(Alert::takeControl); //o= take control
      emit sigs_pic(takeControlAlert);
      emit sigs_state(output);

   }//hmi_reason that are out of oDD
   else if(hmi_reason == 1 || hmi_reason == 2){
       QPixmap eyesOnRoadAlert(":/pictures/icons/eyesAlert.png");
       QString output = "Eyes on Road\n"+ message[hmi_reason];
       emit play_alert(Alert::eyesOnRoad);
       emit sigs_pic(eyesOnRoadAlert);
       emit sigs_state(output);
   }//Eyes on Road
   else if(hmi_reason == 10 ||
           hmi_reason == 14 ||
           hmi_reason == 20 ||
           hmi_reason == 21 ||
           hmi_reason == 4 ||
           hmi_reason == 13){
       QPixmap takeControlAlert(":/pictures/icons/controlAlert.png");
       QString output = "Take Control\nDangerous\n" + message[hmi_reason];

       emit play_alert(Alert::takeControl);
       emit sigs_pic(takeControlAlert);
       emit sigs_state(output);
   }//hmi_reason that car is in danger
   else {
       QPixmap p; //default
       QString s; //default
       emit play_alert(Alert::noAlert);
       emit sigs_pic(p);
       emit sigs_state(s);
   }

   //emit sigs_state(output);
}

