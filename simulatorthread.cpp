#include "simulatorthread.h"
#include "simulator.h"
#include "flightsmodel.h"

#include <QThread>



SimulatorThread::SimulatorThread(FlightsModel &model, QObject *parent) :
    QObject(parent),
    flightsModel(model)
{

}

void SimulatorThread::run()
{
    QThread * simulatorThread = new QThread();
    Simulator * simulator = new Simulator();

    simulator->moveToThread(simulatorThread);

//    connect(simulator, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(simulatorThread, SIGNAL(started()), simulator, SLOT(process()));
    connect(simulator, SIGNAL(finished()), simulatorThread, SLOT(quit()));
    connect(simulator, SIGNAL(finished()), simulator, SLOT(deleteLater()));
    connect(simulatorThread, SIGNAL(finished()), simulatorThread, SLOT(deleteLater()));

    connect(&flightsModel, FlightsModel::run, simulator, Simulator::onRun);
    connect(&flightsModel, FlightsModel::pause, simulator, Simulator::onPause);

    simulatorThread->start();
}
