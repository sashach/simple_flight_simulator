#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flightmodel.h"
#include "flightsview.h"



MainWindow::MainWindow(FlightModel &model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    flightsModel(model)
{
    ui->setupUi(this);

    connect(ui->generateButton, QPushButton::pressed, &flightsModel, FlightModel::onGenerate);
    connect(ui->flightsViewButton, QPushButton::pressed, this, MainWindow::onFlightsView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFlightsView()
{
    FlightsView *flightsView = new FlightsView(flightsModel, this);

    connect(&flightsModel, FlightModel::updated, flightsView, FlightsView::onModelUpdated);

    flightsView->setGeometry(QRect(100, 100, 700, 700));
    flightsView->show();
}
