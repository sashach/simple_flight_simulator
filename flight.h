#ifndef FLIGHT_H
#define FLIGHT_H

#include "point3d.h"
#include "waypoint.h"

#include <QObject>
#include <QVector>
#include <QDateTime>

class Flight : public QObject
{
    Q_OBJECT
public:
    explicit Flight(const int _id = 0, const std::string & _aircraftId = "", QObject *parent = nullptr);
    explicit Flight(const Flight &other);

    const Flight & operator = (const Flight & other);

    int getId() const;

    void addWayPoint(const WayPoint & wayPoint);
    const QVector<WayPoint> & getWayPoints() const;
    QVector<WayPoint> & getWayPoints();

    void updateCoordinates(const int x, const int y, const int h);
    void updateCoordinates(const Point3d & coord);

    const Point3d & getCoordinates() const;

    int getSpeed() const;

    QDateTime getLastUpdateTime();

    const std::string & getAircraftId() const;

    void setSimulatorTimeDiff(const double timeDiff);
    double getSimulatorTimeDiff() const;

    enum
    {
        CLIMB_DESCENT_NONE = 0,
        CLIMB_DESCENT_CLIMB,
        CLIMB_DESCENT_DESCENT
    };

    int getClimbDescent() const;

private:
    int id;
    QVector<WayPoint> wayPoints;
    Point3d coordinates;
    int speed;
    QDateTime lastUpdateTime;

    std::string aircraftId;
    double simulatorTimeDiff;
    int climbDescent;

signals:

public slots:
};

#endif // FLIGHT_H
