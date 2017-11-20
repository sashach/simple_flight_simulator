#include "mainwindow.h"
#include <QApplication>

#include "flightsmodel.h"
#include "simulatorthread.h"
#include "signalsmanager.h"

//#define STANDALONE_VERSION

#ifndef STANDALONE_VERSION
#include "netsender.h"
#include "netreceiver.h"
#include "commandscreator.h"
#include "commandsparser.h"
#include "simulatorserver.h"
#include "simulatorclient.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef STANDALONE_VERSION
    FlightsModel flightsModel;

    MainWindow mainWindow(flightsModel);
    mainWindow.setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    mainWindow.show();

    SignalsManager signalsManager;

    SimulatorThread simulator(flightsModel);
    signalsManager.connectObjects(mainWindow, flightsModel);
    signalsManager.connectObjects(mainWindow, simulator);

    simulator.run();
    int res = a.exec();
#else

    QString mode;
    if(argc > 1)
    {
        mode = argv[1];
    }

    const int port = 23235;

    SimulatorServer server(port);
    SimulatorClient client("localhost", port);

    SignalsManager signalsManager;

    CommandsCreator commandsCreator;
    CommandsParser commandsParser;

    NetReceiver netReceiver;
    NetSender netSender;
//    signalsManager.connectObjects(netSender, netReceiver);

    signalsManager.connectObjects(commandsCreator, netSender);
    signalsManager.connectObjects(netReceiver, commandsParser);

    int res = 0;
    if(mode == "server")
    {
        server.run();

        FlightsModel simulatorFlightModel;
        SimulatorThread simulator(simulatorFlightModel);

        signalsManager.connectObjectsServer(commandsParser, simulatorFlightModel);
        signalsManager.connectObjectsServer(simulatorFlightModel, commandsCreator);
        signalsManager.connectObjectsServer(commandsParser, simulator);

        signalsManager.connectObjectsServer(commandsCreator, server);
        signalsManager.connectObjectsServer(commandsParser, server);

        simulator.run();

        res = a.exec();
    }
    else if(mode == "client")
    {
        signalsManager.connectObjectsClient(commandsCreator, client);
        signalsManager.connectObjectsClient(commandsParser, client);

        client.run();

        FlightsModel flightsModel;
        MainWindow mainWindow(flightsModel);
        mainWindow.setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        mainWindow.show();

        signalsManager.connectObjectsClient(mainWindow, commandsCreator);
        signalsManager.connectObjectsClient(commandsParser, flightsModel);
        signalsManager.connectObjectsClient(commandsParser, mainWindow);

        res = a.exec();
    }

#endif

    return res;
}
