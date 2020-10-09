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
    timerId = 0;
}

void Graph::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    QPen penBlue(QBrush(Qt::blue), edgeWidth);
    QPen penRed(QBrush(Qt::red), edgeWidth);
    painter.setPen(penBlue);
    painter.setRenderHint(QPainter::Antialiasing);

    foreach (Node node, nodes) {
        painter.drawEllipse(node.getX() - sizeOfNode / 2, node.getY() - sizeOfNode / 2, sizeOfNode, sizeOfNode);
        painter.setPen(penRed);

        painter.drawText(node.getX() + sizeOfNode - 5, node.getY() - sizeOfNode / 2, sizeOfNode / 2, sizeOfNode / 2, Qt::AlignCenter, "x" + QString::number(node.getId() + 1));
        painter.setPen(penBlue);
    }

    EdgesMap nedges;

    foreach (Edge edge, edges) {
        if(orient){
            QLineF line;
            if(edge.getIn() == edge.getOut())
                line = QLineF(QPointF(nodes[edge.getOut()].getX()+5,nodes[edge.getOut()].getY() - 50), QPointF(nodes[edge.getOut()].getX()+5,nodes[edge.getOut()].getY() - 30));
            else
                line = QLineF(QPointF(nodes[edge.getIn()].getX(),nodes[edge.getIn()].getY()), QPointF(nodes[edge.getOut()].getX(),nodes[edge.getOut()].getY()));

            double angle = ::acos(line.dx() / line.length());
            if (line.dy() >= 0)
              angle = TwoPi - angle;

            QPointF destArrowP1 = QPointF(nodes[edge.getOut()].getX(),nodes[edge.getOut()].getY()) + QPointF(sin(angle - Pi / 3) * 15,
                                                                                                             cos(angle - Pi / 3) * 15);
            QPointF destArrowP2 = QPointF(nodes[edge.getOut()].getX(),nodes[edge.getOut()].getY()) + QPointF(sin(angle - Pi + Pi / 3) * 15,
                                                                                                             cos(angle - Pi + Pi / 3) * 15);

            painter.setPen(penRed);
            painter.drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
            painter.setPen(penBlue);
        }

        int i = 0;
        int hei = 15;
        if(edge.getIn() == edge.getOut()){
            painter.drawArc(nodes[edge.getIn()].getX() - sizeOfNode, nodes[edge.getIn()].getY() - sizeOfNode, sizeOfLoop, sizeOfLoop, 10 * 16, 245 * 16);
            painter.setPen(penRed);
            painter.drawText(nodes[edge.getOut()].getX() - 50, nodes[edge.getOut()].getY() - 50,
                    sizeOfNode, sizeOfNode, Qt::AlignCenter, "y" + QString::number(edge.getId() + 1));
            painter.setPen(penBlue);
        }
        else{
            for(int j = edges.getPos(edge.getId()) + 1; j < (int)edges.size(); j++){
                if((edge.getIn() == edges.at(j).getIn() && edge.getOut() == edges.at(j).getOut()) ||
                   (edge.getIn() == edges.at(j).getOut() && edge.getOut() == edges.at(j).getIn())){
                    QPainterPath path;

                    path.moveTo(nodes[edges.at(j).getIn()].getX(), nodes[edges.at(j).getIn()].getY());
                    if(i % 2 == 0){
                        path.cubicTo(nodes[edges.at(j).getIn()].getX(), nodes[edges.at(j).getIn()].getY(),
                                    (nodes[edges.at(j).getIn()].getX() + nodes[edges.at(j).getOut()].getX()) / 2 + hei,
                                    (nodes[edges.at(j).getIn()].getY() + nodes[edges.at(j).getOut()].getY()) / 2 + hei,
                                    nodes[edges.at(j).getOut()].getX(), nodes[edges.at(j).getOut()].getY());

                        painter.setPen(penRed);
                        painter.drawText((nodes[edges.at(j).getIn()].getX() + nodes[edges.at(j).getOut()].getX()) / 2 + hei,
                                        (nodes[edges.at(j).getIn()].getY() + nodes[edges.at(j).getOut()].getY()) / 2 + hei,
                                        sizeOfNode + 10, sizeOfNode + 10, Qt::AlignCenter, "y" + QString::number(edges.at(j).getId() + 1));
                    }
                    else{
                        path.cubicTo(nodes[edges.at(j).getIn()].getX(), nodes[edges.at(j).getIn()].getY(),
                                    (nodes[edges.at(j).getIn()].getX() + nodes[edges.at(j).getOut()].getX()) / 2 - hei,
                                    (nodes[edges.at(j).getIn()].getY() + nodes[edges.at(j).getOut()].getY()) / 2 - hei,
                                    nodes[edges.at(j).getOut()].getX(), nodes[edges.at(j).getOut()].getY());

                        painter.setPen(penRed);
                        painter.drawText((nodes[edges.at(j).getIn()].getX() + nodes[edges.at(j).getOut()].getX()) / 2 - hei,
                                        (nodes[edges.at(j).getIn()].getY() + nodes[edges.at(j).getOut()].getY()) / 2 - hei,
                                        sizeOfNode - 10, sizeOfNode - 10, Qt::AlignCenter, "y" + QString::number(edges.at(j).getId() + 1));
                    }
                    painter.setPen(penRed);
                    painter.drawPath(path);
                    painter.setPen(penBlue);

                    hei+=15;
                    i++;

                    nedges.push_back(edges.at(j));
                    edges.erase(edges.begin() + edges.getPos(edges.at(j).getId()));
                }
            }

            painter.drawLine(nodes[edge.getIn()].getX(), nodes[edge.getIn()].getY(),
                            nodes[edge.getOut()].getX(), nodes[edge.getOut()].getY());
            painter.setPen(penRed);

            painter.drawText((nodes[edge.getIn()].getX() + nodes[edge.getOut()].getX()) / 2,
                            (nodes[edge.getIn()].getY() + nodes[edge.getOut()].getY()) / 2,
                            sizeOfNode + 10, sizeOfNode + 10, Qt::AlignCenter, "y" + QString::number(edge.getId() + 1));
            painter.setPen(penBlue);
        }
    }

    foreach (Edge edge, nedges)
        edges.insert(edges.findToInsert(edges.newIndex()),edge);
    nedges.clear();
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

    QCursor cursor;

    int pos = nodes.getPos(mouseNode->getId());
    nodes[pos].setX(cursor.pos().x() - 350);
    nodes[pos].setY(cursor.pos().y() - 225);

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
                    edges.insert(edges.findToInsert(edges.newIndex()),Edge(edges.newIndex(), mouseNode->getId(), node.getId()));
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
