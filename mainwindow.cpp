#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flightsmodel.h"
#include "flightsview.h"



MainWindow::MainWindow(FlightsModel &model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    flightsModel(model)
{
    ui->setupUi(this);

    connect(ui->generateButton, QPushButton::pressed, &flightsModel, FlightsModel::onGenerate);
    connect(ui->flightsViewButton, QPushButton::pressed, this, MainWindow::onFlightsView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFlightsView()
{
    FlightsView *flightsView = new FlightsView(flightsModel, this);

    flightsView->setGeometry(QRect(100, 100, 700, 700));
    flightsView->show();
}
