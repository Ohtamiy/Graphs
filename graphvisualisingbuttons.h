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
    GraphVisualisingButtons(NodesMap nodes, EdgesMap edges, size_t width, size_t height, QWidget *parent = NULL);
    ~GraphVisualisingButtons();

private slots:
    void addNodeButtonClicked();
    void addEdgeButtonClicked();
    void removeNodeButtonClicked();
    void removeEdgeButtonClicked();

};

#endif // GRAPHVISUALISINGBUTTONS_H
