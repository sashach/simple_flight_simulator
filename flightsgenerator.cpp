#include "flightsgenerator.h"
#include "flight.h"
#include "constants.h"
#include "waypoint.h"

#include <cstdlib>

FlightsGenerator::FlightsGenerator()
{

}

void FlightsGenerator::generate(Flight &flight, const int worldSize)
{
    int curX = 0;
    int curY = 0;
    int curZ = 0;

    const int cellStep = worldSize / MAX_FLIGHT_POINTS;
    const int coordDiff = cellStep;

    auto addPoint = [&flight, &curX, &curY, &curZ](const std::string & name, const bool passed = false)
    {
        WayPoint point(curX, curY, curZ);
        point.setPassed(passed);
        point.setName(name);
        flight.addWayPoint(point);
    };

    addPoint("TOFF", true); // take off

    const int cruiseFlightLevel = 10000;

    curX += cellStep;
    curY += cellStep;
    curZ = cruiseFlightLevel;
    addPoint("TOC", true); // top of climb

    for(int i = 0; i < (MAX_FLIGHT_POINTS - 4); ++i)
    {
        curX += cellStep;
        curY = curX + ( -1 * coordDiff + std::rand() % coordDiff);
        curZ = cruiseFlightLevel + ( -500 + std::rand() % 1000);
        addPoint("PT" + std::to_string(i), i < 4); // enroute
    }

    curX += cellStep;
    curY = worldSize - cellStep;
    curZ = cruiseFlightLevel;
    addPoint("TOD"); // top of descent

    curX = worldSize;
    curY = worldSize;
    curZ = 0;
    addPoint("LAND"); // landing
}
