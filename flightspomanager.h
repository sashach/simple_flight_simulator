#ifndef FLIGHTSPOMANAGER_H
#define FLIGHTSPOMANAGER_H

#include <QObject>
#include "flight.h"

class FlightsPOManager : public QObject
{
    Q_OBJECT
public:
    explicit FlightsPOManager(QObject *parent = nullptr);

    void clearFlights();
    void addFlight(const Flight & flight);
    const QVector<Flight> & getFlights() const;

private:
    QVector<Flight> flights;

signals:

public slots:
};

#endif // FLIGHTSPOMANAGER_H
