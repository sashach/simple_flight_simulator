#ifndef SIMULATORCLIENT_H
#define SIMULATORCLIENT_H

#include <QObject>
#include <QAbstractSocket>

class QTcpSocket;

class SimulatorClient : public QObject
{
    Q_OBJECT
public:
    explicit SimulatorClient(const QString& _host, int _port, QObject *parent = nullptr);

    void run();

private:
    QTcpSocket* tcpSocket;
    QString host;
    int port;

signals:
    void receivedFromServer(QDataStream & in);

public slots:

private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void sendToServer(QByteArray *data);
    void slotConnected();
};

#endif // SIMULATORCLIENT_H
