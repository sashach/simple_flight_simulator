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
    connect(&mainWindow, MainWindow::doubleSpeed, &simulator, SimulatorThread::onDoubleSpeed, Qt::DirectConnection);
    connect(&mainWindow, MainWindow::halfSpeed, &simulator, SimulatorThread::onHalfSpeed, Qt::DirectConnection);
    connect(&mainWindow, MainWindow::normalSpeed, &simulator, SimulatorThread::onNormalSpeed, Qt::DirectConnection);
}

void SignalsManager::connectObjects(FlightsModel & flightsModel, SimulatorThread & simulator)
{
    connect(&flightsModel, FlightsModel::ready, &simulator, SimulatorThread::onStop, Qt::DirectConnection);
}
