#include "mainwindow.h"
#include <QApplication>

#include "flightsmodel.h"
#include "simulatorthread.h"
#include "signalsmanager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FlightsModel flightsModel;

    MainWindow w(flightsModel);
    w.setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    w.show();

    SimulatorThread simulator(flightsModel);
    simulator.run();

    SignalsManager signalsManager;
    signalsManager.connectObjects(w, flightsModel);
    signalsManager.connectObjects(w, simulator);

    return a.exec();
}
