#include "graph.h"

Graph::Graph(NodesMap nodes, EdgesMap edges, QWidget *parent) : QLabel(parent){
    this->nodes = nodes;
    this->edges = edges;
    sizeOfNode = 25;
    sizeOfLoop = 25;
    edgeWidth = 3;
    loopWidth = 5;
    mouseNode = nullptr;
    state = moving;


}

void Graph::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pen(QBrush(Qt::black), edgeWidth);
    painter.setPen(pen);

    foreach (Node node, nodes) {
        painter.drawEllipse(node.getX() - sizeOfNode / 2, node.getY() - sizeOfNode / 2, sizeOfNode, sizeOfNode);
        painter.drawText(node.getX() - sizeOfNode / 4, node.getY() - sizeOfNode / 4, sizeOfNode / 2, sizeOfNode / 2, Qt::AlignCenter, "x" + QString::number(node.getId()));
    }



    //painter.drawEllipse(nodes[0].getX(),nodes[0].getY(),sizeOfNode,sizeOfNode);

//    painter.drawEllipse(200,100,sizeOfNode,sizeOfNode);

//    painter.drawEllipse(400,400,sizeOfNode,sizeOfNode);

//    painter.drawEllipse(350,100,sizeOfNode,sizeOfNode);

//    painter.drawLine(100,200,200,100);

//    painter.drawLine(100,200,350,100);

//    painter.drawLine(400,400,100,200);

}

void Graph::mousePressEvent(QMouseEvent *event){
    int x = event->x(), y = event->y();
    switch (state) {
    case none: return;
    case moving:
        nodeMoving(x,y);
        break;
    case NodeAdding:
        nodeAdding(x,y);
        break;
    case EdgeAdding:

        break;
    case NodeRemoving:

        break;
    case EdgeRemoving:

        break;
    }
    repaint();
}

void Graph::nodeMoving(int x, int y){
    if(!mouseNode){
        foreach (Node node, nodes)
            if(abs( node.getX() - x ) < sizeOfNode && abs( node.getY() - y ) < sizeOfNode){
                mouseNode = new Node(node);
            }
    }
    else{
        int pos = nodes.getPos(mouseNode->getId());

        nodes[pos].setX(x);
        nodes[pos].setY(y);

        delete mouseNode;
        mouseNode = nullptr;
    }
}

void Graph::helper(string button){
    delete mouseNode;
    mouseNode = nullptr;
    if(button == "Add node")
        state == NodeAdding ? state = moving : state = NodeAdding;
    else if(button == "Add edge")
        state == EdgeAdding ? state = moving : state = EdgeAdding;
    else if(button == "Remove node")
        state == NodeRemoving ? state = moving : state = NodeRemoving;
    else
        state == EdgeRemoving ? state = moving : state = EdgeRemoving;
}

void Graph::nodeAdding(int x, int y){
    nodes.push_back(Node(nodes[nodes.size() - 1].getId() + 1, x, y));
}
