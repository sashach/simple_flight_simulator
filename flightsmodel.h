#ifndef FLIGHTSMODEL_H
#define FLIGHTSMODEL_H

#include <QObject>
#include <QMap>
#include <QMutex>

#include "flight.h"

class FlightsModel : public QObject
{
    Q_OBJECT
public:
    explicit FlightsModel(QObject *parent = nullptr);

    const QMap <int, Flight> & getFlights() const;
    QMap<int, Flight> & getFlights();

    QMutex & getLock();

private:
    QMap<int, Flight> flights;
    QMutex flightsLock;

    void clearFlights();
    void generateFlights();

signals:
    void updated();
    void ready();
    void run();
    void pause();

public slots:
    void onGenerate();
    void onUpdate();
};

#endif // FLIGHTSMODEL_H
