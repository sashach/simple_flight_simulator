#ifndef CONSTANTS_H
#define CONSTANTS_H

    enum
    {
        MAX_FLIGHT_POINTS = 12,
        WORLD_SIZE = 550,
        GRID_SIZE = 10
    };

    enum CommandsTypes
    {
        COMMAND_TYPE_NONE = 0,
        COMMAND_TYPE_GENERATE_FLIGHTS,
        COMMAND_TYPE_DELETE_ALL_FLIGHTS,
        COMMAND_TYPE_UPDATE_ONE_FLIGHT,
        COMMAND_TYPE_FLIGHTS_READY,
        COMMAND_TYPE_START,
        COMMAND_TYPE_PAUSE,
        COMMAND_TYPE_SET_GENERATION_SPEED,
        COMMAND_TYPE_ALTERNATIVE_ROUTE_REQUEST,
        COMMAND_TYPE_ALTERNATIVE_ROUTE_APPLY,
        COMMAND_TYPE_ALTERNATIVE_ROUTE_CANCEL,
        COMMAND_TYPE_ALTERNATIVE_ROUTE_GENERATED,
        COMMAND_TYPE_ALTERNATIVE_ROUTE_NOT_GENERATED,

    };

#endif // CONSTANTS_H
