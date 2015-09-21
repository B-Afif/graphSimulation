#include "simulation.h"

Simulation::Simulation(GraphWidget *graph, QWidget *parent) : QWidget(parent)
{
    graphwidget=graph;
    this->resize(1000,650);
    QVBoxLayout *vlayout= new QVBoxLayout;
    QHBoxLayout *hlayout= new QHBoxLayout;
    vlayout->addWidget(graphwidget);
    button = new QPushButton("Démarrer la simulation");
    hlayout->addSpacing(400);
    hlayout->addWidget(button,Qt::AlignCenter);
    hlayout->addSpacing(400);
    vlayout->addLayout(hlayout);
    this->setLayout(vlayout);
    connect(button, SIGNAL (clicked()), this, SLOT (on_bouton_clicked()));
}

void Simulation::on_bouton_clicked()
{
    graphwidget->startSim();
}

