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
    graphButtons->setStyleSheet("border: 1px solid red;");
}

MainWindow::~MainWindow()
{
    //graphButtons->deleteLater();
    delete ui;
}

void MainWindow::on_vertice_valueChanged(int arg1)
{
    on_operation_currentIndexChanged(arg1);
}

int MainWindow::countColumns()
{
    int columnCount = 0;
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
    {
        for(int j = 0; j < ui->firstMatrix->columnCount(); j++)
        {
            columnCount += ui->firstMatrix->item(i,j)->text().toInt();
        }
    }
    return columnCount;
}

QStringList MainWindow::createVerticalHeaderLabels()
{
    QStringList headers;
    for(int i = 1; i <= ui->X->value(); i++)
    {
        headers << "x" + QString::number(i);
    }
    return headers;
}

QStringList MainWindow::createHorizontalHeaderLabels(int value)
{
    QStringList headers;
    for(int i = 1; i <= value; i++)
    {
        headers << "y" + QString::number(i);
    }
    return headers;
}

void MainWindow::on_operation_currentIndexChanged(int index)
{
    if(index == 0){
        on_clear_clicked();
        return;
    }
    ui->firstMatrix->setRowCount(ui->X->value());
    ui->secondMatrix->setRowCount(ui->X->value());
    ui->firstMatrix->setVerticalHeaderLabels(createVerticalHeaderLabels());
    ui->secondMatrix->setVerticalHeaderLabels(createVerticalHeaderLabels());
    switch (index)
    {
    case 1:
        if(orient)
            doDefault12();
        else
            doDefault12();
        break;
    case 2:
        if(orient){
            doDefault34();
        }
        else{
            doDefault34();
        }
        break;
    default:
        break;
    }
    setSizeForTables();
}

void MainWindow::fromItoA(int orient)
{
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
    {
        for(int j = 0; j < ui->firstMatrix->columnCount(); j++)
        {
            if(ui->firstMatrix->item(i,j)->text().toInt() == 1)
            {
                for(int k = 0; k < ui->firstMatrix->rowCount(); k++)
                {
                    if(k != i && ui->firstMatrix->item(k,j)->text().toInt() == orient)
                    {
                        QTableWidgetItem *item = new QTableWidgetItem;
                        if(ui->secondMatrix->item(i,k) != NULL)
                        {
                            item->setText(QString::number(ui->secondMatrix->item(i,k)->text().toInt() + 1));
                        }
                        else
                        {
                            item->setText(QString::number(1));
                        }
                        ui->secondMatrix->setItem(i,k,item);
                        break;
                    }
                }
            }
            else if(ui->firstMatrix->item(i,j)->text().toInt() == 2)
            {
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText(QString::number(1));
                ui->secondMatrix->setItem(i,i,item);
            }
        }
    }
}

void MainWindow::fromAtoI(int orient)
{
    ui->secondMatrix->setColumnCount(countColumns());
    ui->secondMatrix->setHorizontalHeaderLabels(createHorizontalHeaderLabels(ui->secondMatrix->columnCount()));
    int column = 0;
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
    {
        for(int j = 0; j < ui->firstMatrix->columnCount(); j++)
        {
            if(i == j && ui->firstMatrix->item(i,j)->text().toInt() == 1)
            {
                QTableWidgetItem *two = new QTableWidgetItem;
                two->setText(QString::number(2));
                ui->secondMatrix->setItem(i,column++,two);
                continue;
            }
            for(int number = ui->firstMatrix->item(i,j)->text().toInt(); number > 0; number--, column++)
            {
                QTableWidgetItem *one = new QTableWidgetItem;
                one->setText(QString::number(1));
                ui->secondMatrix->setItem(i,column,one);

                QTableWidgetItem *oneone = new QTableWidgetItem;
                oneone->setText(QString::number(orient));
                ui->secondMatrix->setItem(j,column,oneone);
            }
        }
    }
}

bool MainWindow::checkForOriented()
{
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
    {
        for(int j = 0; j < ui->firstMatrix->columnCount(); j++)
        {
            if(ui->firstMatrix->item(i,j)->text().toInt() == 1)
            {
                bool ok = false;
                for(int k = 0; k < ui->firstMatrix->rowCount(); k++)
                {
                    if(k != i && ui->firstMatrix->item(k,j)->text().toInt() == -1)
                    {
                        ok = true;
                    }
                }
                if(!ok)
                {
                    QDialog *newDialog = new QDialog;
                    QMessageBox::warning(newDialog, "Warning", "Your matrix is not from oriented graph");
                    return false;
                }
            }
            else if(ui->firstMatrix->item(i,j)->text().toInt() == -1)
            {
                bool ok = false;
                for(int k = 0; k < ui->firstMatrix->rowCount(); k++)
                {
                    if(k != i && ui->firstMatrix->item(k,j)->text().toInt() == 1)
                    {
                        ok = true;
                    }
                }
                if(!ok)
                {
                    QDialog *newDialog = new QDialog;
                    QMessageBox::warning(newDialog, "Warning", "Your matrix is not from oriented graph");
                    return false;
                }
            }
        }
    }
    return true;
}

void MainWindow::clearSecondMatrix()
{
    for(int i = 0; i < ui->secondMatrix->rowCount(); i++)
    {
        for(int j = 0; j < ui->secondMatrix->columnCount(); j++)
        {
            ui->secondMatrix->takeItem(i,j);
        }
    }
}

void MainWindow::set1ForNotOriented()
{
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
    {
        for(int j = 0; j < ui->firstMatrix->columnCount(); j++)
        {
            if(ui->firstMatrix->item(i,j)->text().toInt() == -1)
            {
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText(QString::number(1));
                ui->firstMatrix->setItem(i,j,item);
            }
        }
    }
}

void MainWindow::fillMatrixWith0(bool choice)
{
    if(choice)
    {
        for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
        {
            for(int j = 0; j < ui->firstMatrix->columnCount(); j++)
            {
                if(ui->firstMatrix->item(i,j) == NULL)
                {
                    QTableWidgetItem *item = new QTableWidgetItem;
                    item->setText(QString::number(0));
                    ui->firstMatrix->setItem(i,j,item);
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < ui->secondMatrix->rowCount(); i++)
        {
            for(int j = 0; j < ui->secondMatrix->columnCount(); j++)
            {
                if(ui->secondMatrix->item(i,j) == NULL)
                {
                    QTableWidgetItem *item = new QTableWidgetItem;
                    item->setText(QString::number(0));
                    ui->secondMatrix->setItem(i,j,item);
                }
            }
        }
    }
}

void MainWindow::doDefault12()
{
    ui->firstMatrix->setColumnCount(ui->vertice->value());
    ui->secondMatrix->setColumnCount(ui->X->value());
    ui->firstMatrix->setHorizontalHeaderLabels(createHorizontalHeaderLabels(ui->vertice->value()));
    ui->secondMatrix->setHorizontalHeaderLabels(createVerticalHeaderLabels());
    ui->aboveFirstMatrix->setText("Incidence");
    ui->aboveSecondMatrix->setText("Adjacency");
    ui->secondMatrix->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::doDefault34()
{
    ui->firstMatrix->setColumnCount(ui->X->value());
    ui->firstMatrix->setHorizontalHeaderLabels(createVerticalHeaderLabels());
    ui->secondMatrix->setHorizontalHeaderLabels(createHorizontalHeaderLabels(ui->vertice->value()));
    ui->aboveFirstMatrix->setText("Adjacency");
    ui->aboveSecondMatrix->setText("Incidence");
    ui->secondMatrix->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setSizeForTables()
{
    for(int i = 0; i < ui->firstMatrix->columnCount(); i++)
    {
        ui->firstMatrix->setColumnWidth(i,ui->firstMatrix->rowHeight(0));
    }
    for(int i = 0; i < ui->secondMatrix->columnCount(); i++)
    {
        ui->secondMatrix->setColumnWidth(i,ui->secondMatrix->rowHeight(0));
    }
    ui->firstMatrix->setFixedHeight(ui->firstMatrix->rowHeight(0) * (ui->firstMatrix->rowCount() + 1));
    ui->firstMatrix->setFixedWidth(ui->firstMatrix->columnWidth(0) * (ui->firstMatrix->columnCount() + 1));
    ui->secondMatrix->setFixedHeight(ui->secondMatrix->rowHeight(0) * (ui->secondMatrix->rowCount() + 1));
    ui->secondMatrix->setFixedWidth(ui->secondMatrix->columnWidth(0) * (ui->secondMatrix->columnCount() + 1));
}

void MainWindow::on_X_valueChanged()
{
    on_operation_currentIndexChanged(ui->operation->currentIndex());
}

void MainWindow::on_clear_clicked()
{
    ui->firstMatrix->clear();
    ui->secondMatrix->clear();
    // clear tables with rows and columns ???????
    ui->X->setValue(0);
    ui->operation->setCurrentIndex(0);
    ui->aboveFirstMatrix->clear();
    ui->aboveSecondMatrix->clear();
    ui->vertice->setValue(0);
    ui->orientedCheck->setChecked(false);
}

void MainWindow::on_build_clicked()
{
    clearSecondMatrix();
    fillMatrixWith0(true);
    int i = ui->operation->currentIndex();
    switch (i)
    {
    case 1:
        if(checkForOriented())
        {
            fromItoA(-1);
        }
        break;
    case 2:
        // check for matrix with two 1 in one column at least
        set1ForNotOriented();
        fromItoA(1);
        break;
    case 3:
        fromAtoI(-1);
        break;
    case 4:
        fromAtoI(1);
        break;
    default:
        break;
    }
    fillMatrixWith0(false);
}

void MainWindow::on_orientedCheck_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    orient = ui->orientedCheck->isChecked() ? true : false;
    graphButtons->graph->setOrient(orient);
    repaint();
}

void MainWindow::on_firstMatrix_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(currentRow);
    Q_UNUSED(currentColumn);
    if(orient)
    {
        if(previousRow != previousColumn && ui->firstMatrix->item(previousRow,previousColumn))
        {
            QTableWidgetItem *symmetricitem = new QTableWidgetItem;
            symmetricitem->setText(ui->firstMatrix->item(previousRow,previousColumn)->text());
            if(ui->firstMatrix->item(previousColumn,previousRow))
                ui->firstMatrix->takeItem(previousColumn,previousRow);
            ui->firstMatrix->setItem(previousColumn,previousRow,symmetricitem);
        }
    }
}
