#include "mainwindow.h"
#include <QApplication>

#include "flightsmodel.h"
#include "simulatorthread.h"
#include "signalsmanager.h"
#include "directservice.h"

//#define STANDALONE_VERSION
#define WITH_TCP

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

    DirectService directService;
    signalsManager.connectObjects(flightsModel, directService);

    simulator.run();
    int res = a.exec();
#else

    QString mode;
    if(argc > 1)
    {
        mode = argv[1];
    }

#ifdef WITH_TCP
    const int port = 23235;

    SimulatorServer server(port);
    SimulatorClient client("localhost", port);
#endif

    CommandsCreator commandsCreator;
    CommandsParser commandsParser;

    NetReceiver netReceiver;
    NetSender netSender;

    SignalsManager signalsManager;

    signalsManager.connectObjects(commandsCreator, netSender);
    signalsManager.connectObjects(netReceiver, commandsParser);
#ifndef WITH_TCP
    signalsManager.connectObjects(netSender, netReceiver);
#endif

    int res = 0;
#ifdef WITH_TCP
    if(mode == "server")
    {
        server.run();

        signalsManager.connectObjectsServer(commandsCreator, server);
        signalsManager.connectObjectsServer(server, commandsParser);
#endif

        DirectService directService;
        signalsManager.connectObjectsServer(directService, commandsCreator);
        signalsManager.connectObjectsServer(commandsParser, directService);

#ifdef WITH_TCP
        res = a.exec();
    }
    else if(mode == "client")
    {
//        client.run();

        signalsManager.connectObjectsClient(commandsCreator, client);
        signalsManager.connectObjectsClient(client, commandsParser);
#endif

        FlightsModel flightsModel;
        MainWindow mainWindow(flightsModel);
        mainWindow.setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        mainWindow.show();

        signalsManager.connectObjectsClient(flightsModel, commandsCreator);
        signalsManager.connectObjectsClient(commandsParser, flightsModel);
        signalsManager.connectObjectsClient(commandsParser, mainWindow);
        signalsManager.connectObjectsClient(flightsModel, client);

        SimulatorThread simulator(flightsModel);
        signalsManager.connectObjects(mainWindow, flightsModel);
        signalsManager.connectObjects(mainWindow, simulator);

        simulator.run();

        res = a.exec();
#ifdef WITH_TCP
    }
#endif

#endif

    return res;
}
