#include "vehiclespeedinfo.h"
#include <QDebug>
VehicleSpeedInfo::VehicleSpeedInfo()
{
   vehicle_speed = 0;
}

void VehicleSpeedInfo::handle(const lcm::ReceiveBuffer *rbuf, const std::string &channel){
   HMI_Vehicle_INFORMATION::Vehicle v;
   int result = v.decode(rbuf->data, 0 ,static_cast<int>(rbuf->data_size));
   if(result<0){
       qDebug()<<"failed to decode Speed info "<<endl;
       return;
   }
   vehicle_speed = v.speed;


   emit sigs(v.speed);
   emit speed_int(v.speed);
}
