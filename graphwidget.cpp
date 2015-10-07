#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include "delay.h"

#include <math.h>

#include <QKeyEvent>
#include <QQueue>

GraphWidget::GraphWidget(QTableWidget *table,int som, QWidget *parent)
    : QGraphicsView(parent)
{
    numNodes=som;
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 1200, 720
                        );
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Simulation"));
    int factor=100;
    if (numNodes<19) factor=200;
    for(int i=0;i<numNodes;i++)
    {
        nodes << new Node(this,i);
        scene->addItem(nodes[i]);
        if (i==0)
        {
            nodes[i]->setPos(50,360);
        }
        else if ((i-1)%4 == 0)
        {
            if (i==numNodes-1)
            {
                nodes[i]->setPos(((i-1)/4)*factor+factor+50,360);
            }
            else
            nodes[i]->setPos(((i-1)/4)*factor+factor+50,100);
        }
        else if ((((i-2)%4 == 0)&&(i!=numNodes-1)))
        {
            nodes[i]->setPos(((i-1)/4)*factor+factor+50,273);
        }
        else if ((((i-3)%4 == 0)&&(i!=numNodes-1)))
        {
            nodes[i]->setPos(((i-1)/4)*factor+factor+50,447);
        }
        else if ((((i-4)%4 == 0)&&(i!=numNodes-1)))
        {
            nodes[i]->setPos(((i-1)/4)*factor+factor+50,620);
        }
        else if (i==numNodes-1)
        {
            nodes[i]->setPos(((i-1)/4)*factor+2*factor+50,360);
        }
    }

    for(int i=0;i<numNodes;i++)
    {
        for(int j=0;j<numNodes;j++)
        {
            int value = table->item(i,j)->text().toInt();
            if((table->item(i,j)->text() != "-") && (value!=0))
            {
              scene->addItem(new Edge(nodes[i], nodes[j],value));
            }
        }
    }
}

void GraphWidget::startSim()
{
    /*for (int i=0; i<numNodes; i++)
    {
        nodes[i]->setState(0);
        if(i>0) nodes[i-1]->update();
        nodes[i]->update();
        Delay(1000);
        nodes[i]->setState(-1);
        nodes[i]->update();
    }*/
    /*foreach(Edge *e,nodes[2]->edges())
    {
        if(e->destNode()==nodes[4])
        {
            e->setState(1);
            e->update();
        }
    }*/
    QQueue<Node *> Q;
    Q.enqueue(nodes[0]);
    nodes[0]->setExplored(true);
    while (!Q.isEmpty())
    {
        Node *n = Q.dequeue();
        n->setState(0);
        //if(i>0) nodes[i-1]->update();
        n->update();
        Delay(1000);
        n->setState(-1);
        n->update();
        foreach(Edge *e, n->allEdges())
        {
            if(e->is)
        }

    }
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

#ifndef QT_NO_WHEELEVENT
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
