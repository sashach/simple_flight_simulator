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

    enum
    {
        MAX_FLIGHTS_NUMBER = 1,
        OPTIMISER_FLIGHT_ID = 9999
    };

    void sendUpdateFlightNotification(const Flight & flight);

private:
    QMap<int, Flight> flights;
    QMutex flightsLock;
    int lastFlightId;
    int optimisedFlightId;

    void clearFlights();
    void generateFlights();
    int generateFlightId();

    void applyAlternativeRoute();

    void removeAlternativeRoute();
    void updateOneFlight(const Flight & flight);

    void sendUpdateFlightNotification(const int id);

signals:
    void updated();
    void ready();
    void run();
    void pause();
    void alternativeRouteRequest();
    void alternativeRouteGenerated();
    void alternativeRouteNotGenerated();
    void readyFlights(const QMap <int, Flight> & flights);
    void sendUpdateOneFlight(const Flight & flight);
    void optimiseFlight(const Flight & flight);

public slots:
    void onGenerate();
    void onUpdate();
    void onOptimise();
    void onApplyAlternativeRoute();
    void onCancelAlternativeRoute();
    void onClearFlights();
    void onUpdateOneFlight(const Flight & flight);
    void onFlightOptimised(const Flight & flight);
    void onFlightNotOptimised();
};

#endif // FLIGHTSMODEL_H
