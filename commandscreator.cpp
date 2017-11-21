#include "commandscreator.h"
#include "constants.h"

#include <QDataStream>
#include <QMap>

CommandsCreator::CommandsCreator(QObject *parent) : QObject(parent)
{

}

void CommandsCreator::sendCommand(const qint32 commandType)
{
    QByteArray  *data = new QByteArray();
    QDataStream out(data, QIODevice::ReadWrite);

    out << commandType;

    emit send(data);
}

void CommandsCreator::onGenerateFlights()
{
    sendCommand(COMMAND_TYPE_GENERATE_FLIGHTS);
}

void CommandsCreator::onFlightsReady(const QMap<int, Flight> &flights)
{
    sendCommand(COMMAND_TYPE_DELETE_ALL_FLIGHTS);

    for(auto it = flights.begin(); it != flights.end(); ++it)
    {
        sendOneFlightData(it.value(), COMMAND_TYPE_UPDATE_ONE_FLIGHT);
    }

    sendCommand(COMMAND_TYPE_FLIGHTS_READY);
}

void CommandsCreator::sendOneFlightData(const Flight & flight, qint32 commandType)
{
    QByteArray  *data = new QByteArray();
    QDataStream out(data, QIODevice::ReadWrite);

    out << commandType;

    out << qint32(flight.getId());
    out << QString(flight.getAircraftId().c_str());
    out << qint32(flight.getCoordinates().getX());
    out << qint32(flight.getCoordinates().getY());
    out << qint32(flight.getCoordinates().getH());
    out << flight.getSimulatorTimeDiff();

    out << qint32(flight.getWayPoints().size());
    for(auto it = flight.getWayPoints().begin(); it != flight.getWayPoints().end(); ++it)
    {
        out << QString(it->getName().c_str());
        out << qint32(it->getCoordinates().getX());
        out << qint32(it->getCoordinates().getY());
        out << qint32(it->getCoordinates().getH());
        out << it->isPassed();
        out << it->isMandatory();
    }

    emit send(data);
}

void CommandsCreator::onStartGeneration()
{
    sendCommand(COMMAND_TYPE_START);
}

void CommandsCreator::onPauseGeneration()
{
    sendCommand(COMMAND_TYPE_PAUSE);
}

void CommandsCreator::onUpdateOneFlight(const Flight & flight)
{
    sendOneFlightData(flight, COMMAND_TYPE_UPDATE_ONE_FLIGHT);
}

void CommandsCreator::onSendFlightToOptimiser(const Flight & flight)
{
    sendOneFlightData(flight, COMMAND_TYPE_SEND_FLIGHT_TO_OPTIMISER);
}

void CommandsCreator::sendSetGeneratorSpeedCommand(const qint32 speed)
{
    QByteArray  *data = new QByteArray();
    QDataStream out(data, QIODevice::ReadWrite);

    out << qint32(COMMAND_TYPE_SET_GENERATION_SPEED);
    out << speed;

    emit send(data);
}

void CommandsCreator::onSetHalfSpeed()
{
    sendSetGeneratorSpeedCommand(5);
}

void CommandsCreator::onSetNormalSpeed()
{
    sendSetGeneratorSpeedCommand(10);
}

void CommandsCreator::onSetDoubleSpeed()
{
    sendSetGeneratorSpeedCommand(20);
}

void CommandsCreator::onAlternativeRouteRequest()
{
    sendCommand(COMMAND_TYPE_ALTERNATIVE_ROUTE_REQUEST);
}

void CommandsCreator::onAlternativeRouteApply()
{
    sendCommand(COMMAND_TYPE_ALTERNATIVE_ROUTE_APPLY);
}

void CommandsCreator::onAlternativeRouteCancel()
{
    sendCommand(COMMAND_TYPE_ALTERNATIVE_ROUTE_CANCEL);
}

void CommandsCreator::onAlternativeRouteGenerated()
{
    sendCommand(COMMAND_TYPE_ALTERNATIVE_ROUTE_GENERATED);
}

void CommandsCreator::onAlternativeRouteNotGenerated()
{
    sendCommand(COMMAND_TYPE_ALTERNATIVE_ROUTE_NOT_GENERATED);
}
