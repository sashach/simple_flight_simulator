#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QMutex>

class FlightsModel;
class Flight;

class Simulator : public QObject
{
    Q_OBJECT
public:
    explicit Simulator(FlightsModel & model, QObject *parent = nullptr);

    void doSomeWork();

private:
    FlightsModel & flightsModel;

    QMutex controlLock;
    bool enabled;
    bool paused;

    void processFlights();
    void processOneFlight(Flight & flight);

signals:
    void start();

public slots:
    void process();
    void onStart();
    void onPause();
    void onStop();

};

#endif // SIMULATOR_H
