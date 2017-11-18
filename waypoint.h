#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "point3d.h"

#include <string>

class WayPoint
{
public:
    WayPoint();
    explicit WayPoint(const int x, const int y, const int h);
    explicit WayPoint(const WayPoint & other);

    const WayPoint & operator = (const WayPoint & other);

    const Point3d & getCoordinates() const;
    bool isPassed() const;
    bool isMandatory() const;
    const std::string & getName() const;

    void setPassed(const bool _passed);
    void setName(const std::string & _name);
    void setMandatory(const bool _mandatory);
private:
    Point3d coordinates;
    bool passed;
    bool mandatory;
    std::string name;
};

#endif // WAYPOINT_H
