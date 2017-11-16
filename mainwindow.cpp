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

    connect(ui->generateButton, QPushButton::pressed, this, MainWindow::onGenerate);
    connect(ui->flightsViewButton, QPushButton::pressed, this, MainWindow::onFlightsView);

    connect(ui->runButton, QPushButton::pressed, this, MainWindow::onRun);
    connect(ui->pauseButton, QPushButton::pressed, this, MainWindow::onPause);
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
    ui->pauseButton->setEnabled(false);
    ui->speedGroupBox->setEnabled(true);
}

void MainWindow::onRun()
{
    ui->runButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
    emit run();
}

void MainWindow::onPause()
{
    emit pause();
}

void MainWindow::onGenerate()
{
    emit generate();
}
