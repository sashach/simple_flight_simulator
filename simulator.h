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
    int simulationTime;
    double simulationSpeed;

    void processFlights();
    void processOneFlight(Flight & flight);

    enum
    {
        POINTS_PASSED_THRESHOLD = 10
    };

signals:
    void start();

public slots:
    void process();
    void onStart();
    void onPause();
    void onStop();
    void onDoubleSpeed();
    void onHalfSpeed();
    void onNormalSpeed();

};

#endif // SIMULATOR_H
