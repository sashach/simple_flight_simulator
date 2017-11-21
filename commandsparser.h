#ifndef COMMANDSPARSER_H
#define COMMANDSPARSER_H

#include <QObject>
class Flight;

class CommandsParser : public QObject
{
    Q_OBJECT
public:
    explicit CommandsParser(QObject *parent = nullptr);

private:
    void parseCommand(QByteArray * data);
    void parseCommand(QDataStream & in);
    void processUpdateOneFlight(QDataStream &in, qint32 commandType);
    void processSetGeneratorSpeed(QDataStream &in);

signals:
    void generateFlights();
    void deleteAllFlights();
    void updateOneFlight(const Flight & flight);
    void optimiseFlight(const Flight & flight);
    void flightsReady();
    void startGeneration();
    void pauseGeneration();
    void halfSpeed();
    void normalSpeed();
    void doubleSpeed();
    void alternativeRequest();
    void alternativeApply();
    void alternativeCancel();
    void alternativeRouteGenerated();
    void alternativeRouteNotGenerated();


public slots:
    void onReceivedCommand(QByteArray * data);
    void onReceivedCommand(QDataStream & in);
};

#endif // COMMANDSPARSER_H
