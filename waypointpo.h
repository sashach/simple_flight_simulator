#ifndef WAYPOINTPO_H
#define WAYPOINTPO_H

#include "point3d.h"
#include <QString>

class WayPointPO
{
public:
    WayPointPO();
    explicit WayPointPO(const int x, const int y, const int h, const bool _passed, const std::string & _name);

    const Point3d & getCoordinates() const;
    bool isPassed() const;
    const QString & getName() const;
    const QString & getLabelString2() const;

private:
    Point3d coordinates;
    bool passed;

    QString name;
    QString labelRow2;
};

#endif // WAYPOINTPO_H
