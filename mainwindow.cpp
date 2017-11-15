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
    connect(&flightsModel, FlightsModel::updated, this, MainWindow::onGenerationReady);

    connect(ui->runButton, QPushButton::pressed, &flightsModel, FlightsModel::onRun);
    connect(ui->pauseButton, QPushButton::pressed, &flightsModel, FlightsModel::onPause);
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

void MainWindow::onGenerationReady()
{
    ui->runButton->setEnabled(true);
    ui->pauseButton->setEnabled(true);
    ui->speedGroupBox->setEnabled(true);
}
