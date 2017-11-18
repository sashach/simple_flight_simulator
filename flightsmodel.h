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
        OPTIMISER_FLIGHT_ID = 9999
    };

private:
    QMap<int, Flight> flights;
    QMutex flightsLock;
    int lastFlightId;
    int optimisedFlightId;

    void clearFlights();
    void generateFlights();
    void optimiseFlight();
    int generateFlightId();

    void applyAlternativeRoute();

    void removeAlternativeRoute();

signals:
    void updated();
    void ready();
    void run();
    void pause();
    void alternativeRouteGenerated();

public slots:
    void onGenerate();
    void onUpdate();
    void onOptimise();
    void onApplyAlternativeRoute();
    void onCancelAlternativeRoute();
};

#endif // FLIGHTSMODEL_H
