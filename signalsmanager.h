#ifndef SIGNALSMANAGER_H
#define SIGNALSMANAGER_H

#include <QObject>

class MainWindow;
class FlightsModel;
class SimulatorThread;
class DirectService;

class NetSender;
class NetReceiver;

class CommandsCreator;
class CommandsParser;

class SimulatorServer;
class SimulatorClient;

class Flight;

class SignalsManager : public QObject
{
    Q_OBJECT
public:
    explicit SignalsManager(QObject *parent = nullptr);

    void connectObjects(MainWindow & mainWindow, FlightsModel & flightsModel);
    void connectObjects(MainWindow & mainWindow, SimulatorThread & simulator);
    void connectObjects(FlightsModel & flightsModel, SimulatorThread & simulator);

    void connectObjects(FlightsModel & flightsModel, DirectService & directService);

    void connectObjects(NetSender & netSender, NetReceiver & netReceiver);

    void connectObjects(CommandsCreator & commandsCreator, NetSender & netSender);
    void connectObjects(NetReceiver & netReceiver, CommandsParser & commandsParser);

    void connectObjectsClient(CommandsParser & commandsParser, MainWindow & mainWindow);

    void connectObjectsServer(DirectService & directService, CommandsCreator &commandsCreator);
    void connectObjectsServer(CommandsParser & commandsParser, DirectService & directService);

    void connectObjectsClient(FlightsModel & flightsModel, CommandsCreator & commandsCreator);
    void connectObjectsClient(CommandsParser & commandsParser, FlightsModel & flightsModel);

signals:
    void send(QByteArray * data);
    void receivedFromServer(QDataStream & in);

public slots:
    void sendToClient(QByteArray *data);
    void onReceivedCommand(QDataStream & in);
};

#endif // SIGNALSMANAGER_H
