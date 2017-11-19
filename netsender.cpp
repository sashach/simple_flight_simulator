#include "netsender.h"

NetSender::NetSender(QObject *parent) : QObject(parent)
{

}

void NetSender::onSend(QByteArray *data)
{
    emit send(data);
}
