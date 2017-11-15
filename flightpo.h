#ifndef FLIGHTPO_H
#define FLIGHTPO_H

#include "point3d.h"
#include "waypoint.h"
#include "waypointpo.h"

#include <QObject>
#include <QVector>

class Flight;
class ScreenCoordinatesCalculator;

class FlightPO : public QObject
{
    Q_OBJECT
public:
    explicit FlightPO(QObject *parent = nullptr);
    explicit FlightPO(const FlightPO &other);

    const FlightPO & operator = (const FlightPO & other);

    void updateFlight(const Flight & flight);
    void updateScreenCoordinates(const ScreenCoordinatesCalculator & calculator);

    int getX() const;
    int getY() const;

    const QVector<WayPointPO> & getWayPoints() const;

private:
    Point3d relativeCoordinates;
    QVector<WayPoint> relativeWayPoints;

    int screenX;
    int screenY;
    QVector<WayPointPO> wayPoints;

signals:

public slots:
};

#endif // FLIGHTPO_H
