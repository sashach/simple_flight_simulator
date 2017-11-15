#include "mainwindow.h"
#include <QApplication>

#include "flightsmodel.h"
#include "simulatorthread.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FlightsModel flightsModel;
    MainWindow w(flightsModel);
    w.show();

    SimulatorThread simulator(flightsModel);
    simulator.run();

    return a.exec();
}
