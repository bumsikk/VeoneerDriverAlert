QT       += core gui
#QT += quick


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -llcm
macx {
    INCLUDEPATH += /usr/local/include
    LIBS += -L1"/usr/local/lib"
}
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    garrow.cpp \
    gindicator.cpp \
    gneedle.cpp \
    gscene.cpp \
    lcm_thread.cpp \
    main.cpp \
    mainwindow.cpp \
    tjpfeaturestate.cpp \
    vehiclespeedinfo.cpp

HEADERS += \
    garrow.h \
    generated/HMI_DcConfigParameters_REQUEST/DcConfigParameters.hpp \
    generated/HMI_DcConfigParameters_REQUEST/DcConfigParameters.hpp \
    generated/HMI_FeatureActivation_REQUEST/FeatureActivation.hpp \
    generated/HMI_FeatureActivation_REQUEST/FeatureActivation.hpp \
    generated/HMI_LanePoints_INFORMATION/LanePoint.hpp \
    generated/HMI_LanePoints_INFORMATION/LanePoint.hpp \
    generated/HMI_LanePoints_INFORMATION/LanePoints.hpp \
    generated/HMI_LanePoints_INFORMATION/LanePoints.hpp \
    generated/HMI_Lanes_INFORMATION/ClothoidInformation.hpp \
    generated/HMI_Lanes_INFORMATION/ClothoidInformation.hpp \
    generated/HMI_Lanes_INFORMATION/LaneClothoids.hpp \
    generated/HMI_Lanes_INFORMATION/LaneClothoids.hpp \
    generated/HMI_Lanes_INFORMATION/RoadEstimationLaneInformation.hpp \
    generated/HMI_ParkingAssistActivation_REQUEST/ParkingActivation.hpp \
    generated/HMI_ParkingAssistActivation_REQUEST/ParkingActivation.hpp \
    generated/HMI_ParkingAssistStatus_INFORMATION/ParkingSpot.hpp \
    generated/HMI_ParkingAssistStatus_INFORMATION/ParkingSpot.hpp \
    generated/HMI_ParkingAssistStatus_INFORMATION/ParkingStatus.hpp \
    generated/HMI_ParkingAssistStatus_INFORMATION/ParkingStatus.hpp \
    generated/HMI_TargetTracking_INFORMATION/TargetInformation.hpp \
    generated/HMI_TargetTracking_INFORMATION/TargetInformation.hpp \
    generated/HMI_TargetTracking_INFORMATION/Targets.hpp \
    generated/HMI_TargetTracking_INFORMATION/Targets.hpp \
    generated/HMI_TjpAvailabilityRequirements_INFORMATION/TjpAvailabilityRequirements.hpp \
    generated/HMI_TjpAvailabilityRequirements_INFORMATION/TjpAvailabilityRequirements.hpp \
    generated/HMI_TjpFeatureActivation_REQUEST/FeatureActivationRequest.hpp \
    generated/HMI_TjpFeatureActivation_REQUEST/FeatureActivationRequest.hpp \
    generated/HMI_TjpFeatureState_INFORMATION/FeatureState.hpp \
    generated/HMI_TjpFeatureState_INFORMATION/FeatureState.hpp \
    generated/HMI_Vehicle_INFORMATION/Gps.hpp \
    generated/HMI_Vehicle_INFORMATION/Gps.hpp \
    generated/HMI_Vehicle_INFORMATION/Vehicle.hpp \
    generated/HMI_Vehicle_INFORMATION/Vehicle.hpp \
    generated/HMI_VirtualBumper_INFORMATION/VirtualBumper.hpp \
    generated/HMI_VirtualBumper_INFORMATION/VirtualBumper.hpp \
    generated/flexrayd/svs4_100_E4/lcm/dblClothoid_left_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/dblClothoid_left_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/dblClothoid_right_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/dblClothoid_right_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/dblClothoid_secondLeft_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/dblClothoid_secondLeft_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/dblClothoid_secondRight_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/dblClothoid_secondRight_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/egoLane_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/egoLane_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/laneEvent_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/laneEvent_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/left_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/left_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/right_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/right_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/secondLeft_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/secondLeft_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/secondRight_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/secondRight_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/svs4_100_E4_lane_markers_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/svs4_100_E4_lane_markers_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/temporary_marking_t.hpp \
    generated/flexrayd/svs4_100_E4/lcm/temporary_marking_t.hpp \
    generated/zenuity/lcm/zeader_t.hpp \
    generated/zenuity/lcm/zeader_t.hpp \
    gindicator.h \
    gneedle.h \
    gscene.h \
    lcm_thread.h \
    mainwindow.h \
    tjpfeaturestate.h \
    vehiclespeedinfo.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

