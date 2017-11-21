#-------------------------------------------------
#
# Project created by QtCreator 2017-11-14T16:53:32
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simple_flight_simulator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    flight.cpp \
    flightsgenerator.cpp \
    waypoint.cpp \
    flightsview.cpp \
    flightsviewmodel.cpp \
    flightsmodel.cpp \
    point3d.cpp \
    flightpo.cpp \
    screencoordinatescalculator.cpp \
    waypointpo.cpp \
    simulator.cpp \
    simulatorthread.cpp \
    signalsmanager.cpp \
    flightplanoptimiser.cpp \
    netreceiver.cpp \
    netsender.cpp \
    commandscreator.cpp \
    commandsparser.cpp \
    simulatorserver.cpp \
    simulatorclient.cpp \
    directservice.cpp

HEADERS += \
        mainwindow.h \
    flight.h \
    flightsgenerator.h \
    waypoint.h \
    flightsview.h \
    flightsviewmodel.h \
    flightsmodel.h \
    point3d.h \
    flightpo.h \
    screencoordinatescalculator.h \
    waypointpo.h \
    constants.h \
    simulator.h \
    simulatorthread.h \
    signalsmanager.h \
    flightplanoptimiser.h \
    netreceiver.h \
    netsender.h \
    commandscreator.h \
    commandsparser.h \
    simulatorserver.h \
    simulatorclient.h \
    directservice.h

FORMS += \
        mainwindow.ui
