#ifndef VEHICLESPEEDINFO_H
#define VEHICLESPEEDINFO_H

#include <QObject>
#include "lcm/lcm-cpp.hpp"
#include "generated/HMI_TjpFeatureState_INFORMATION/FeatureState.hpp"
#include "generated/HMI_Vehicle_INFORMATION/Vehicle.hpp"

class VehicleSpeedInfo : public QObject
{
   Q_OBJECT
public:
   VehicleSpeedInfo();
   void handle(const lcm::ReceiveBuffer* rbuf, const std::string &channel);
signals:
   void sigs(double sp);
private:
   double vehicle_speed;
};

#endif // VEHICLESPEEDINFO_H

