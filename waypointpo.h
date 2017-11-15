#ifndef WAYPOINTPO_H
#define WAYPOINTPO_H

#include <QString>

class WayPointPO
{
public:
    WayPointPO();
    explicit WayPointPO(const int x, const int y, const bool _passed, const std::string & _name);

    int getX() const;
    int getY() const;
    bool isPassed() const;
    const QString & getName() const;

private:
    int screenX;
    int screenY;
    bool passed;

    QString name;
};

#endif // WAYPOINTPO_H
