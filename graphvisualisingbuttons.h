#ifndef GRAPHVISUALISINGBUTTONS_H
#define GRAPHVISUALISINGBUTTONS_H

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <graph.h>

class GraphVisualisingButtons : public QLabel
{
    Graph *graph;
    QLabel *buttonsInLabel;
    QHBoxLayout *buttons;
    QPushButton *addNodeButton, *addEdgeButton, *removeNodeButton, *removeEdgeButton;
    bool addNode, addEdge, removeNode, removeEdge;
public:
    GraphVisualisingButtons();
    GraphVisualisingButtons(size_t width, size_t height, QWidget *parent = NULL) : QLabel(parent){
        graph = new Graph(this);

        addNodeButton = new QPushButton("Add node", this);
        connect(addNodeButton, &QPushButton::clicked, this, addNodeButtonClicked);
        addEdgeButton = new QPushButton("Add edge", this);
        connect(addEdgeButton, &QPushButton::clicked, this, addEdgeButtonClicked);
        removeNodeButton = new QPushButton("Remove node", this);
        connect(removeNodeButton, &QPushButton::clicked, this, removeNodeButtonClicked);
        removeEdgeButton = new QPushButton("Remove edge", this);
        connect(removeEdgeButton, &QPushButton::clicked, this, removeEdgeButtonClicked);

        buttons = new QHBoxLayout(this);
        buttons->addWidget(addNodeButton);
        buttons->addWidget(addEdgeButton);
        buttons->addWidget(removeNodeButton);
        buttons->addWidget(removeEdgeButton);
        this->resize(width, height);

        graph->resize(width, height * 0.8);
        graph->move(0,0);

        buttonsInLabel = new QLabel(this);
        buttonsInLabel->setLayout(buttons);
        buttonsInLabel->resize(width, height * 0.2);
        buttonsInLabel->move(0,height * 0.8);

        addNode = addEdge = removeNode = removeEdge = false;
    }

private slots:
    void addNodeButtonClicked(){
        if(!addNode){
            addNodeButton->setStyleSheet("background-color: red;");
            addEdgeButton->setStyleSheet("background-color: white;");
            removeNodeButton->setStyleSheet("background-color: white;");
            removeEdgeButton->setStyleSheet("background-color: white;");
            addEdge = removeNode = removeEdge = false;
        }
        else
            addNodeButton->setStyleSheet("background-color: white;");
        addNode = !addNode;
    }
    void addEdgeButtonClicked(){
        if(!addEdge){
            addNodeButton->setStyleSheet("background-color: white;");
            addEdgeButton->setStyleSheet("background-color: red;");
            removeNodeButton->setStyleSheet("background-color: white;");
            removeEdgeButton->setStyleSheet("background-color: white;");
            addNode = removeNode = removeEdge = false;
        }
        else
            addEdgeButton->setStyleSheet("background-color: white;");
        addEdge = !addEdge;
    }
    void removeNodeButtonClicked(){
        if(!removeNode){
            addNodeButton->setStyleSheet("background-color: white;");
            addEdgeButton->setStyleSheet("background-color: white;");
            removeNodeButton->setStyleSheet("background-color: red;");
            removeEdgeButton->setStyleSheet("background-color: white;");
            addNode = addEdge = removeEdge = false;
        }
        else
            removeNodeButton->setStyleSheet("background-color: white;");
        removeNode = !removeNode;
    }
    void removeEdgeButtonClicked(){
        if(!removeEdge){
            addNodeButton->setStyleSheet("background-color: white;");
            addEdgeButton->setStyleSheet("background-color: white;");
            removeNodeButton->setStyleSheet("background-color: white;");
            removeEdgeButton->setStyleSheet("background-color: red;");
            addNode = addEdge = removeNode = false;
        }
        else
            removeEdgeButton->setStyleSheet("background-color: white;");
        removeEdge = !removeEdge;
    }
};

#endif // GRAPHVISUALISINGBUTTONS_H
