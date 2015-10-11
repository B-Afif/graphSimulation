#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QTableWidget>
#include <QString>
class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QTableWidget *table, int numNodes, QWidget *parent = 0);

    void itemMoved();

    void startSim(QString alg);

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

    void scaleView(qreal scaleFactor);

private:
    QList<Node *> nodes;
    int timerId;
    int numNodes;
};

#endif
