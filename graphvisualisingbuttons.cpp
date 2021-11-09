#include "graphvisualisingbuttons.h"

GraphVisualisingButtons::~GraphVisualisingButtons(){
    delete graph;
}

GraphVisualisingButtons::GraphVisualisingButtons(NodesMap nodes, EdgesMap edges, bool orient, size_t width, size_t height, QWidget *parent) : QLabel(parent){
    graph = new Graph(nodes,edges,orient,this);

    addNodeButton = new QPushButton("Add node", this);
    connect(addNodeButton, &QPushButton::clicked, this, addNodeButtonClicked);
    addNodeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    addEdgeButton = new QPushButton("Add edge", this);
    connect(addEdgeButton, &QPushButton::clicked, this, addEdgeButtonClicked);
    addEdgeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    removeNodeButton = new QPushButton("Remove node", this);
    connect(removeNodeButton, &QPushButton::clicked, this, removeNodeButtonClicked);
    removeNodeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    removeEdgeButton = new QPushButton("Remove edge", this);
    connect(removeEdgeButton, &QPushButton::clicked, this, removeEdgeButtonClicked);
    removeEdgeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    addNodeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:white; border-radius:10px;font-size:12pt");
    addEdgeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:white; border-radius:10px;font-size:12pt");
    removeNodeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:white; border-radius:10px;font-size:12pt");
    removeEdgeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:white; border-radius:10px;font-size:12pt");
    buttons = new QHBoxLayout(this);
    buttons->addWidget(addNodeButton);
    buttons->addWidget(addEdgeButton);
    buttons->addWidget(removeNodeButton);
    buttons->addWidget(removeEdgeButton);
    this->resize(width, height);

    graph->resize(width, height * 0.91);
    graph->setStyleSheet("background-color:white;");
    //можно подвигать (не в начало координат)
    graph->move(10,10);

    buttonsInLabel = new QLabel(this);

    buttonsInLabel->setLayout(buttons);
    buttonsInLabel->resize(width, height * 0.09);
    buttonsInLabel->move(5,height * 0.91 + 1);

    addNode = addEdge = removeNode = removeEdge = false;
}

void GraphVisualisingButtons::addNodeButtonClicked(){
    if(!addNode){
        addNodeButton->setStyleSheet("background-color:#FF7800; color:#737373; border-radius:10px;font-size:12pt");
        addEdgeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        removeNodeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        removeEdgeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        addEdge = removeNode = removeEdge = false;
    }
    else
        addNodeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
    addNode = !addNode;
    graph->helper(addNodeButton->text());
}

void GraphVisualisingButtons::addEdgeButtonClicked(){
    if(!addEdge){
        addNodeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        addEdgeButton->setStyleSheet("background-color:#FF7800; color:#737373; border-radius:10px;font-size:12pt");
        removeNodeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        removeEdgeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        addNode = removeNode = removeEdge = false;
    }
    else
        addEdgeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
    addEdge = !addEdge;
    graph->helper(addEdgeButton->text());
}

void GraphVisualisingButtons::removeNodeButtonClicked(){
    if(!removeNode){
        addNodeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        addEdgeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        removeNodeButton->setStyleSheet("background-color:#FF7800; color:#737373; border-radius:10px;font-size:12pt");
        removeEdgeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        addNode = addEdge = removeEdge = false;
    }
    else
        removeNodeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
    removeNode = !removeNode;
    graph->helper(removeNodeButton->text());
}

void GraphVisualisingButtons::removeEdgeButtonClicked(){
    if(!removeEdge){
        addNodeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        addEdgeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        removeNodeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
        removeEdgeButton->setStyleSheet("background-color:#FF7800; color:#737373; border-radius:10px;font-size:12pt");
        addNode = addEdge = removeNode = false;
    }
    else
        removeEdgeButton->setStyleSheet("background-color:rgba(109, 135, 214, 0.4); color:#737373; border-radius:10px;font-size:12pt");
    removeEdge = !removeEdge;
    graph->helper(removeEdgeButton->text());
}
