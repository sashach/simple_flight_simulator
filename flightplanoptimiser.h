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

    bool createOptimisedCopy(QMap<int, Flight> & flights, const int flightId, const int optimisedFlightId);
    bool optimiseFlight(Flight & flight);

private:
    bool optimiseRoute(Flight & flight);

signals:

public slots:
};

#endif // FLIGHTPLANOPTIMISER_H
