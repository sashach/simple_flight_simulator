#include "netreceiver.h"

NetReceiver::NetReceiver(QObject *parent) : QObject(parent)
{

}

void NetReceiver::onReceive(QByteArray * data)
{
    emit received(data);
}
