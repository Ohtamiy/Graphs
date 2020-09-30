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
    Graph(NodesMap nodes, EdgesMap edges, QWidget *parent = nullptr);
    void helper(string button);
    void nodeMoving(int x, int y);
    void nodeAdding(int x, int y);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // GRAPH_H
