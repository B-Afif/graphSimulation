#ifndef SIMULATION_H
#define SIMULATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "graphwidget.h"

class Simulation : public QWidget
{
    Q_OBJECT
public:
    explicit Simulation(GraphWidget *graphwidget, QWidget *parent = 0);

signals:

public slots:
    void on_bouton_clicked();

private:
    QPushButton *button;
    GraphWidget *graphwidget;
};

#endif
