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

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// ------------------------- Paint nodes and edges --------------------------------------
void MainWindow::on_paintVertice_clicked(){
    vector <short> result;
    short color = 0;
    for(short i = 0; i < ui->firstMatrix->rowCount(); i++){
        bool colour = 0, adj = 0;
        for(short j = 0; j < (int)result.size(); j++){
            if(ui->firstMatrix->item(i,j)->text().toInt() == 0){
                for(int h = 0; h < (int)result.size(); h++){
                    if(j != h && result.at(j) == result.at(h) && ui->firstMatrix->item(i,h)->text().toInt() != 0){
                        adj = 1;
                    }
                }
                if(!adj){
                    result.push_back(result.at(j));
                    colour = 1;
                    break;
                }
            }
            if(j + 1 < (int)result.size())
                adj = 0;
        }
        if(!colour)
            result.push_back(color++);
    }

    QString res;
    for(int i = 0; i < (int)result.size(); i++)
        res += QString::number(result.at(i)+1) + "  ";
    ui->result->setText(res);

    NodesMap paintVertice;
    short u = 0;
    foreach(Node node, graphButtons->graph->getNodesMap()){
        paintVertice.push_back(Node(result.at(u++),node.getX(), node.getY()));
    }
    graphButtons->graph->setNodesMap(paintVertice);
    graphButtons->graph->setOrient(1);
    repaint();
}

void MainWindow::on_paintEdges_clicked(){
    EdgesMap paintEdges;

    short color = 0;
    for(short i = 0; i < ui->firstMatrix->rowCount(); i++){
        for(short j = i + 1; j < ui->firstMatrix->rowCount(); j++){
            short number = ui->firstMatrix->item(i,j)->text().toInt();
            while(number != 0){
                vector<pair<int,int>> colorVertice;

                for(int h = 0; h <= j; h++){
                    int n = ui->firstMatrix->item(i,h)->text().toInt();
                    if(h == j)
                        n = ui->firstMatrix->item(i,h)->text().toInt() - 1;
                    if(n > 0){
                        colorVertice.push_back({i,h});
                        n--;
                    }
                }

                for(int h = 0; h <= i; h++){
                    int n = ui->firstMatrix->item(h,j)->text().toInt();
                    if(h == i)
                        n = ui->firstMatrix->item(h,j)->text().toInt() - 1;
                    if(n > 0){
                        colorVertice.push_back({h,j});
                        n--;
                    }
                }

                vector<int> colors;

                foreach (Edge edge, paintEdges) {
                    for(auto f = colorVertice.begin(); f != colorVertice.end(); f++){
                        if((edge.getIn() == f->first && edge.getOut() == f->second) ||
                           (edge.getIn() == f->second && edge.getOut() == f->first)){
                            colors.push_back(edge.getId());
                        }
                    }
                }

                bool ok = 0, ok1 = 0;
                for(int f = 0; f < color; f++){
                    foreach (int c, colors) {
                        if(c == f){
                            ok = 1;
                            break;
                        }
                    }
                    if(!ok){
                        paintEdges.push_back(Edge(f,i,j));
                        ok1 = 1;
                        break;
                    }
                    if(f + 1 != color)
                        ok = 0;
                }

                if(!ok1)
                    paintEdges.push_back(Edge(color++,i,j));
                number--;

                colorVertice.clear();
                colors.clear();
            }
        }
    }

    QString res;
    foreach(Edge edge, paintEdges)
        res += QString::number(edge.getId()+1) + "  ";
    ui->result->setText(res);

    graphButtons->graph->setEdgesMap(paintEdges);
    graphButtons->graph->setOrient(0);
    repaint();

    clearFirstMatrix();
    fillFirstMatrix();
    fromGraphToA();
}

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// ------------------------- Finding minimal way ----------------------------------------
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
    ui->result->setText(result);//íâ® ¢ë¢®¤

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
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// ------------------------- Breath and depth search ------------------------------------
void MainWindow::fill(int x, int k, vector<int> &arr){
    for(int i = 0; i < (int)arr.size();i++)
        if(ui->firstMatrix->item(x,i)->text().toInt() != 0 && arr[i] == -1)
            arr[i] = k;
}

void MainWindow::on_breadth_first_search_clicked(){
    on_build_clicked();
    vector<int> arr(ui->firstMatrix->rowCount());
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        arr[i] = -1;

    int k = 0;
    arr[ui->start->value()-1] = k++;
    fill(ui->start->value()-1,k,arr);

    for(int j = 0; j < ui->firstMatrix->rowCount(); j++){
        for(int j = 0; j < ui->firstMatrix->rowCount(); j++)
            if(arr[j] == k)
                fill(j,k+1,arr);
        k++;
    }

    QString result;
    NodesMap paintVertice;
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++){
        paintVertice.push_back(Node(arr[i], graphButtons->graph->getNodesMap().at(i).getX(), graphButtons->graph->getNodesMap().at(i).getY()));
        result += "x" + QString::number(i+1) + ": " + QString::number(arr[i]) + "  ";
    }
    ui->result->setText(result);
    graphButtons->graph->setNodesMap(paintVertice);
    graphButtons->graph->setOrient(1);
    repaint();
}

int MainWindow::findMinD(int x, int arr[]) {
    for(int j = 0; j < ui->firstMatrix->rowCount(); j++)
        if(ui->firstMatrix->item(x,j)->text().toInt() != 0 && arr[j] == 0)
            return j;
    return -1;
}

void MainWindow::on_depth_first_search_clicked(){
    on_build_clicked();
    EdgesMap painted;
    int *arr = new int[ui->firstMatrix->rowCount()]();
    int k = 1, x = ui->start->value()-1;
    arr[x] = k++;

    stack<int> checked;
    checked.push(x);

    for(int i = 0, min = 0, temp = 0; i < ui->firstMatrix->rowCount(); i++, k++){
        min = findMinD(x, arr);
        while(min == -1 && !checked.empty()){
            temp = checked.top();
            checked.pop();
            min = findMinD(temp, arr);
        }
        if(min != -1){
            painted.push_back(Edge(1, graphButtons->graph->getNodesMap().at(x).getId(), graphButtons->graph->getNodesMap().at(min).getId()));
            x = min;
            arr[x] = k;
            checked.push(x);
        }
    }

    if((int)painted.size() < ui->firstMatrix->rowCount() - 1)
        ui->result->setText("Can't find depth from this vertice");
    else{
        foreach (Edge edge, graphButtons->graph->getEdgesMap()) {
            bool ok = 0;
            foreach (Edge colored, painted) {
                if((edge.getIn() == colored.getIn() && edge.getOut() == colored.getOut()) ||
                   (edge.getIn() == colored.getOut() && edge.getOut() == colored.getIn()))
                    ok = 1;
            }
            if(!ok)
                painted.push_back(Edge(0,edge.getIn(),edge.getOut()));
        }

        QString result;
        NodesMap paintVertice;
        for(int i = 0; i < ui->firstMatrix->rowCount(); i++){
            paintVertice.push_back(Node(arr[i], graphButtons->graph->getNodesMap().at(i).getX(), graphButtons->graph->getNodesMap().at(i).getY()));
            result += "x" + QString::number(i+1) + ": " + QString::number(arr[i]) + "  ";
        }
        ui->result->setText(result);
        graphButtons->graph->setEdgesMap(painted);
        graphButtons->graph->setNodesMap(paintVertice);
        graphButtons->graph->setOrient(1);
        repaint();
    }
}

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// ------------------------- Building spanning tree -------------------------------------
void MainWindow::findMin(vector<vector<int>> &matrix, int n, int &x, int &y, int &min){
    min = 225;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(matrix[i][j] < min && matrix[i][j] != 0){
                min = matrix[i][j];
                x = i;
                y = j;
            }
        }
    }
}
void MainWindow::fillMin(vector<vector<int>> &matrix,int x, int y){
    matrix[x][y] = 0;
    matrix[y][x] = 0;
}
void MainWindow::addColumn(vector<vector<int>> &matrix,int y, int n, vector<int> &col){
    for(int i = 0; i < n;i++){
        matrix[i][y] = ui->firstMatrix->item(i,y)->text().toInt();
    }
    col.push_back(y);
}
bool MainWindow::isEmpty(vector<int> col, int y){
    int n = col.size();
    for(int i = 0; i < n;i++){
        if(col[i] == y)
            return false;
    }
    return true;
}

void MainWindow::on_find_clicked()
{
    vector<int> column;
    EdgesMap paintEdges;
    QString result;
    int x = 0, y = 0, min = 225, n = ui->firstMatrix->rowCount(), count = n - 1;
    vector<vector<int>> matrix(n, vector<int>(n));

    fillFirstMatrix();//копирую матрицы
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = ui->firstMatrix->item(i,j)->text().toInt();
        }
    }
    findMin(matrix, n, x, y, min);//нахожу минимальное значение
    paintEdges.push_back(Edge(ui->firstMatrix->item(x,y)->text().toInt(),x,y));

    result += QString::number(min) + " ";

    for(int i = 0; i < n; i++){//очищаю матрицу
        for(int j = 0; j < n; j++){
                matrix[i][j] = 0;
        }
    }
    //заполняю двумя начальными столбиками
    addColumn(matrix, y, n, column);
    addColumn(matrix, x, n, column);
    count-=1;

    while(count != 0){
        do{
            fillMin(matrix, x, y);
            findMin(matrix, n, x, y, min);
        }while(!isEmpty(column, x));
        paintEdges.push_back(Edge(ui->firstMatrix->item(x,y)->text().toInt(),x,y));
        result += QString::number(min) + "   ";
        addColumn(matrix, x, n, column);
        count--;
    }
    matrix.clear();
    ui->result->setText(result);

    graphButtons->graph->setEdgesMap(paintEdges);
    graphButtons->graph->setOrient(0);
    repaint();
}
