#include "mainwindow.h"
#include "htja_switch.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    LCM_thread LCM_THREAD;
    w.setLCM(&LCM_THREAD);
    LCM_THREAD.start();

    return a.exec();
}
