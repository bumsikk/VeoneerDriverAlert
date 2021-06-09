#ifndef LCM_THREAD_H
#define LCM_THREAD_H

#include <QObject>
#include <QThread>
#include "lcm/lcm-cpp.hpp"
#include "generated/HMI_TjpFeatureState_INFORMATION/FeatureState.hpp"
#include "generated/HMI_Vehicle_INFORMATION/Vehicle.hpp"
#include "vehiclespeedinfo.h"
#include "tjpfeaturestate.h"

using namespace std;

class LCM_thread : public QThread
{
   Q_OBJECT
public:
   LCM_thread();
   void run();
   void lcm_subscribe_v(VehicleSpeedInfo *V);
   VehicleSpeedInfo* V_star();
   TJPFeatureState* T_star();
   lcm::LCM *l_obj();
private:
   lcm::LCM *lcmObj;
   string url;

   string HMI_TjpFeatureStateInfo_channel;
   string HMI_Vehicle_Info;

   VehicleSpeedInfo V;
   TJPFeatureState T;

};

#endif // LCM_THREAD_H

