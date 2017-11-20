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
    connect(&mainWindow, SIGNAL(generate()), &flightsModel, SLOT(onGenerate()));
    connect(&mainWindow, SIGNAL(alternative()), &flightsModel, SLOT(onOptimise()));
    connect(&mainWindow, SIGNAL(applyAlternative()), &flightsModel, SLOT(onApplyAlternativeRoute()));
    connect(&mainWindow, SIGNAL(cancelAlternative()), &flightsModel, SLOT(onCancelAlternativeRoute()));

    connect(&flightsModel, SIGNAL(ready()), &mainWindow, SLOT(onGenerationReady()));
    connect(&flightsModel, SIGNAL(alternativeRouteGenerated()), &mainWindow, SLOT(onAlternativeGenerated()));
    connect(&flightsModel, SIGNAL(alternativeRouteNotGenerated()), &mainWindow, SLOT(onAlternativeNotGenerated()));
}

void SignalsManager::connectObjects(MainWindow & mainWindow, SimulatorThread & simulator)
{
    connect(&mainWindow, SIGNAL(run()), &simulator, SLOT(onStart()));
    connect(&mainWindow, SIGNAL(pause()), &simulator, SLOT(onPause()), Qt::DirectConnection);
    connect(&mainWindow, SIGNAL(doubleSpeed()), &simulator, SLOT(onDoubleSpeed()), Qt::DirectConnection);
    connect(&mainWindow, SIGNAL(halfSpeed()), &simulator, SLOT(onHalfSpeed()), Qt::DirectConnection);
    connect(&mainWindow, SIGNAL(normalSpeed()), &simulator, SLOT(onNormalSpeed()), Qt::DirectConnection);
    connect(&mainWindow, SIGNAL(generate()), &simulator, SLOT(onStop()));
}

void SignalsManager::connectObjects(FlightsModel & flightsModel, SimulatorThread & simulator)
{
    connect(&flightsModel, SIGNAL(ready()), &simulator, SLOT(onStop()), Qt::DirectConnection);
}

void SignalsManager::connectObjects(NetSender & netSender, NetReceiver & netReceiver)
{
    connect(&netSender, SIGNAL(send(QByteArray*)), &netReceiver, SLOT(onReceive(QByteArray*)));
}

void SignalsManager::connectObjects(CommandsCreator & commandsCreator, NetSender & netSender)
{
    connect(&commandsCreator, SIGNAL(send(QByteArray*)), &netSender, SLOT(onSend(QByteArray*)));
}

void SignalsManager::connectObjects(NetReceiver & netReceiver, CommandsParser & commandsParser)
{
    connect(&netReceiver, SIGNAL(received(QByteArray*)), &commandsParser, SLOT(onReceivedCommand(QByteArray*)));
}

void SignalsManager::connectObjectsServer(CommandsParser & commandsParser, FlightsModel & flightsModel)
{
    connect(&commandsParser, SIGNAL(generateFlights()), &flightsModel, SLOT(onGenerate()));
    connect(&commandsParser, SIGNAL(alternativeRequest()), &flightsModel, SLOT(onOptimise()));
    connect(&commandsParser, SIGNAL(alternativeApply()), &flightsModel, SLOT(onApplyAlternativeRoute()));
    connect(&commandsParser, SIGNAL(alternativeCancel()), &flightsModel, SLOT(onCancelAlternativeRoute()));
}

void SignalsManager::connectObjectsServer(FlightsModel & flightsModel, CommandsCreator & commandsCreator)
{
    connect(&flightsModel, SIGNAL(readyFlights(QMap<int,Flight>)), &commandsCreator, SLOT(onFlightsReady(QMap<int,Flight>)));
    connect(&flightsModel, SIGNAL(sendUpdateOneFlight(Flight)), &commandsCreator, SLOT(onUpdateOneFlight(Flight)), Qt::DirectConnection);
    connect(&flightsModel, SIGNAL(alternativeRouteGenerated()), &commandsCreator, SLOT(onAlternativeRouteGenerated()));
    connect(&flightsModel, SIGNAL(alternativeRouteNotGenerated()), &commandsCreator, SLOT(onAlternativeRouteNotGenerated()));
}

void SignalsManager::connectObjectsServer(CommandsParser & commandsParser, SimulatorThread & simulator)
{
    connect(&commandsParser, SIGNAL(startGeneration()), &simulator, SLOT(onStart()));
    connect(&commandsParser, SIGNAL(pauseGeneration()), &simulator, SLOT(onPause()), Qt::DirectConnection);
    connect(&commandsParser, SIGNAL(halfSpeed()), &simulator, SLOT(onHalfSpeed()), Qt::DirectConnection);
    connect(&commandsParser, SIGNAL(normalSpeed()), &simulator, SLOT(onNormalSpeed()), Qt::DirectConnection);
    connect(&commandsParser, SIGNAL(doubleSpeed()), &simulator, SLOT(onDoubleSpeed()), Qt::DirectConnection);
}

void SignalsManager::connectObjectsClient(CommandsParser & commandsParser, FlightsModel & flightsModel)
{
    connect(&commandsParser, SIGNAL(deleteAllFlights()), &flightsModel, SLOT(onClearFlights()));
    connect(&commandsParser, SIGNAL(updateOneFlight(Flight)), &flightsModel, SLOT(onUpdateOneFlight(Flight)), Qt::DirectConnection);
    connect(&commandsParser, SIGNAL(alternativeApply()), &flightsModel, SLOT(onApplyAlternativeRoute()));
    connect(&commandsParser, SIGNAL(alternativeCancel()), &flightsModel, SLOT(onCancelAlternativeRoute()));
}

void SignalsManager::connectObjectsClient(CommandsParser & commandsParser, MainWindow & mainWindow)
{
    connect(&commandsParser, SIGNAL(flightsReady()), &mainWindow, SLOT(onGenerationReady()));
    connect(&commandsParser, SIGNAL(alternativeRouteGenerated()), &mainWindow, SLOT(onAlternativeGenerated()));
    connect(&commandsParser, SIGNAL(alternativeRouteNotGenerated()), &mainWindow, SLOT(onAlternativeNotGenerated()));
}

void SignalsManager::connectObjectsClient(MainWindow & mainWindow, CommandsCreator & commandsCreator)
{
    connect(&mainWindow, SIGNAL(generate()), &commandsCreator, SLOT(onGenerateFlights()));
    connect(&mainWindow, SIGNAL(run()), &commandsCreator, SLOT(onStartGeneration()));
    connect(&mainWindow, SIGNAL(pause()), &commandsCreator, SLOT(onPauseGeneration()));
    connect(&mainWindow, SIGNAL(halfSpeed()), &commandsCreator, SLOT(onSetHalfSpeed()));
    connect(&mainWindow, SIGNAL(normalSpeed()), &commandsCreator, SLOT(onSetNormalSpeed()));
    connect(&mainWindow, SIGNAL(doubleSpeed()), &commandsCreator, SLOT(onSetDoubleSpeed()));
    connect(&mainWindow, SIGNAL(alternative()), &commandsCreator, SLOT(onAlternativeRouteRequest()));
    connect(&mainWindow, SIGNAL(applyAlternative()), &commandsCreator, SLOT(onAlternativeRouteApply()));
    connect(&mainWindow, SIGNAL(cancelAlternative()), &commandsCreator, SLOT(onAlternativeRouteCancel()));
}

void SignalsManager::connectObjectsServer(CommandsCreator & commandsCreator, SimulatorServer & server)
{
    connect(&commandsCreator, SIGNAL(send(QByteArray*)), this, SLOT(sendToClient(QByteArray*)), Qt::DirectConnection);
    connect(this, SIGNAL(send(QByteArray*)), &server, SLOT(sendToClient(QByteArray*)), Qt::DirectConnection);
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
    connect(&client, SIGNAL(receivedFromServer(QDataStream&)), this, SLOT(onReceivedCommand(QDataStream&)), Qt::DirectConnection);
    connect(this, SIGNAL(receivedFromServer(QDataStream&)), &commandsParser, SLOT(onReceivedCommand(QDataStream&)), Qt::DirectConnection);
}

void SignalsManager::sendToClient(QByteArray *data)
{
    emit send(data);
}

void SignalsManager::onReceivedCommand(QDataStream & in)
{
    emit receivedFromServer(in);
}
