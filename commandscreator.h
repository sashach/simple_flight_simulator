#ifndef COMMANDSCREATOR_H
#define COMMANDSCREATOR_H

#include <QObject>

#include "flight.h"

class CommandsCreator : public QObject
{
    Q_OBJECT

public:
    explicit CommandsCreator(QObject *parent = nullptr);

private:
    void sendCommand(const qint32 commandType);
    void sendOneFlightData(const Flight & flight);
    void sendSetGeneratorSpeedCommand(const qint32 speed);

signals:
    void send(QByteArray * data);

public slots:
    void onGenerateFlights();
    void onFlightsReady(const QMap <int, Flight> & flights);
    void onStartGeneration();
    void onPauseGeneration();
    void onUpdateOneFlight(const Flight & flight);
    void onSetHalfSpeed();
    void onSetNormalSpeed();
    void onSetDoubleSpeed();
    void onAlternativeRouteRequest();
    void onAlternativeRouteApply();
    void onAlternativeRouteCancel();
    void onAlternativeRouteGenerated();
    void onAlternativeRouteNotGenerated();

};

#endif // COMMANDSCREATOR_H
