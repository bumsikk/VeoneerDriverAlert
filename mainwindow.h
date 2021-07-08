#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lcm_thread.h"
#include <QPainter>
#include <QPixmap>
#include <QTransform>
#include <QtMath>
#include "htja_switch.h"
#include "tjpfeaturestate.h"
#include "gscene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GScene;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setLCM(LCM_thread *lcm);

public Q_SLOTS:
    void UpdateSpeed(double s);
    void HtjaState(HTJA h);

private slots:
    void UpdateTime();
    void PlayAudio(Alert alert_type);


private:
    Ui::MainWindow *ui;
    LCM_thread *lcm_thread;
    QTimer *time;
    GScene *mScene;
    HtjaSwitch *htjaSwitch;
    bool isAlert;

    void UpdatePosition();

};
#endif // MAINWINDOW_H
