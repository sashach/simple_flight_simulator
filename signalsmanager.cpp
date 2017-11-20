#include "signalsmanager.h"

#include "mainwindow.h"
#include "flightsmodel.h"
#include "simulatorthread.h"

#include "netsender.h"
#include "netreceiver.h"
#include "commandscreator.h"
#include "commandsparser.h"

#include "simulatorserver.h"
#include "simulatorclient.h"

SignalsManager::SignalsManager(QObject *parent) : QObject(parent)
{

}

void SignalsManager::connectObjects(MainWindow & mainWindow, FlightsModel & flightsModel)
{
    connect(&mainWindow, MainWindow::generate, &flightsModel, FlightsModel::onGenerate);
    connect(&mainWindow, MainWindow::alternative, &flightsModel, FlightsModel::onOptimise);
    connect(&mainWindow, MainWindow::applyAlternative, &flightsModel, FlightsModel::onApplyAlternativeRoute);
    connect(&mainWindow, MainWindow::cancelAlternative, &flightsModel, FlightsModel::onCancelAlternativeRoute);

    connect(&flightsModel, FlightsModel::ready, &mainWindow, MainWindow::onGenerationReady);
    connect(&flightsModel, FlightsModel::alternativeRouteGenerated, &mainWindow, MainWindow::onAlternativeGenerated);
    connect(&flightsModel, FlightsModel::alternativeRouteNotGenerated, &mainWindow, MainWindow::onAlternativeNotGenerated);
}

void SignalsManager::connectObjects(MainWindow & mainWindow, SimulatorThread & simulator)
{
    connect(&mainWindow, MainWindow::run, &simulator, SimulatorThread::onStart);
    connect(&mainWindow, MainWindow::pause, &simulator, SimulatorThread::onPause, Qt::DirectConnection);
    connect(&mainWindow, MainWindow::doubleSpeed, &simulator, SimulatorThread::onDoubleSpeed, Qt::DirectConnection);
    connect(&mainWindow, MainWindow::halfSpeed, &simulator, SimulatorThread::onHalfSpeed, Qt::DirectConnection);
    connect(&mainWindow, MainWindow::normalSpeed, &simulator, SimulatorThread::onNormalSpeed, Qt::DirectConnection);
    connect(&mainWindow, MainWindow::generate, &simulator, SimulatorThread::onStop);
}

void SignalsManager::connectObjects(FlightsModel & flightsModel, SimulatorThread & simulator)
{
    connect(&flightsModel, FlightsModel::ready, &simulator, SimulatorThread::onStop, Qt::DirectConnection);
}

void SignalsManager::connectObjects(NetSender & netSender, NetReceiver & netReceiver)
{
    connect(&netSender, NetSender::send, &netReceiver, NetReceiver::onReceive);
}

void SignalsManager::connectObjects(CommandsCreator & commandsCreator, NetSender & netSender)
{
    connect(&commandsCreator, CommandsCreator::send, &netSender, NetSender::onSend);
}

void SignalsManager::connectObjects(NetReceiver & netReceiver, CommandsParser & commandsParser)
{
    connect(&netReceiver, SIGNAL(received(QByteArray*)), &commandsParser, SLOT(onReceivedCommand(QByteArray*)));
}

void SignalsManager::connectObjectsServer(CommandsParser & commandsParser, FlightsModel & flightsModel)
{
    connect(&commandsParser, CommandsParser::generateFlights, &flightsModel, FlightsModel::onGenerate);
    connect(&commandsParser, CommandsParser::alternativeRequest, &flightsModel, FlightsModel::onOptimise);
    connect(&commandsParser, CommandsParser::alternativeApply, &flightsModel, FlightsModel::onApplyAlternativeRoute);
    connect(&commandsParser, CommandsParser::alternativeCancel, &flightsModel, FlightsModel::onCancelAlternativeRoute);
}

void SignalsManager::connectObjectsServer(FlightsModel & flightsModel, CommandsCreator & commandsCreator)
{
    connect(&flightsModel, FlightsModel::readyFlights, &commandsCreator, CommandsCreator::onFlightsReady);
    connect(&flightsModel, FlightsModel::sendUpdateOneFlight, &commandsCreator, CommandsCreator::onUpdateOneFlight, Qt::DirectConnection);
    connect(&flightsModel, FlightsModel::alternativeRouteGenerated, &commandsCreator, CommandsCreator::onAlternativeRouteGenerated);
    connect(&flightsModel, FlightsModel::alternativeRouteNotGenerated, &commandsCreator, CommandsCreator::onAlternativeRouteNotGenerated);
}

void SignalsManager::connectObjectsServer(CommandsParser & commandsParser, SimulatorThread & simulator)
{
    connect(&commandsParser, CommandsParser::startGeneration, &simulator, SimulatorThread::onStart);
    connect(&commandsParser, CommandsParser::pauseGeneration, &simulator, SimulatorThread::onPause, Qt::DirectConnection);
    connect(&commandsParser, CommandsParser::halfSpeed, &simulator, SimulatorThread::onHalfSpeed, Qt::DirectConnection);
    connect(&commandsParser, CommandsParser::normalSpeed, &simulator, SimulatorThread::onNormalSpeed, Qt::DirectConnection);
    connect(&commandsParser, CommandsParser::doubleSpeed, &simulator, SimulatorThread::onDoubleSpeed, Qt::DirectConnection);
}

void SignalsManager::connectObjectsClient(CommandsParser & commandsParser, FlightsModel & flightsModel)
{
    connect(&commandsParser, CommandsParser::deleteAllFlights, &flightsModel, FlightsModel::onClearFlights);
    connect(&commandsParser, CommandsParser::updateOneFlight, &flightsModel, FlightsModel::onUpdateOneFlight, Qt::DirectConnection);
    connect(&commandsParser, CommandsParser::alternativeApply, &flightsModel, FlightsModel::onApplyAlternativeRoute);
    connect(&commandsParser, CommandsParser::alternativeCancel, &flightsModel, FlightsModel::onCancelAlternativeRoute);
}

void SignalsManager::connectObjectsClient(CommandsParser & commandsParser, MainWindow & mainWindow)
{
    connect(&commandsParser, CommandsParser::flightsReady, &mainWindow, MainWindow::onGenerationReady);
    connect(&commandsParser, CommandsParser::alternativeRouteGenerated, &mainWindow, MainWindow::onAlternativeGenerated);
    connect(&commandsParser, CommandsParser::alternativeRouteNotGenerated, &mainWindow, MainWindow::onAlternativeNotGenerated);
}

void SignalsManager::connectObjectsClient(MainWindow & mainWindow, CommandsCreator & commandsCreator)
{
    connect(&mainWindow, MainWindow::generate, &commandsCreator, CommandsCreator::onGenerateFlights);
    connect(&mainWindow, MainWindow::run, &commandsCreator, CommandsCreator::onStartGeneration);
    connect(&mainWindow, MainWindow::pause, &commandsCreator, CommandsCreator::onPauseGeneration);
    connect(&mainWindow, MainWindow::halfSpeed, &commandsCreator, CommandsCreator::onSetHalfSpeed);
    connect(&mainWindow, MainWindow::normalSpeed, &commandsCreator, CommandsCreator::onSetNormalSpeed);
    connect(&mainWindow, MainWindow::doubleSpeed, &commandsCreator, CommandsCreator::onSetDoubleSpeed);
    connect(&mainWindow, MainWindow::alternative, &commandsCreator, CommandsCreator::onAlternativeRouteRequest);
    connect(&mainWindow, MainWindow::applyAlternative, &commandsCreator, CommandsCreator::onAlternativeRouteApply);
    connect(&mainWindow, MainWindow::cancelAlternative, &commandsCreator, CommandsCreator::onAlternativeRouteCancel);
}

void SignalsManager::connectObjectsServer(CommandsCreator & commandsCreator, SimulatorServer & server)
{
    connect(&commandsCreator, SIGNAL(send(QByteArray*)), &server, SLOT(sendToClient(QByteArray*)), Qt::DirectConnection);
}

void SignalsManager::connectObjectsServer(CommandsParser & commandsParser, SimulatorServer & server)
{
    connect(&server, SIGNAL(receivedFromClient(QDataStream&)), &commandsParser, SLOT(onReceivedCommand(QDataStream&)), Qt::DirectConnection);
}

void SignalsManager::connectObjectsClient(CommandsCreator & commandsCreator, SimulatorClient & client)
{
    connect(&commandsCreator, SIGNAL(send(QByteArray*)), &client, SLOT(sendToServer(QByteArray*)), Qt::DirectConnection);
}

void SignalsManager::connectObjectsClient(CommandsParser & commandsParser, SimulatorClient & client)
{
    connect(&client, SIGNAL(receivedFromServer(QDataStream&)), &commandsParser, SLOT(onReceivedCommand(QDataStream&)), Qt::DirectConnection);
}
