#include "tjpfeaturestate.h"
#include <iostream>

Alert FindAlert(HTJA _state){
    if(_state == HTJA::ReducePropulsion ||
       _state ==HTJA::IntelligentStop ||
       _state == HTJA::BlindStop||
       _state == HTJA::DriverDeactivationReqeust){
        return Alert::takeControl;}
    else if(_state == HTJA::DriverCautionRequest){
        return Alert::eyesOnRoad;
    }
    else if(_state == HTJA::Unavailable){
        return Alert::pilotUnavailable;
    }
    else return Alert::noAlert;
}


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
   int prev_hmi = hmi_reason;
   hmi_reason = int(f.hmiReason);
   Alert prevAlert = curAlert;
   curAlert = FindAlert(HTJA(state));
   //QString htja_status = HTJA[state];

   if(prev_state==state){
       return;
   }

   emit sigs_htja(HTJA(state));

   if(curAlert==Alert::takeControl ){
       if(prevAlert !=curAlert){
           QPixmap takeControlAlert(":/pictures/icons/controlAlert.png");
           emit play_alert(Alert::takeControl);
           emit sigs_pic(takeControlAlert);
       }
       if(prev_hmi != hmi_reason)
        emit sigs_state(message[hmi_reason]);
   }
   else if(curAlert==Alert::eyesOnRoad){
       if(prevAlert !=curAlert){
           QPixmap eyesOnRoadAlert(":/pictures/icons/eyesAlert.png");
           emit play_alert(Alert::eyesOnRoad);
           emit sigs_pic(eyesOnRoadAlert);
       }
       if(prev_hmi != hmi_reason)
        emit sigs_state(message[hmi_reason]);
   }
   else if(curAlert==Alert::pilotUnavailable){
       if(prevAlert !=curAlert){
           QPixmap pilotAlert(":/pictures/icons/pilotAlert.png");
           emit play_alert(Alert::pilotUnavailable);
           emit sigs_pic(pilotAlert);
           emit sigs_state(message[hmi_reason]);
       }
       if(prev_hmi != hmi_reason)
        emit sigs_state(message[hmi_reason]);
   }
   else {
       QPixmap p; //default
       QString s; //default
       emit play_alert(Alert::noAlert);
       emit sigs_pic(p);
       emit sigs_state(s);

   }

   //emit sigs_state(output);
}



