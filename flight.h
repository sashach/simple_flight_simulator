#ifndef FLIGHT_H
#define FLIGHT_H

#include "point3d.h"
#include "waypoint.h"

#include <QObject>
#include <QVector>

class Flight : public QObject
{
    Q_OBJECT
public:
    explicit Flight(QObject *parent = nullptr);
    explicit Flight(const Flight &other);

    const Flight & operator = (const Flight & other);

    void addWayPoint(const WayPoint & wayPoint);
    const QVector<WayPoint> & getWayPoints() const;

    void updateCoordinates(const int x, const int y, const int h);

    const Point3d & getCoordinates() const;

private:
    QVector<WayPoint> wayPoints;
    Point3d coordinates;

signals:

public slots:
};

#endif // FLIGHT_H
