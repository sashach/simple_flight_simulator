#ifndef FLIGHTSGENERATOR_H
#define FLIGHTSGENERATOR_H

class Flight;

class FlightsGenerator
{
public:
    explicit FlightsGenerator();

    void generate(Flight & flight, const int worldSize, const int offX = 0);

};

#endif // FLIGHTSGENERATOR_H
