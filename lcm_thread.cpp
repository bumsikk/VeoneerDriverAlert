#include "lcm_thread.h"

//subscribe necessary chennels here
LCM_thread::LCM_thread()
{
    url = "udpm://239.255.76.67:7667?ttl=1"; //don't change
    lcmObj = new lcm::LCM(url);
    string HMI_TjpFeatureStateInfo_channel = "HMI_TjpFeatureState_INFORMATION";
    string HMI_Vehicle_Info = "HMI_Vehicle_INFORMATION";
    lcmObj->subscribe(HMI_Vehicle_Info, &VehicleSpeedInfo::handle, &V);
    lcmObj->subscribe(HMI_TjpFeatureStateInfo_channel,&TJPFeatureState::handle, &T );
}


void LCM_thread::run(){
    while(0 == lcmObj->handle());
}

VehicleSpeedInfo* LCM_thread::V_star(){
    return &V;
}

TJPFeatureState* LCM_thread::T_star(){
    return &T;
}

lcm::LCM * LCM_thread::l_obj(){
    return lcmObj;
}
