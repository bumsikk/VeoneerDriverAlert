QT       += core gui
QT += multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -llcm
macx {
    INCLUDEPATH += /usr/local/include
    LIBS += -L"/usr/local/lib"
}
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    garrow.cpp \
    gindicator.cpp \
    gneedle.cpp \
    gscene.cpp \
    htja_switch.cpp \
    lcm_thread.cpp \
    main.cpp \
    mainwindow.cpp \
    tjpfeaturestate.cpp \
    vehiclespeedinfo.cpp

HEADERS += \
    garrow.h \
    generated/HMI_DcConfigParameters_REQUEST/DcConfigParameters.hpp \
    generated/HMI_FeatureActivation_REQUEST/FeatureActivation.hpp \
    generated/HMI_LanePoints_INFORMATION/LanePoint.hpp \
    generated/HMI_LanePoints_INFORMATION/LanePoints.hpp \
    generated/HMI_Lanes_INFORMATION/ClothoidInformation.hpp \
    generated/HMI_Lanes_INFORMATION/LaneClothoids.hpp \
    generated/HMI_Lanes_INFORMATION/RoadEstimationLaneInformation.hpp \
    generated/HMI_ParkingAssistActivation_REQUEST/ParkingActivation.hpp \
    generated/HMI_ParkingAssistStatus_INFORMATION/ParkingSpot.hpp \
    generated/HMI_ParkingAssistStatus_INFORMATION/ParkingStatus.hpp \
    generated/HMI_TargetTracking_INFORMATION/TargetInformation.hpp \
    generated/HMI_TargetTracking_INFORMATION/Targets.hpp \
    generated/HMI_TjpAvailabilityRequirements_INFORMATION/TjpAvailabilityRequirements.hpp \
    generated/HMI_TjpFeatureActivation_REQUEST/FeatureActivationRequest.hpp \
    generated/HMI_TjpFeatureState_INFORMATION/FeatureState.hpp \
    generated/HMI_Vehicle_INFORMATION/Gps.hpp \
    generated/HMI_Vehicle_INFORMATION/Vehicle.hpp \
    generated/HMI_VirtualBumper_INFORMATION/VirtualBumper.hpp \
    gindicator.h \
    gneedle.h \
    gscene.h \
    htja_switch.h \
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

RESOURCES += \
    res.qrc

