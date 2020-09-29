#ifndef GRAPH_H
#define GRAPH_H

#include <QLabel>

class Graph : public QLabel
{
public:
    Graph();
    Graph(QWidget *parent = NULL) : QLabel(parent){

    }
};

#endif // GRAPH_H
