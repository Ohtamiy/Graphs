#include "graph.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

Graph::Graph(NodesMap nodes, EdgesMap edges, bool orient, QWidget *parent) : QLabel(parent){
    this->nodes = nodes;
    this->edges = edges;
    this->orient = orient;
    sizeOfNode = 30;
    sizeOfLoop = 35;
    edgeWidth = 3;
    loopWidth = 5;
    mouseNode = nullptr;
    state = moving;
}

void Graph::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    QPen penBlack(QBrush(Qt::black), edgeWidth);
    QPen penRed(QBrush(Qt::red), edgeWidth);
    painter.setPen(penBlack);

    foreach (Node node, nodes) {
        painter.drawEllipse(node.getX() - sizeOfNode / 2, node.getY() - sizeOfNode / 2, sizeOfNode, sizeOfNode);
        painter.setPen(penRed);
        painter.drawText(node.getX() - sizeOfNode / 4, node.getY() - sizeOfNode / 4, sizeOfNode /2, sizeOfNode / 2, Qt::AlignCenter, "x" + QString::number(node.getId()));
        painter.setPen(penBlack);
    }

    foreach (Edge edge, edges) {
        if(edge.getIn() == edge.getOut()){
            painter.drawArc(nodes[nodes.getPos(edge.getIn())].getX() - sizeOfNode, nodes[nodes.getPos(edge.getIn())].getY() - sizeOfNode, sizeOfLoop, sizeOfLoop, 10 * 16, 245 * 16);
            painter.setPen(penRed);
            painter.drawText(nodes[edge.getOut()].getX() - 50, nodes[edge.getOut()].getY() - 50,
                    sizeOfNode, sizeOfNode, Qt::AlignCenter, "y" + QString::number(edge.getId()));
            painter.setPen(penBlack);
        }
        else{
            // draw some edges at one place
            painter.drawLine(nodes[nodes.getPos(edge.getIn())].getX(), nodes[nodes.getPos(edge.getIn())].getY(),
                            nodes[nodes.getPos(edge.getOut())].getX(), nodes[nodes.getPos(edge.getOut())].getY());
            painter.setPen(penRed);
            painter.drawText((nodes[edge.getIn()].getX() + nodes[edge.getOut()].getX()) / 2,
                             (nodes[edge.getIn()].getY() + nodes[edge.getOut()].getY()) / 2,
                              sizeOfNode + 10, sizeOfNode + 10, Qt::AlignCenter, "y" + QString::number(edge.getId()));
            painter.setPen(penBlack);
        }
        if(orient){
            QLineF line(QPointF(nodes[edge.getIn()].getX(),nodes[edge.getIn()].getY()), QPointF(nodes[edge.getOut()].getX(),nodes[edge.getOut()].getY()));

            double angle = ::acos(line.dx() / line.length());
            if (line.dy() >= 0)
              angle = TwoPi - angle;

            QPointF destArrowP1 = QPointF(nodes[edge.getOut()].getX(),nodes[edge.getOut()].getY()) + QPointF(sin(angle - Pi / 3) * 15,
                                  cos(angle - Pi / 3) * 15);
            QPointF destArrowP2 = QPointF(nodes[edge.getOut()].getX(),nodes[edge.getOut()].getY()) + QPointF(sin(angle - Pi + Pi / 3) * 15,
                                  cos(angle - Pi + Pi / 3) * 15);

            painter.drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
        }
    }
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
        edgeAdding(x,y);
        break;
    case NodeRemoving:
        nodeRemoving(x,y);
        break;
    case EdgeRemoving:
        edgeRemoving(x,y);
        break;
    }
    repaint();
}

void Graph::helper(QString button){
    deleteMouseNode();
    if(button == "Add node")
        state == NodeAdding ? state = moving : state = NodeAdding;
    else if(button == "Add edge")
        state == EdgeAdding ? state = moving : state = EdgeAdding;
    else if(button == "Remove node")
        state == NodeRemoving ? state = moving : state = NodeRemoving;
    else
        state == EdgeRemoving ? state = moving : state = EdgeRemoving;
}

void Graph::nodeMoving(int x, int y){
    if(!mouseNode){
        foreach (Node node, nodes)
            if(abs( node.getX() - x ) < sizeOfNode && abs( node.getY() - y ) < sizeOfNode){
                mouseNode = new Node(node);
                break;
            }
    }
    else{
        int pos = nodes.getPos(mouseNode->getId());
        nodes[pos].setX(x);
        nodes[pos].setY(y);
        deleteMouseNode();
    }
}

void Graph::nodeAdding(int x, int y){
    bool ok = false;
    foreach (Node node, nodes) {
        if(abs( node.getX() - x ) < sizeOfNode && abs( node.getY() - y ) < sizeOfNode){
            ok = true;
            break;
        }
    }
    if(!ok)
        nodes.push_back(Node(nodes[nodes.size() - 1].getId() + 1, x, y));
}

void Graph::edgeAdding(int x, int y){
    if(!mouseNode){
        foreach (Node node, nodes)
            if(abs( node.getX() - x ) < sizeOfNode && abs( node.getY() - y ) < sizeOfNode){
                mouseNode = new Node(node);
                break;
            }
    }
    else{
        foreach (Node node, nodes)
            if(abs( node.getX() - x ) < sizeOfNode && abs( node.getY() - y ) < sizeOfNode){
                Edge edge = Edge(edges.size() + 1, mouseNode->getId(), node.getId());
                edges.push_back(edge);
                deleteMouseNode();
                break;
            }
    }
}

void Graph::nodeRemoving(int x, int y){
    foreach (Node node, nodes)
        if(abs( node.getX() - x ) < sizeOfNode && abs( node.getY() - y ) < sizeOfNode){
            foreach (Edge edge, edges)
                if(node.getId() == edge.getIn() || node.getId() == edge.getOut())
                    edges.erase(edges.begin() + edges.getPos(edge.getId()));
            nodes.erase(nodes.begin() + nodes.getPos(node.getId()));
            break;
        }
}

void Graph::edgeRemoving(int x, int y){
    if(!mouseNode){
        foreach (Node node, nodes)
            if(abs( node.getX() - x ) < sizeOfNode && abs( node.getY() - y ) < sizeOfNode){
                mouseNode = new Node(node);
                break;
            }
    }
    else{
        foreach (Node node, nodes)
            if(abs( node.getX() - x ) < sizeOfNode && abs( node.getY() - y ) < sizeOfNode)
                foreach (Edge edge, edges)
                    if((edge.getIn() == mouseNode->getId() && edge.getOut() == node.getId()) ||
                       (edge.getIn() == node.getId() && edge.getOut() == mouseNode->getId())){
                        edges.erase(edges.begin() + edges.getPos(edge.getId()));
                        deleteMouseNode();
                        break;
                    }
    }
}

void Graph::deleteMouseNode(){
    delete mouseNode;
    mouseNode = nullptr;
}
