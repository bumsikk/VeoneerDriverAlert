#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QObject>

class speedometer : public QObject
{
    Q_OBJECT
public:
    explicit speedometer(QObject *parent = nullptr);

signals:

};

#endif // SPEEDOMETER_H
