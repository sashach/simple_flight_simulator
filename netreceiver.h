#ifndef NETRECEIVER_H
#define NETRECEIVER_H

#include <QObject>

class NetReceiver : public QObject
{
    Q_OBJECT
public:
    explicit NetReceiver(QObject *parent = nullptr);

signals:
    void received(QByteArray * data);

public slots:
    void onReceive(QByteArray * data);
};

#endif // NETRECEIVER_H
