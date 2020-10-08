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
#include <QDebug>

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
    inline NodesMap getNodesMap() const { return nodes; }
    inline EdgesMap getEdgesMap() const { return edges; }

    inline void setOrient(const bool orient) { this->orient = orient; }
    inline void setNodesMap(const NodesMap nodes) { this->nodes = nodes; }
    inline void setEdgesMap(const EdgesMap edges) { this->edges = edges; }

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
    void mouseReleaseEvent(QMouseEvent *ev);
    void timerEvent(QTimerEvent *event);

private:
    int timerId;
};

#endif // GRAPH_H
