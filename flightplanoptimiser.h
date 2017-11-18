#ifndef FLIGHTPLANOPTIMISER_H
#define FLIGHTPLANOPTIMISER_H

#include "flight.h"
#include <QObject>
#include <QMap>

class FlightPlanOptimiser : public QObject
{
    Q_OBJECT
public:
    explicit FlightPlanOptimiser(QObject *parent = nullptr);

    void createOptimisedCopy(QMap<int, Flight> & flights, const int flightId, const int optimisedFlightId);

private:
    void optimiseRoute(Flight & flight);

signals:

public slots:
};

#endif // FLIGHTPLANOPTIMISER_H
