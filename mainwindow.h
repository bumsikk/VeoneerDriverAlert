#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lcm_thread.h"
#include <QPainter>
#include <QPixmap>
#include <QDir>
#include <QDebug>
#include <QTransform>
#include <QtMath>
#include"htja_switch.h"

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
    void HtjaState(QString h);

private slots:
    void UpdateTime();


private:
    Ui::MainWindow *ui;
    LCM_thread *lcm_thread;
    QTimer *time;
    GScene *mScene;
    HtjaSwitch *htjaSwitch;
};
#endif // MAINWINDOW_H
