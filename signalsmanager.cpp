#include "signalsmanager.h"

#include "mainwindow.h"
#include "flightsmodel.h"
#include "simulatorthread.h"
#include "directservice.h"

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
    connect(&mainWindow, SIGNAL(generate()), &simulator, SLOT(onStop()), Qt::DirectConnection);
}

void SignalsManager::connectObjects(FlightsModel & flightsModel, SimulatorThread & simulator)
{
    connect(&flightsModel, SIGNAL(ready()), &simulator, SLOT(onStop()), Qt::DirectConnection);
}

void SignalsManager::connectObjects(FlightsModel & flightsModel, DirectService & directService)
{
    connect(&flightsModel, SIGNAL(optimiseFlight(const Flight&)), &directService, SLOT(onOptimise(const Flight&)));
    connect(&directService, SIGNAL(flightOptimised(const Flight&)), &flightsModel, SLOT(onFlightOptimised(const Flight&)));
    connect(&directService, SIGNAL(flightWasNotOptimised()), &flightsModel, SLOT(onFlightNotOptimised()));
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

void SignalsManager::connectObjectsClient(FlightsModel & flightsModel, CommandsCreator & commandsCreator)
{
    connect(&flightsModel, SIGNAL(optimiseFlight(Flight)), &commandsCreator, SLOT(onSendFlightToOptimiser(Flight)), Qt::DirectConnection);
    connect(&flightsModel, SIGNAL(alternativeRouteRequest()), &commandsCreator, SLOT(onAlternativeRouteRequest()));
}

void SignalsManager::connectObjectsClient(CommandsParser & commandsParser, FlightsModel & flightsModel)
{
    connect(&commandsParser, SIGNAL(updateOneFlight(Flight)), &flightsModel, SLOT(onUpdateOneFlight(Flight)), Qt::DirectConnection);
    connect(&commandsParser, SIGNAL(alternativeApply()), &flightsModel, SLOT(onApplyAlternativeRoute()));
    connect(&commandsParser, SIGNAL(alternativeCancel()), &flightsModel, SLOT(onCancelAlternativeRoute()));
}

void SignalsManager::connectObjectsServer(CommandsParser & commandsParser, DirectService & directService)
{
    connect(&commandsParser, SIGNAL(optimiseFlight(const Flight&)), &directService, SLOT(onOptimise(const Flight&)));
}

void SignalsManager::connectObjectsClient(CommandsParser & commandsParser, MainWindow & mainWindow)
{
    connect(&commandsParser, SIGNAL(alternativeRouteGenerated()), &mainWindow, SLOT(onAlternativeGenerated()));
    connect(&commandsParser, SIGNAL(alternativeRouteNotGenerated()), &mainWindow, SLOT(onAlternativeNotGenerated()));
}

void SignalsManager::sendToClient(QByteArray *data)
{
    emit send(data);
}

void SignalsManager::onReceivedCommand(QDataStream & in)
{
    emit receivedFromServer(in);
}

void SignalsManager::connectObjectsServer(DirectService & directService, CommandsCreator & commandsCreator)
{
    connect(&directService, SIGNAL(flightOptimised(const Flight&)), &commandsCreator, SLOT(onUpdateOneFlight(const Flight)));
    connect(&directService, SIGNAL(alternativeRouteGenerated()), &commandsCreator, SLOT(onAlternativeRouteGenerated()));
    connect(&directService, SIGNAL(alternativeRouteNotGenerated()), &commandsCreator, SLOT(onAlternativeRouteNotGenerated()));
}
