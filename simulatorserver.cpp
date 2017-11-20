#include "simulatorserver.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>

SimulatorServer::SimulatorServer(int _port, QObject *parent) :
    QObject(parent),
    tcpServer(nullptr),
    port(_port),
    clientSocket(nullptr)
{
}

SimulatorServer::~SimulatorServer()
{
    if(tcpServer)
    {
        tcpServer->close();
    }
}

void SimulatorServer::run()
{
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              + tcpServer->errorString()
                             );
        tcpServer->close();
        return;
    }
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

void SimulatorServer::slotNewConnection()
{
    clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()), Qt::DirectConnection);
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()), Qt::DirectConnection);
}

void SimulatorServer::slotReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    if(!clientSocket)
    {
        qDebug() << "no client socket is available";
        return;
    }
    qDebug() << "Bytes available " << clientSocket->bytesAvailable();
    QDataStream in(clientSocket->readAll());
    if(in.device()->size() == 0)
    {
        qDebug() << "0 bytes received from client. Possible error";
    }
    else
    {
        qDebug() << "Got " << in.device()->size() << " bytes from client";
    }
//    QDataStream data(in.device());
    emit receivedFromClient(in);
}

void SimulatorServer::sendToClient(QByteArray * data)
{
    if(!clientSocket)
    {
        qDebug() << "Socket is null";
        return;
    }

    QByteArray out = *data;
    qint64 sentBytes = clientSocket->write(out);
    if(sentBytes < 0)
    {
        qDebug() << "Error in send to client";
    }
    else
    {
        qDebug() << "Sent to client " << sentBytes << " bytes";
    }
}
