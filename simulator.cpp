#include "simulator.h"
#include "flightsmodel.h"

#include <iostream>
#include <unistd.h>

#include <QThread>

Simulator::Simulator(QObject *parent) :
    QObject(parent)
{
}

void Simulator::process()
{
    for(int i = 0; i < 10; ++i)
    {
        std::cout << "Hello " << i << std::endl;
        usleep(500000);
//        QThread::sleep(1);
    }

    emit finished();
}

void Simulator::onRun()
{
    std::cout << "Run" << std::endl;
}

void Simulator::onPause()
{
    std::cout << "Pause" << std::endl;
}
