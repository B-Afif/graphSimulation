#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget,int i);

    void addEdge(Edge *edge);
    void addIncoming(Edge *edge);
    QList<Edge *> edges() const;
    QList<Edge *> incomingEdges() const;
    QList<Edge *> allEdges() {return edgeList + incomingEdgesList}

    enum { Type = UserType + 1 };
    int type() const Q_DECL_OVERRIDE { return Type; }

    bool advance();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void setState(int s){active=s;};
    bool isExplored(){return explored;};
    void setExplored(bool b){explored=b;};

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QList<Edge *> edgeList;
    QList<Edge *> incomingEdgesList;
    //QList<Edge *> allEdgesList;
    QList<Node *> descendants;
    QPointF newPos;
    GraphWidget *graph;
    int tag;
    int active;
    bool explored;
};

#endif
