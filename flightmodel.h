#ifndef FLIGHTMODEL_H
#define FLIGHTMODEL_H

#include <QObject>
#include <QVector>
#include <QMutex>

#include "flight.h"

class FlightModel : public QObject
{
    Q_OBJECT
public:
    explicit FlightModel(QObject *parent = nullptr);

    const QVector<Flight> & getFlights() const;

    QMutex & getLock();

    enum {
        WORLD_SIZE = 500
    };

private:
    QVector<Flight> flights;
    QMutex flightsLock;

    void clearFlights();
    void generateFlights();

signals:
    void updated();

public slots:
    void onGenerate();
};

#endif // FLIGHTMODEL_H
