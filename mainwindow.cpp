#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nodes.push_back(Node(0,100,100));
    edges.push_back(Edge(0,0,0));
    orient = false;

    graphButtons = new GraphVisualisingButtons(nodes, edges, orient, 600, 600, this);
    graphButtons->setStyleSheet("border: 1px solid black;");
}

MainWindow::~MainWindow()
{
    delete graphButtons;
    delete ui;
}

void MainWindow::on_vertice_valueChanged(int arg1){
    Q_UNUSED(arg1);
    on_operation_currentIndexChanged(ui->operation->currentIndex());
}

int MainWindow::countColumns(){
    int columnCount = 0;
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        for(int j = 0; j < ui->firstMatrix->columnCount(); j++)
            columnCount += ui->firstMatrix->item(i,j)->text().toInt();
    return columnCount;
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

void MainWindow::on_operation_currentIndexChanged(int index){
    if(index == 0){
        on_clear_clicked();
        return;
    }
    ui->firstMatrix->setRowCount(ui->vertice->value());
    ui->secondMatrix->setRowCount(ui->vertice->value());
    ui->firstMatrix->setVerticalHeaderLabels(createVerticalHeaderLabels(ui->vertice->value()));
    ui->secondMatrix->setVerticalHeaderLabels(createVerticalHeaderLabels(ui->vertice->value()));
    switch (index){
    case 1:
        ui->arc->setEnabled(true);
        incidence = true;
        ui->firstMatrix->setColumnCount(ui->arc->value());
        ui->secondMatrix->setColumnCount(ui->vertice->value());
        ui->firstMatrix->setHorizontalHeaderLabels(createHorizontalHeaderLabels(ui->arc->value()));
        ui->secondMatrix->setHorizontalHeaderLabels(createVerticalHeaderLabels(ui->vertice->value()));
        ui->aboveFirstMatrix->setText("Incidence");
        ui->aboveSecondMatrix->setText("Adjacency");
        ui->secondMatrix->setEditTriggers(QAbstractItemView::NoEditTriggers);
        break;
    case 2:
        ui->arc->setEnabled(false);
        incidence = false;
        ui->firstMatrix->setColumnCount(ui->vertice->value());
        ui->firstMatrix->setHorizontalHeaderLabels(createVerticalHeaderLabels(ui->vertice->value()));
        ui->aboveFirstMatrix->setText("Adjacency");
        ui->aboveSecondMatrix->setText("Incidence");
        ui->secondMatrix->setEditTriggers(QAbstractItemView::NoEditTriggers);
        break;
    default: break;
    }
    setSizeForTables();
}

void MainWindow::fromItoA(int orient){
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        for(int j = 0; j < ui->firstMatrix->columnCount(); j++)
            if(ui->firstMatrix->item(i,j)->text().toInt() == 1){
                for(int k = 0; k < ui->firstMatrix->rowCount(); k++){
                    if(k != i && ui->firstMatrix->item(k,j)->text().toInt() == orient){
                        QTableWidgetItem *item = new QTableWidgetItem;
                        if(ui->secondMatrix->item(i,k) != NULL)
                            item->setText(QString::number(ui->secondMatrix->item(i,k)->text().toInt() + 1));
                        else
                            item->setText(QString::number(1));
                        ui->secondMatrix->setItem(i,k,item);
                        break;
                    }
                }
            }
            else if(ui->firstMatrix->item(i,j)->text().toInt() == 2){
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText(QString::number(1));
                ui->secondMatrix->setItem(i,i,item);
            }
}

void MainWindow::fromAtoIor(){
    ui->secondMatrix->setColumnCount(countColumns());
    ui->secondMatrix->setHorizontalHeaderLabels(createHorizontalHeaderLabels(ui->secondMatrix->columnCount()));
    int column = 0;
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        for(int j = 0; j < ui->firstMatrix->columnCount(); j++){
            if(i == j && ui->firstMatrix->item(i,j)->text().toInt() == 1){
                QTableWidgetItem *two = new QTableWidgetItem;
                two->setText(QString::number(2));
                ui->secondMatrix->setItem(i,column++,two);
                continue;
            }
            for(int number = ui->firstMatrix->item(i,j)->text().toInt(); number > 0; number--, column++){
                QTableWidgetItem *one = new QTableWidgetItem;
                one->setText(QString::number(1));
                ui->secondMatrix->setItem(i,column,one);

                QTableWidgetItem *oneone = new QTableWidgetItem;
                oneone->setText(QString::number(-1));
                ui->secondMatrix->setItem(j,column,oneone);
            }
        }
}

void MainWindow::fromAtoI(){
    ui->secondMatrix->setColumnCount(countColumns() / 2 + 1);
    ui->secondMatrix->setHorizontalHeaderLabels(createHorizontalHeaderLabels(ui->secondMatrix->columnCount()));
    int column = 0;
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        for(int j = i; j < ui->firstMatrix->columnCount(); j++){
            if(i == j && ui->firstMatrix->item(i,j)->text().toInt() == 1){
                QTableWidgetItem *two = new QTableWidgetItem;
                two->setText(QString::number(2));
                ui->secondMatrix->setItem(i,column++,two);
                continue;
            }
            for(int number = ui->firstMatrix->item(i,j)->text().toInt(); number > 0; number--, column++){
                QTableWidgetItem *one = new QTableWidgetItem;
                one->setText(QString::number(1));
                ui->secondMatrix->setItem(i,column,one);

                QTableWidgetItem *oneone = new QTableWidgetItem;
                oneone->setText(QString::number(1));
                ui->secondMatrix->setItem(j,column,oneone);
            }
        }
}

void MainWindow::clearSecondMatrix(){
    for(int i = 0; i < ui->secondMatrix->rowCount(); i++)
        for(int j = 0; j < ui->secondMatrix->columnCount(); j++)
            ui->secondMatrix->takeItem(i,j);
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

void MainWindow::fillSecondMatrix(){
    for(int i = 0; i < ui->secondMatrix->rowCount(); i++)
        for(int j = 0; j < ui->secondMatrix->columnCount(); j++)
            if(ui->secondMatrix->item(i,j) == NULL){
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText(QString::number(0));
                ui->secondMatrix->setItem(i,j,item);
            }
}

void MainWindow::setSizeForTables(){
    for(int i = 0; i < ui->firstMatrix->columnCount(); i++)
        ui->firstMatrix->setColumnWidth(i,ui->firstMatrix->rowHeight(0));
    for(int i = 0; i < ui->secondMatrix->columnCount(); i++)
        ui->secondMatrix->setColumnWidth(i,ui->secondMatrix->rowHeight(0));
    ui->firstMatrix->setFixedHeight(ui->firstMatrix->rowHeight(0) * (ui->firstMatrix->rowCount() + 1));
    ui->firstMatrix->setFixedWidth(ui->firstMatrix->columnWidth(0) * (ui->firstMatrix->columnCount() + 1));
    ui->secondMatrix->setFixedHeight(ui->secondMatrix->rowHeight(0) * (ui->secondMatrix->rowCount() + 1));
    ui->secondMatrix->setFixedWidth(ui->secondMatrix->columnWidth(0) * (ui->secondMatrix->columnCount() + 1));
}

void MainWindow::on_arc_valueChanged(int arg1){
    Q_UNUSED(arg1);
    on_operation_currentIndexChanged(ui->operation->currentIndex());
}

void MainWindow::on_clear_clicked(){
    ui->firstMatrix->clear();
    ui->secondMatrix->clear();
    ui->arc->setValue(0);
    ui->operation->setCurrentIndex(0);
    ui->aboveFirstMatrix->clear();
    ui->aboveSecondMatrix->clear();
    ui->vertice->setValue(0);
    ui->orientedCheck->setChecked(false);
    nodes.clear();
    edges.clear();
    graphButtons->graph->setNodesMap(nodes);
    graphButtons->graph->setEdgesMap(edges);
    repaint();
}

void MainWindow::on_build_clicked(){
    nodes.clear();
    edges.clear();
    receiveNodesMap();
    graphButtons->graph->setNodesMap(nodes);
    graphButtons->graph->setEdgesMap(edges);
    repaint();

    clearSecondMatrix();
    fillFirstMatrix();
    int i = ui->operation->currentIndex();
    switch (i){
    case 1:
        if(orient){
            fromItoA(-1);
            fromIorToGraph();
        }
        else{
            fromItoA(1);
            fromIToGraph();
        }
        break;
    case 2:
        if(orient){
            fromAtoIor();
            fromAorToGraph();
        }
        else{
            fromAtoI();
            fromAToGraph();
        }
        setSizeForTables();
        break;
    default: break;
    }
    fillSecondMatrix();

    graphButtons->graph->setEdgesMap(edges);
    graphButtons->graph->repaint();
}

void MainWindow::receiveNodesMap(){
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        nodes.push_back(Node(nodes.newIndex(),(100 + i * 100) % 300,(100 + i * 100) % 300));
}

void MainWindow::fromAToGraph(){
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        for(int j = i; j < ui->firstMatrix->rowCount(); j++){
            int number = ui->firstMatrix->item(i,j)->text().toInt();
            while(number >= 1){
                edges.push_back(Edge(edges.newIndex(), i, j));
                number--;
            }
        }
}

void MainWindow::fromAorToGraph(){
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        for(int j = 0; j < ui->firstMatrix->rowCount(); j++){
            int number = ui->firstMatrix->item(i,j)->text().toInt();
            while(number >= 1){
                edges.push_back(Edge(edges.newIndex(), i, j));
                number--;
            }
        }
}

void MainWindow::fromIToGraph(){
    for(int j = 0; j < ui->firstMatrix->columnCount(); j++){
        Edge edge = Edge(j, j, j);
        for(int i = 0; i < ui->firstMatrix->rowCount(); i++){
            if(ui->firstMatrix->item(i,j)->text().toInt() < 1)
                continue;
            if(ui->firstMatrix->item(i,j)->text().toInt() == 1){
                edge.setIn(i++);
                while(ui->firstMatrix->item(i,j)->text().toInt() != 1) i++;
            }
            else if(ui->firstMatrix->item(i,j)->text().toInt() == 2){
                edge.setIn(i);
            }
            edge.setOut(i);
            edges.push_back(edge);
            break;
        }
    }
}

void MainWindow::fromIorToGraph(){
    for(int j = 0; j < ui->firstMatrix->columnCount(); j++){
        Edge edge = Edge(j, j, j);
        for(int i = 0; i < ui->firstMatrix->rowCount(); i++){
            if(ui->firstMatrix->item(i,j)->text().toInt() == 0)
                continue;
            if(ui->firstMatrix->item(i,j)->text().toInt() == 1){
                edge.setIn(i);
                while(ui->firstMatrix->item(i,j)->text().toInt() != -1) i++;
                edge.setOut(i);
            }
            else if(ui->firstMatrix->item(i,j)->text().toInt() == -1){
                edge.setOut(i);
                while(ui->firstMatrix->item(i,j)->text().toInt() != 1) i++;
                edge.setIn(i);
            }
            else if(ui->firstMatrix->item(i,j)->text().toInt() == 2){
                edge.setIn(i);
                edge.setOut(i);
            }
            edges.push_back(edge);
            break;
        }
    }
}

void MainWindow::on_matrix_clicked(){
    ui->firstMatrix->setRowCount(graphButtons->graph->getNodesMap().size());
    ui->secondMatrix->setRowCount(graphButtons->graph->getNodesMap().size());
    ui->firstMatrix->setVerticalHeaderLabels(createVerticalHeaderLabels(graphButtons->graph->getNodesMap().size()));
    ui->secondMatrix->setVerticalHeaderLabels(createVerticalHeaderLabels(graphButtons->graph->getNodesMap().size()));

    clearFirstMatrix();
    clearSecondMatrix();
    int i = ui->operation->currentIndex();
    switch (i){
    case 1:
        ui->firstMatrix->setColumnCount(graphButtons->graph->getEdgesMap().size());
        ui->secondMatrix->setColumnCount(graphButtons->graph->getNodesMap().size());
        ui->firstMatrix->setHorizontalHeaderLabels(createHorizontalHeaderLabels(graphButtons->graph->getEdgesMap().size()));
        ui->secondMatrix->setHorizontalHeaderLabels(createVerticalHeaderLabels(graphButtons->graph->getNodesMap().size()));

        fillFirstMatrix();
        if(orient){
            fromGraphToIor();
            fromItoA(-1);
        }
        else{
            fromGraphToI();
            fromItoA(1);
        }
        break;
    case 2:
        ui->firstMatrix->setColumnCount(graphButtons->graph->getNodesMap().size());
        ui->secondMatrix->setColumnCount(graphButtons->graph->getEdgesMap().size());
        ui->firstMatrix->setHorizontalHeaderLabels(createVerticalHeaderLabels(graphButtons->graph->getNodesMap().size()));
        ui->secondMatrix->setHorizontalHeaderLabels(createHorizontalHeaderLabels(graphButtons->graph->getEdgesMap().size()));

        fillFirstMatrix();
        if(orient){
            fromGraphToAor();
            fromAtoIor();
        }
        else{
            fromGraphToA();
            fromAtoI();
        }

        break;
    default: break;
    }
    fillSecondMatrix();
    setSizeForTables();
}

void MainWindow::fromGraphToAor(){
    foreach (Edge edge, graphButtons->graph->getEdgesMap()) {
        QTableWidgetItem *item = new QTableWidgetItem;
        if(ui->firstMatrix->item(edge.getIn(),edge.getOut()) != NULL)
            item->setText(QString::number(ui->firstMatrix->item(edge.getIn(),edge.getOut())->text().toInt() + 1));
        else
            item->setText(QString::number(1));
        ui->firstMatrix->setItem(edge.getIn(),edge.getOut(),item);
    }
}

void MainWindow::fromGraphToA(){
    foreach (Edge edge, graphButtons->graph->getEdgesMap()) {
        QTableWidgetItem *item = new QTableWidgetItem;
        if(ui->firstMatrix->item(edge.getIn(),edge.getOut()) != NULL)
            item->setText(QString::number(ui->firstMatrix->item(edge.getIn(),edge.getOut())->text().toInt() + 1));
        else
            item->setText(QString::number(1));
        ui->firstMatrix->setItem(edge.getIn(),edge.getOut(),item);
        QTableWidgetItem *nitem = new QTableWidgetItem;
        nitem->setText(item->text());
        ui->firstMatrix->setItem(edge.getOut(),edge.getIn(),nitem);
    }
}

void MainWindow::fromGraphToIor(){
    foreach (Edge edge, graphButtons->graph->getEdgesMap()) {
        QTableWidgetItem *item = new QTableWidgetItem;

        if(edge.getIn() == edge.getOut()){
            item->setText(QString::number(2));
            ui->firstMatrix->setItem(edge.getIn(),edge.getId(),item);
        }
        else{
            item->setText(QString::number(1));
            ui->firstMatrix->setItem(edge.getIn(),edge.getId(),item);
            QTableWidgetItem *nitem = new QTableWidgetItem;
            nitem->setText(QString::number(-1));
            ui->firstMatrix->setItem(edge.getOut(),edge.getId(),nitem);
        }
    }
}

void MainWindow::fromGraphToI(){
    foreach (Edge edge, graphButtons->graph->getEdgesMap()) {
        QTableWidgetItem *item = new QTableWidgetItem;

        if(edge.getIn() == edge.getOut()){
            item->setText(QString::number(2));
            ui->firstMatrix->setItem(edge.getIn(),edge.getId(),item);
        }
        else{
            item->setText(QString::number(1));
            ui->firstMatrix->setItem(edge.getIn(),edge.getId(),item);
            QTableWidgetItem *nitem = new QTableWidgetItem;
            nitem->setText(QString::number(1));
            ui->firstMatrix->setItem(edge.getOut(),edge.getId(),nitem);
        }
    }
}

void MainWindow::on_orientedCheck_stateChanged(int arg1){
    Q_UNUSED(arg1);
    orient = ui->orientedCheck->isChecked() ? true : false;
    graphButtons->graph->setOrient(orient);
    repaint();
}

void MainWindow::on_firstMatrix_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn){
    Q_UNUSED(currentRow);
    Q_UNUSED(currentColumn);
    if(!orient && !incidence){
        if(previousRow != previousColumn && ui->firstMatrix->item(previousRow,previousColumn)){
            QTableWidgetItem *symmetricitem = new QTableWidgetItem;
            symmetricitem->setText(ui->firstMatrix->item(previousRow,previousColumn)->text());
            if(ui->firstMatrix->item(previousColumn,previousRow))
                ui->firstMatrix->takeItem(previousColumn,previousRow);
            ui->firstMatrix->setItem(previousColumn,previousRow,symmetricitem);
        }
    }
}
