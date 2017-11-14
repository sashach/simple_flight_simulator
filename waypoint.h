#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QString>

class WayPoint
{
public:
    WayPoint();
    explicit WayPoint(const int _x, const int _y, const int _z);
    explicit WayPoint(const WayPoint & other);

    const WayPoint & operator = (const WayPoint & other);

    int getX() const;
    int getY() const;
    int getZ() const;
    bool isPassed() const;
    bool isMandatory() const;
    const QString & getName() const;

    void setPassed(const bool _passed);
    void setName(const std::string & _name);

private:
    int x;
    int y;
    int z;
    bool passed;
    bool mandatory;
    QString name;
};

#endif // WAYPOINT_H
