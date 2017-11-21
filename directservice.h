#ifndef DIRECTSERVICE_H
#define DIRECTSERVICE_H

#include "flight.h"
#include <QObject>

class DirectService : public QObject
{
    Q_OBJECT
public:
    explicit DirectService(QObject *parent = nullptr);

private:
    Flight flightToOptimise;

    bool directFlight(Flight & optimisedFlight) const;

signals:
    void flightOptimised(const Flight & flight);
    void alternativeRouteGenerated();
    void alternativeRouteNotGenerated();

public slots:
    void onOptimise(const Flight &flight);
};

#endif // DIRECTSERVICE_H
