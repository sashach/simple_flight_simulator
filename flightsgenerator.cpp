#include "flightsgenerator.h"
#include "flight.h"
#include "constants.h"
#include "waypoint.h"

#include <cstdlib>

FlightsGenerator::FlightsGenerator()
{

}

void FlightsGenerator::generate(Flight &flight, const int worldSize, const int offX)
{
    int curX = offX;
    int curY = 0;
    int curZ = 0;

    const int cellStep = worldSize / MAX_FLIGHT_POINTS;
    const int coordDiff = cellStep;

    auto addPoint = [&flight, &curX, &curY, &curZ](const std::string & name)
    {
        WayPoint point(curX, curY, curZ);
        point.setName(name);
        flight.addWayPoint(point);
    };

    addPoint("TOFF"); // take off

    const int cruiseFlightLevel = 10000;

    curX += cellStep;
    curY += cellStep;
    curZ = cruiseFlightLevel;
    addPoint("TOC"); // top of climb

    for(int i = 0; i < (MAX_FLIGHT_POINTS - 4); ++i)
    {
        curX += cellStep;
        curY = curX + ( -1 * coordDiff + std::rand() % coordDiff);
        curZ = cruiseFlightLevel + ( -500 + std::rand() % 1000);
        addPoint("PT" + std::to_string(i)); // enroute
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
