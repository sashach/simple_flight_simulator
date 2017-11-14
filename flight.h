#ifndef FLIGHT_H
#define FLIGHT_H

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

    enum
    {
        MAX_FLIGHT_POINTS = 12
    };

    void addWayPoint(const WayPoint & wayPoint);
    const QVector<WayPoint> & getWayPoints() const;

    void updateFlightPosition(const int _x, const int _y, const int _h);

    int getX() const;
    int getY() const;
    int getH() const;

private:
    QVector<WayPoint> wayPoints;
    int x;
    int y;
    int h;

signals:

public slots:
};

#endif // FLIGHT_H
