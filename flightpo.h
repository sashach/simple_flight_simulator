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
    explicit FlightPO(const int _id = 0, QObject *parent = nullptr);
    explicit FlightPO(const FlightPO &other);

    const FlightPO & operator = (const FlightPO & other);

    void updateFlight(const Flight & flight);
    void updateScreenCoordinates(const ScreenCoordinatesCalculator & calculator);

    int getX() const;
    int getY() const;

    const QVector<WayPointPO> & getWayPoints() const;

    const QString & getAircraftId() const;
    const QString & getLabelCoordinates() const;
    const QString & getSimulatorTimeDiff() const;

    void setAltitudeInFeet(const bool val);

private:
    int id;
    Point3d relativeCoordinates;
    QVector<WayPoint> relativeWayPoints;

    int screenX;
    int screenY;
    QVector<WayPointPO> wayPoints;

    QString aircraftId;
    QString labelCoordinates;
    QString simulatorTimeDiff;

    bool altitudeInFeet;
    int climbDescent;

    void updateLabelCoordinates();

signals:

public slots:
};

#endif // FLIGHTPO_H
