#ifndef FLIGHTSGENERATOR_H
#define FLIGHTSGENERATOR_H

class Flight;

class FlightsGenerator
{
public:
    explicit FlightsGenerator();

    void generate(Flight & flight, const int worldSize);

};

#endif // FLIGHTSGENERATOR_H
