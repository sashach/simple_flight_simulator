#include "signalsmanager.h"

#include "mainwindow.h"
#include "flightsmodel.h"
#include "simulatorthread.h"


SignalsManager::SignalsManager(QObject *parent) : QObject(parent)
{

}

void SignalsManager::connectObjects(MainWindow & mainWindow, FlightsModel & flightsModel)
{
    connect(&mainWindow, MainWindow::generate, &flightsModel, FlightsModel::onGenerate);
    connect(&flightsModel, FlightsModel::ready, &mainWindow, MainWindow::onGenerationReady);
}

void SignalsManager::connectObjects(MainWindow & mainWindow, SimulatorThread & simulator)
{
    connect(&mainWindow, MainWindow::run, &simulator, SimulatorThread::onStart);
    connect(&mainWindow, MainWindow::pause, &simulator, SimulatorThread::onPause, Qt::DirectConnection);
}

void SignalsManager::connectObjects(FlightsModel & flightsModel, SimulatorThread & simulator)
{
    connect(&flightsModel, FlightsModel::ready, &simulator, SimulatorThread::onStop, Qt::DirectConnection);
}
