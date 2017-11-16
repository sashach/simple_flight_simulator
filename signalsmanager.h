#ifndef SIGNALSMANAGER_H
#define SIGNALSMANAGER_H

#include <QObject>

class MainWindow;
class FlightsModel;
class SimulatorThread;

class SignalsManager : public QObject
{
    Q_OBJECT
public:
    explicit SignalsManager(QObject *parent = nullptr);

    void connectObjects(MainWindow & mainWindow, FlightsModel & flightsModel);
    void connectObjects(MainWindow & mainWindow, SimulatorThread & simulator);
    void connectObjects(FlightsModel & flightsModel, SimulatorThread & simulator);

signals:

public slots:
};

#endif // SIGNALSMANAGER_H
