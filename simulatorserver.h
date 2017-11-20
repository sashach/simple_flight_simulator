#ifndef SIMULATORSERVER_H
#define SIMULATORSERVER_H

#include <QObject>

class QTcpServer;
class QTcpSocket;

class SimulatorServer : public QObject
{
    Q_OBJECT
public:
    explicit SimulatorServer(int _port, QObject *parent = nullptr);
    ~SimulatorServer();

    void run();

private:
    QTcpServer* tcpServer;
    int         port;
    QTcpSocket* clientSocket;

signals:
    void receivedFromClient(QDataStream & in);

public slots:
    virtual void slotNewConnection();
    void slotReadClient();
    void sendToClient(QByteArray *data);
};

#endif // SIMULATORSERVER_H
