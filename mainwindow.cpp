#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stack>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    nodes.push_back(Node(0,100,100));

    graphButtons = new GraphVisualisingButtons(nodes, edges, false, 555, 560, this);
    graphButtons->move(10,10);
    graphButtons->setStyleSheet("border:none;background-color:#242b35;");

    coordVertice = { {150,100},{300,100},
                     {400,150},{400,300},
                     {300,400},{100,300},
                     {150,400},{100,150},
                     {250,250}
    };

    ui->aboveFirstMatrix->setText("Adjacency");
    ui->aboveFirstMatrix->setVisible(false);
    ui->result->setStyleSheet("border:none;color:#737373;font-size:12pt;background-color:white;border-radius:10px;");
}
MainWindow::~MainWindow()
{
    delete graphButtons;
    delete ui;
}

void MainWindow::on_vertice_valueChanged(int arg1){
    Q_UNUSED(arg1);
    SetMatrix();
}

QStringList MainWindow::createVerticalHeaderLabels(int value){
    QStringList headers;
    for(int i = 1; i <= value; i++)
        headers << "x" + QString::number(i);
    return headers;
}

QStringList MainWindow::createHorizontalHeaderLabels(int value){
    QStringList headers;
    for(int i = 1; i <= value; i++)
        headers << "y" + QString::number(i);
    return headers;
}

void MainWindow::SetMatrix(){
    ui->start->setMaximum(ui->vertice->value());
    ui->end->setMaximum(ui->vertice->value());

    ui->firstMatrix->setRowCount(ui->vertice->value());
    ui->firstMatrix->setVerticalHeaderLabels(createVerticalHeaderLabels(ui->vertice->value()));
    ui->firstMatrix->setColumnCount(ui->vertice->value());
    ui->firstMatrix->setHorizontalHeaderLabels(createVerticalHeaderLabels(ui->vertice->value()));

    setSizeForTables();
}

void MainWindow::clearFirstMatrix(){
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        for(int j = 0; j < ui->firstMatrix->columnCount(); j++)
            ui->firstMatrix->takeItem(i,j);
}

void MainWindow::fillFirstMatrix(){
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        for(int j = 0; j < ui->firstMatrix->columnCount(); j++)
            if(ui->firstMatrix->item(i,j) == NULL){
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText(QString::number(0));
                ui->firstMatrix->setItem(i,j,item);
            }
}

void MainWindow::setSizeForTables(){
    for(int i = 0; i < ui->firstMatrix->columnCount(); i++)
        ui->firstMatrix->setColumnWidth(i,ui->firstMatrix->rowHeight(0));

    ui->firstMatrix->setFixedHeight(ui->firstMatrix->rowHeight(0) * (ui->firstMatrix->rowCount() + 1));
    ui->firstMatrix->setFixedWidth(ui->firstMatrix->columnWidth(0) * (ui->firstMatrix->columnCount() + 1));
}

void MainWindow::on_clear_clicked(){
    ui->firstMatrix->clear();
    ui->vertice->setValue(0);
    ui->start->setValue(1);
    ui->end->setValue(1);
    nodes.clear();
    edges.clear();
    graphButtons->graph->setNodesMap(nodes);
    graphButtons->graph->setEdgesMap(edges);
    repaint();
    ui->result->clear();
}

void MainWindow::on_build_clicked(){
    nodes.clear();
    edges.clear();
    fillFirstMatrix();
    fromAToGraph();
    receiveNodesMap();
    graphButtons->graph->setNodesMap(nodes);
    graphButtons->graph->setEdgesMap(edges);
    graphButtons->graph->repaint();
}

void MainWindow::receiveNodesMap(){
    nodes.clear();
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++){
        if(i < (int)coordVertice.size())
            nodes.push_back(Node(nodes.newIndex(),coordVertice[i].first,coordVertice[i].second));
        else
            nodes.push_back(Node(nodes.newIndex(),coordVertice[coordVertice.size()-i].first,coordVertice[coordVertice.size()-i].second));
    }
}

void MainWindow::fromAToGraph(){
    edges.clear();
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        for(int j = 0; j < ui->firstMatrix->rowCount(); j++)
            if(ui->firstMatrix->item(i,j)->text().toInt() != 0)
                edges.push_back(Edge(ui->firstMatrix->item(i,j)->text().toInt(), i, j,0));
}

void MainWindow::on_matrix_clicked(){
    ui->aboveFirstMatrix->setVisible(true);

    ui->firstMatrix->setRowCount(graphButtons->graph->getNodesMap().size());
    ui->firstMatrix->setVerticalHeaderLabels(createVerticalHeaderLabels(graphButtons->graph->getNodesMap().size()));
    ui->firstMatrix->setColumnCount(graphButtons->graph->getNodesMap().size());
    ui->firstMatrix->setHorizontalHeaderLabels(createVerticalHeaderLabels(graphButtons->graph->getNodesMap().size()));

    clearFirstMatrix();
    fromGraphToA();
    setSizeForTables();
    fillFirstMatrix();
}

void MainWindow::fromGraphToA(){
    foreach (Edge edge, graphButtons->graph->getEdgesMap()) {
        QTableWidgetItem *item = new QTableWidgetItem;
        if(ui->firstMatrix->item(edge.getIn(),edge.getOut()) != NULL)
            item->setText(QString::number(ui->firstMatrix->item(edge.getIn(),edge.getOut())->text().toInt() + 1));
        else
            item->setText(QString::number(1));
        ui->firstMatrix->setItem(edge.getIn(),edge.getOut(),item);
    }
}

void MainWindow::on_day_pressed(){
    this->setStyleSheet("font-family: 'Arial Black', Arial, sans-serif; background-color: white;color:#737373;");
    graphButtons->setStyleSheet("background-color: #f3f3f3; border: none;border-radius:6px;color:#737373;");
    graphButtons->graph->setStyleSheet("background-color: #f3f3f3; border: none;border-radius:6px;color:#737373;");
    ui->firstMatrix->setStyleSheet("background-color:white;border:none;font-size:8pt;");
    ui->vertice->setStyleSheet("background-color: white;font-size:12pt;color:#737373;border:none;");
    ui->aboveFirstMatrix->setStyleSheet("color:#737373;font-size:12pt;border:none;");
    ui->label->setStyleSheet("color:#737373;font-size:12pt;border:none;");
    ui->VERTICE->setStyleSheet("color:#737373;font-size:12pt;border:none;");
    ui->build->setStyleSheet("border:none;background-color: rgba(109, 135, 214, 0.4);color:white;font-size:12pt;border-radius:10px;color:#737373;");
    ui->clear->setStyleSheet("border:none;background-color: rgba(109, 135, 214, 0.4);color:white;font-size:12pt;border-radius:10px;color:#737373;");
    ui->matrix->setStyleSheet("border:none;background-color: rgba(109, 135, 214, 0.4);color:white;font-size:12pt;border-radius:10px;color:#737373;");
    ui->exit->setStyleSheet("border:none;background-color: red;border-radius:10px");
    ui->night->setStyleSheet("border:none;background-color: #242b35;color:white;font-size:12pt;border-radius:9px;color:#737373;");
    ui->day->setStyleSheet("border:none;background-color:yellow;color:white;font-size:12pt;border-radius:9px;color:#737373;");
    ui->pushButton_4->setStyleSheet("border:none;background-color: white;font-size:12pt;border-radius:9px;");
    ui->pushButton_5->setStyleSheet("border:none;background-color: white;font-size:12pt;border-radius:9px;");
    ui->groupBox->setStyleSheet("border:3px solid #f3f3f3;color:#737373;font-size:12pt;background-color:#f3f3f3;border-radius:10px;");
    ui->groupBox_2->setStyleSheet("border:3px solid #f3f3f3;color:#737373;font-size:12pt;background-color:#f3f3f3;border-radius:10px;");
    ui->result->setStyleSheet("border:none;color:#737373;font-size:12pt;background-color:white;border-radius:10px;");
}

void MainWindow::on_night_clicked(){
    this->setStyleSheet("font-family: 'Arial Black', Arial, sans-serif; background-color: #242b35;");
    graphButtons->setStyleSheet("background-color: #242b35; border: none;border-radius:6px;color:#242b35;");
    graphButtons->graph->setStyleSheet("background-color: white; border: none;border-radius:6px;color:#242b35;");
    ui->firstMatrix->setStyleSheet("background-color:white; color:black;border:none;font-size:8pt;");
    ui->vertice->setStyleSheet("background-color: white;font-size:12pt;border:none;color:black;");
    ui->aboveFirstMatrix->setStyleSheet("color:white;font-size:12pt;border:none;");
    ui->label->setStyleSheet("color:white;font-size:12pt;border:none;");
    ui->VERTICE->setStyleSheet("color:white;font-size:12pt;border:none;");
    ui->build->setStyleSheet("border:none;background-color: rgba(109, 135, 214, 0.4);font-size:12pt;border-radius:10px");
    ui->clear->setStyleSheet("border:none;background-color: rgba(109, 135, 214, 0.4);font-size:12pt;border-radius:10px");
    ui->matrix->setStyleSheet("border:none;background-color: rgba(109, 135, 214, 0.4);font-size:12pt;border-radius:10px");
    ui->exit->setStyleSheet("border:none;background-color: red;border-radius:10px");
    ui->day->setStyleSheet("border:none;background-color: white;font-size:12pt;border-radius:9px;color:white;");
    ui->night->setStyleSheet("border:none;background-color: yellow;font-size:12pt;border-radius:9px; color:white;");
    ui->pushButton_4->setStyleSheet("border:none;background-color: #242b35;font-size:12pt;border-radius:9px;");
    ui->pushButton_5->setStyleSheet("border:none;background-color: #242b35;font-size:12pt;border-radius:9px;");
    ui->groupBox->setStyleSheet("border:3px solid #4c495c;color:white;font-size:12pt;");
    ui->groupBox_2->setStyleSheet("border:3px solid #4c495c;color:white;font-size:12pt;");
    ui->result->setStyleSheet("border:none;color:#737373;font-size:12pt;background-color:white;border-radius:10px;");
}

void MainWindow::on_exit_clicked(){
    close();
}
void MainWindow::on_find_clicked(){
    int start = ui->start->value()-1, size = ui->firstMatrix->columnCount();
    const int inf = 10000000;
    QVector<int> v(size, inf);
    vector<int> p(size,-1);
    v[start] = 0;
    for (int k = 1; k < size; ++k) {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j) {
                QTableWidgetItem *item = new QTableWidgetItem;
                item = ui->firstMatrix->item(j, i);
                int current_weight = 0;
                if (item->text() == "0") current_weight = 10000000;
                else current_weight = item->text().toInt();

                if (v[j] + current_weight < v[i]) {
                    v[i] = v[j] + current_weight;
                    p[i] = j;
                }
            }
    }

    vector<int> path;
    for (int cur=ui->end->value()-1; cur!=-1; cur=p[cur])
        path.push_back (cur);
    reverse (path.begin(), path.end());

    QString result;
    for (size_t i=0; i<path.size(); ++i){
        result += "x" + QString::number(path[i]+1);
        if(i+1 != path.size())
            result += " - ";
    }
    result += " = " + QString::number(v[ui->end->value()-1]);
    ui->result->setText(result);//это вывод

    on_build_clicked();

    EdgesMap pain;
    for(int i = 0; i < (int)path.size(); i++){
        foreach(Edge edge, edges){
            if(edge.getIn() == path.at(i) && i+1 < (int)path.size() && edge.getOut() == path.at(i+1)){
                edge.setColour(1);
                pain.push_back(edge);
                break;
            }
        }
    }

    foreach(Edge edge, graphButtons->graph->getEdgesMap()){
        bool ok = 0;
        foreach(Edge e, pain){
            if(e.getIn() == edge.getIn() && e.getOut() == edge.getOut())
                ok = 1;
        }
        if(!ok)
            pain.push_back(edge);
    }

    graphButtons->graph->setEdgesMap(pain);
    repaint();
}
