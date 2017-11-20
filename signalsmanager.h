#ifndef SIGNALSMANAGER_H
#define SIGNALSMANAGER_H

#include <QObject>

class MainWindow;
class FlightsModel;
class SimulatorThread;

class NetSender;
class NetReceiver;

class CommandsCreator;
class CommandsParser;

class SimulatorServer;
class SimulatorClient;

class SignalsManager : public QObject
{
    Q_OBJECT
public:
    explicit SignalsManager(QObject *parent = nullptr);

    void connectObjects(MainWindow & mainWindow, FlightsModel & flightsModel);
    void connectObjects(MainWindow & mainWindow, SimulatorThread & simulator);
    void connectObjects(FlightsModel & flightsModel, SimulatorThread & simulator);

    void connectObjects(NetSender & netSender, NetReceiver & netReceiver);

    void connectObjects(CommandsCreator & commandsCreator, NetSender & netSender);
    void connectObjects(NetReceiver & netReceiver, CommandsParser & commandsParser);

    void connectObjectsServer(CommandsParser & commandsParser, FlightsModel & flightsModel);
    void connectObjectsServer(FlightsModel & flightsModel, CommandsCreator & commandsCreator);
    void connectObjectsServer(CommandsParser & commandsParser, SimulatorThread & simulator);

    void connectObjectsClient(MainWindow & mainWindow, CommandsCreator & commandsCreator);
    void connectObjectsClient(CommandsParser & commandsParser, FlightsModel & flightsModel);
    void connectObjectsClient(CommandsParser & commandsParser, MainWindow & flightsModel);

    void connectObjectsServer(CommandsCreator & commandsCreator, SimulatorServer & server);
    void connectObjectsServer(CommandsParser & commandsParser, SimulatorServer & server);

    void connectObjectsClient(CommandsCreator & commandsCreator, SimulatorClient & client);
    void connectObjectsClient(CommandsParser & commandsParser, SimulatorClient & client);

signals:

public slots:
};

#endif // SIGNALSMANAGER_H
