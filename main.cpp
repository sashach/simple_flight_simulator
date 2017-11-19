#include "mainwindow.h"
#include <QApplication>

#include "flightsmodel.h"
#include "simulatorthread.h"
#include "signalsmanager.h"

#define STANDALONE_VERSION

#ifndef STANDALONE_VERSION
#include "netsender.h"
#include "netreceiver.h"
#include "commandscreator.h"
#include "commandsparser.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FlightsModel flightsModel;

    MainWindow mainWindow(flightsModel);
    mainWindow.setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    mainWindow.show();

    SignalsManager signalsManager;

#ifdef STANDALONE_VERSION
    SimulatorThread simulator(flightsModel);
    signalsManager.connectObjects(mainWindow, flightsModel);
    signalsManager.connectObjects(mainWindow, simulator);
#else
    FlightsModel simulatorFlightModel;
    SimulatorThread simulator(simulatorFlightModel);

    NetReceiver netReceiver;
    NetSender netSender;

    signalsManager.connectObjects(netSender, netReceiver);

    CommandsCreator commandsCreator;
    CommandsParser commandsParser;

    signalsManager.connectObjects(commandsCreator, netSender);
    signalsManager.connectObjects(netReceiver, commandsParser);

    signalsManager.connectObjectsServer(commandsParser, simulatorFlightModel);
    signalsManager.connectObjectsServer(simulatorFlightModel, commandsCreator);
    signalsManager.connectObjectsServer(commandsParser, simulator);

    signalsManager.connectObjectsClient(mainWindow, commandsCreator);
    signalsManager.connectObjectsClient(commandsParser, flightsModel);
    signalsManager.connectObjectsClient(commandsParser, mainWindow);

#endif

    simulator.run();

    return a.exec();
}
