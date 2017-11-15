#include "mainwindow.h"
#include <QApplication>

#include "flightsmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FlightsModel flightsModel;

    MainWindow w(flightsModel);
    w.show();

    return a.exec();
}
