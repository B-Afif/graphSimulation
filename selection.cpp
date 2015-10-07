#include "selection.h"
#include "ui_selection.h"
#include "graphwidget.h"
#include "simulation.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include <QStringList>

FenTable::FenTable(int num,bool oriented, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Selection)
{
    nodes=num;
    tab=ui->Table;
    ui->setupUi(this);
    ui->Table->setColumnCount(nodes);
    ui->Table->setRowCount(nodes);
    QStringList headers;
    for (int i=0; i<nodes; i++)
    {
        QString q=QString::number(i);
        headers<<q;
    }

    ui->Table->setVerticalHeaderLabels(headers);
    ui->Table->setHorizontalHeaderLabels(headers);

    for(int i=0; i<nodes; i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText("0");
        item->setBackgroundColor(Qt::gray);
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        ui->Table->setItem(i,i,item);
    }
    if (oriented)
    {
        for (int i=0; i<nodes; i++)
        {
            for (int j=i+1; j<nodes; j++)
            {
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setBackgroundColor(Qt::darkGray);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                ui->Table->setItem(i,j,item);
            }
            for (int k=0; k<i; k++)
            {
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setText("-");
                ui->Table->setItem(i,k,item);
            }
        }
    }
    else
    {
        for (int i=0; i<nodes; i++)
        {
            for (int j=0; j<nodes; j++)
            {
                if (i != j){
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setText("-");
                ui->Table->setItem(i,j,item);
                }
            }
        }
    }
    for (int i=0; i<nodes; i++)
       {
           ui->startNodeBox->addItem(QString::number(i));
           ui->finishNodeBox->addItem(QString::number(i));
       }
}

FenTable::~FenTable()
{
    delete ui;
}

void FenTable::on_Go_clicked()
{
    GraphWidget *widget = new GraphWidget(ui->Table,nodes);
    Simulation *sim = new Simulation(widget);
    sim->show();
    this->close();
}
