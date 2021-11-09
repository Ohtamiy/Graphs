#include "graph.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

Graph::Graph(NodesMap nodes, EdgesMap edges, bool orient, QWidget *parent) : QLabel(parent){
    this->nodes = nodes;
    this->edges = edges;
    this->orient = orient;
    sizeOfNode = 13;
    sizeOfLoop = 35;
    sizeOfNodeNew = 50;
    sizeOfLoopNew = 55;
    edgeWidth = 3;
    mouseNode = nullptr;
    state = moving;
    timerId = 0;
}

void Graph::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen penBlue(QBrush(Qt::blue), edgeWidth);
    QPen penBlack(QBrush(Qt::black), edgeWidth);
    QPen penMagenta(QBrush(Qt::magenta), edgeWidth);
    painter.setPen(penBlue);

    int i = 0;
    foreach (Edge edge, edges){   
        if(edge.getColour())
            painter.setPen(penMagenta);

        QLineF line;
        painter.drawLine(nodes[edge.getIn()].getX(), nodes[edge.getIn()].getY(),
                nodes[edge.getOut()].getX(), nodes[edge.getOut()].getY());

        painter.drawText((nodes[edge.getIn()].getX() + nodes[edge.getOut()].getX()) / 2,
                (nodes[edge.getIn()].getY() + nodes[edge.getOut()].getY()) / 2,
                sizeOfNode, sizeOfNode, Qt::AlignCenter, QString::number(edge.getId()));

        line = QLineF(QPointF(nodes[edge.getIn()].getX(),nodes[edge.getIn()].getY()),
                QPointF(nodes[edge.getOut()].getX(),nodes[edge.getOut()].getY()));

        double angle = ::acos(line.dx() / line.length());
        if (line.dy() >= 0)
          angle = TwoPi - angle;
        QPointF destArrowP1 = QPointF(nodes[edge.getOut()].getX(),nodes[edge.getOut()].getY()) + QPointF(sin(angle - Pi / 3) * 15,
                                                                                                         cos(angle - Pi / 3) * 15);
        QPointF destArrowP2 = QPointF(nodes[edge.getOut()].getX(),nodes[edge.getOut()].getY()) + QPointF(sin(angle - Pi + Pi / 3) * 15,
                                                                                                         cos(angle - Pi + Pi / 3) * 15);
        painter.drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);

        painter.setPen(penBlue);
    }

    painter.setPen(penBlack);
    painter.setBrush(Qt::black);
    i = 0;
    foreach (Node node, nodes) {
        painter.drawEllipse(node.getX() - sizeOfNode / 2, node.getY() - sizeOfNode / 2, sizeOfNode, sizeOfNode);
        painter.drawText(node.getX() + sizeOfNode - 5, node.getY() - sizeOfNode / 2, 30 + 2, 30 + 2, Qt::AlignCenter, "x" + QString::number(++i));
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

void Graph::mouseReleaseEvent(QMouseEvent *ev){
    Q_UNUSED(ev);
    killTimer(timerId);
    timerId = 0;
    if(state == moving)
        deleteMouseNode();
}

void Graph::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);

    if(mouseNode){
        QCursor cursor;
        int pos = nodes.getPos(mouseNode->getId());
        nodes[pos].setX(cursor.pos().x() - 400);
        nodes[pos].setY(cursor.pos().y() - 225);
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
        if(!mouseNode)
            return;
    }

    if(!timerId)
        timerId = startTimer(17);
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
        nodes.insert(nodes.findToInsert(nodes.newIndex()),Node(nodes.newIndex(), x, y));
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
                bool ok = false;
                if(mouseNode->getId() == node.getId())
                    foreach (Edge edge, edges)
                        if((edge.getIn() == mouseNode->getId() && edge.getOut() == node.getId()) ||
                           (edge.getOut() == mouseNode->getId() && edge.getIn() == node.getId())){
                            ok = true;
                            break;
                        }
                if(!ok)
                    edges.insert(edges.findToInsert(edges.newIndex()),Edge(edges.newIndex(), mouseNode->getId(), node.getId(), 0));
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
