#include "commandsparser.h"
#include "constants.h"

#include "flight.h"

#include <QDataStream>

CommandsParser::CommandsParser(QObject *parent) : QObject(parent)
{

}

void CommandsParser::onReceivedCommand(QByteArray *data)
{
    parseCommand(data);
    delete data;
}

void CommandsParser::onReceivedCommand(QDataStream & in)
{
    parseCommand(in);
}

void CommandsParser::parseCommand(QByteArray * data)
{
    QDataStream in(data, QIODevice::ReadOnly);
    parseCommand(in);
}

void CommandsParser::parseCommand(QDataStream & in)
{
    qint32 commandType;
    in >> commandType;

    switch (commandType) {
    case COMMAND_TYPE_GENERATE_FLIGHTS:
        emit generateFlights();
        break;
    case COMMAND_TYPE_DELETE_ALL_FLIGHTS:
        emit deleteAllFlights();
        break;
    case COMMAND_TYPE_UPDATE_ONE_FLIGHT:
    case COMMAND_TYPE_SEND_FLIGHT_TO_OPTIMISER:
        processUpdateOneFlight(in, commandType);
        break;
    case COMMAND_TYPE_FLIGHTS_READY:
        emit flightsReady();
        break;
    case COMMAND_TYPE_START:
        emit startGeneration();
        break;
    case COMMAND_TYPE_PAUSE:
        emit pauseGeneration();
        break;
    case COMMAND_TYPE_SET_GENERATION_SPEED:
        emit processSetGeneratorSpeed(in);
        break;
    case COMMAND_TYPE_ALTERNATIVE_ROUTE_REQUEST:
        emit alternativeRequest();
        break;
    case COMMAND_TYPE_ALTERNATIVE_ROUTE_APPLY:
        emit alternativeApply();
        break;
    case COMMAND_TYPE_ALTERNATIVE_ROUTE_CANCEL:
        emit alternativeCancel();
        break;
    case COMMAND_TYPE_ALTERNATIVE_ROUTE_GENERATED:
        emit alternativeRouteGenerated();
        break;
    case COMMAND_TYPE_ALTERNATIVE_ROUTE_NOT_GENERATED:
        emit alternativeRouteNotGenerated();
        break;
    default:
        break;
    }

    if (!in.device()->atEnd())
    {
        parseCommand(in);
    }
}

void CommandsParser::processUpdateOneFlight(QDataStream & in, qint32 commandType)
{
    qint32 id;
    QString aircraftId;
    qint32 x, y, h;
    double simulatorTimeDiff;
    qint32 wayPointsCount;

    in >> id >> aircraftId >> x >> y >> h >> simulatorTimeDiff >> wayPointsCount;

    Flight flight(int(id), std::string(aircraftId.toUtf8().constData()));
    flight.updateCoordinates(x, y, h);
    flight.setSimulatorTimeDiff(simulatorTimeDiff);

    QString wayPointName;
    bool passed, mandatory;

    for(int i = 0; i < wayPointsCount; ++i)
    {
        in >> wayPointName >> x >> y >> h >> passed >> mandatory;

        WayPoint wayPoint(x, y, h);
        wayPoint.setName(aircraftId.toUtf8().constData());
        wayPoint.setPassed(passed);
        wayPoint.setMandatory(mandatory);

        flight.addWayPoint(wayPoint);
    }

    if(commandType == COMMAND_TYPE_SEND_FLIGHT_TO_OPTIMISER)
    {
        emit optimiseFlight(flight);
    }
    else
    {
        emit updateOneFlight(flight);
    }
}

void CommandsParser::processSetGeneratorSpeed(QDataStream &in)
{
    qint32 simulatorSpeed;
    in >> simulatorSpeed;

    switch(simulatorSpeed)
    {
    case 5:
        emit halfSpeed();
        break;
    case 20:
        emit doubleSpeed();
        break;
    default:
        emit normalSpeed();
        break;
    }
}
