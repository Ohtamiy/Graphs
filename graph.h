#ifndef GRAPH_H
#define GRAPH_H

#include <QLabel>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <node.h>
#include <nodesmap.h>
#include <edgesmap.h>

class Graph : public QLabel
{
    bool orient;
    NodesMap nodes;
    EdgesMap edges;
    sizeObj sizeOfNode, sizeOfLoop, edgeWidth, loopWidth;
    Node *mouseNode;
    enum mouse{
        none,
        moving,
        NodeAdding,
        EdgeAdding,
        NodeRemoving,
        EdgeRemoving
    } state;

public:
    void setOrient(bool orient) { this->orient = orient; }
    Graph(NodesMap nodes, EdgesMap edges, bool orient, QWidget *parent = nullptr);
    void helper(QString button);
    void nodeMoving(int x, int y);
    void nodeAdding(int x, int y);
    void edgeAdding(int x, int y);
    void nodeRemoving(int x, int y);
    void edgeRemoving(int x, int y);
    void deleteMouseNode();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

};

#endif // GRAPH_H
