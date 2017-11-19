#ifndef NETSENDER_H
#define NETSENDER_H

#include <QObject>

class NetSender : public QObject
{
    Q_OBJECT
public:
    explicit NetSender(QObject *parent = nullptr);

signals:
    void send(QByteArray * data);

public slots:
    void onSend(QByteArray * data);
};

#endif // NETSENDER_H
