#include "graphvisualisingbuttons.h"

GraphVisualisingButtons::~GraphVisualisingButtons(){
    delete graph;
}

GraphVisualisingButtons::GraphVisualisingButtons(NodesMap nodes, EdgesMap edges, bool orient, size_t width, size_t height, QWidget *parent) : QLabel(parent){
    graph = new Graph(nodes,edges,orient,this);

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
    buttonsInLabel->move(0,height * 0.8 + 1);

    addNode = addEdge = removeNode = removeEdge = false;
}

void GraphVisualisingButtons::addNodeButtonClicked(){
    if(!addNode){
        addNodeButton->setStyleSheet("background-color: silver;");
        addEdgeButton->setStyleSheet("background-color: white;");
        removeNodeButton->setStyleSheet("background-color: white;");
        removeEdgeButton->setStyleSheet("background-color: white;");
        addEdge = removeNode = removeEdge = false;
    }
    else
        addNodeButton->setStyleSheet("background-color: white;");
    addNode = !addNode;
    graph->helper(addNodeButton->text());
}

void GraphVisualisingButtons::addEdgeButtonClicked(){
    if(!addEdge){
        addNodeButton->setStyleSheet("background-color: white;");
        addEdgeButton->setStyleSheet("background-color: silver;");
        removeNodeButton->setStyleSheet("background-color: white;");
        removeEdgeButton->setStyleSheet("background-color: white;");
        addNode = removeNode = removeEdge = false;
    }
    else
        addEdgeButton->setStyleSheet("background-color: white;");
    addEdge = !addEdge;
    graph->helper(addEdgeButton->text());
}

void GraphVisualisingButtons::removeNodeButtonClicked(){
    if(!removeNode){
        addNodeButton->setStyleSheet("background-color: white;");
        addEdgeButton->setStyleSheet("background-color: white;");
        removeNodeButton->setStyleSheet("background-color: silver;");
        removeEdgeButton->setStyleSheet("background-color: white;");
        addNode = addEdge = removeEdge = false;
    }
    else
        removeNodeButton->setStyleSheet("background-color: white;");
    removeNode = !removeNode;
    graph->helper(removeNodeButton->text());
}

void GraphVisualisingButtons::removeEdgeButtonClicked(){
    if(!removeEdge){
        addNodeButton->setStyleSheet("background-color: white;");
        addEdgeButton->setStyleSheet("background-color: white;");
        removeNodeButton->setStyleSheet("background-color: white;");
        removeEdgeButton->setStyleSheet("background-color: silver;");
        addNode = addEdge = removeNode = false;
    }
    else
        removeEdgeButton->setStyleSheet("background-color: white;");
    removeEdge = !removeEdge;
    graph->helper(removeEdgeButton->text());
}
