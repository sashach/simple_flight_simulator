#include "simulatorclient.h"

#include <unistd.h>

#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QDebug>

SimulatorClient::SimulatorClient(const QString &_host, int _port, QObject *parent) :
    QObject(parent),
    tcpSocket(nullptr),
    host(_host),
    port(_port)
{
}

void SimulatorClient::run()
{
    tcpSocket = new QTcpSocket(this);

    tcpSocket->connectToHost(host, port);

    connect(tcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(tcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()), Qt::DirectConnection);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)), Qt::DirectConnection);
}

void SimulatorClient::slotReadyRead()
{
    qDebug() << "Bytes available " << tcpSocket->bytesAvailable();
    QDataStream in(tcpSocket->readAll());
    if(in.device()->size() == 0)
    {
        qDebug() << "0 bytes received from server. Possible error";
    }
    else
    {
        qDebug() << "Got " << in.device()->size() << " bytes from server";
    }
//    QDataStream data(in.device());
    emit receivedFromServer(in);
}

void SimulatorClient::slotError(QAbstractSocket::SocketError err)
{
    qDebug() << "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(tcpSocket->errorString())
                    );
}

void SimulatorClient::sendToServer(QByteArray * data)
{
    if(!tcpSocket)
    {
        qDebug() << "Socket is null";
        return;
    }

    QByteArray out = *data;
    qint64 sentBytes = tcpSocket->write(out);
    if(sentBytes < 0)
    {
        qDebug() << "Error in send to server";
    }
    else
    {
        qDebug() << "Sent to server " << sentBytes << " bytes";
    }
}

void SimulatorClient::slotConnected()
{
    qDebug() << "Connected to server";
}
