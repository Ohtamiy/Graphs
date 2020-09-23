#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wgt = new graphsPaintWidget(this);

    ui->graph->addWidget(wgt);
}

MainWindow::~MainWindow()
{
    wgt->deleteLater();
    delete ui;
}

void MainWindow::on_draw_clicked()
{

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

QStringList MainWindow::createHorizontalHeaderLabels()
{
    QStringList headers;
    for(int i = 1; i <= ui->Y->value(); i++)
    {
        headers << "y" + QString::number(i);
    }
    return headers;
}

void MainWindow::on_operation_currentIndexChanged(int index)
{
    if(index == 0)
    {
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
        doDefault12();
        ui->firstMatrix->setItemDelegate(new OrienterIncidence);

        break;
    case 2:
        doDefault12();
        ui->firstMatrix->setItemDelegate(new NotOrientedIncidence);

        break;
    case 3:
        doDefault34();
        ui->firstMatrix->setItemDelegate(new NotAndOrientedAdjacency);

        break;
    case 4:
        doDefault34();
        ui->firstMatrix->setItemDelegate(new NotAndOrientedAdjacency);

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

void MainWindow::fromAtoIor()
{
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

                QTableWidgetItem *minusone = new QTableWidgetItem;
                minusone->setText(QString::number(-1));
                ui->secondMatrix->setItem(j,column,minusone);
            }
        }
    }
}

void MainWindow::fromAtoInor()
{
    int column = 0;
    for(int i = 0; i < ui->firstMatrix->rowCount(); i++)
    {
        for(int j = i; j < ui->firstMatrix->columnCount(); j++)
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

                QTableWidgetItem *otherone = new QTableWidgetItem;
                otherone->setText(QString::number(1));
                ui->secondMatrix->setItem(j,column,otherone);
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
    ui->firstMatrix->setColumnCount(ui->Y->value());
    ui->secondMatrix->setColumnCount(ui->X->value());
    ui->firstMatrix->setHorizontalHeaderLabels(createHorizontalHeaderLabels());
    ui->secondMatrix->setHorizontalHeaderLabels(createVerticalHeaderLabels());
    ui->aboveFirstMatrix->setText("Incidence");
    ui->aboveSecondMatrix->setText("Adjacency");
    ui->secondMatrix->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Y->setEnabled(true);
}

void MainWindow::doDefault34()
{
    ui->firstMatrix->setColumnCount(ui->X->value());
    ui->secondMatrix->setColumnCount(ui->Y->value());
    ui->firstMatrix->setHorizontalHeaderLabels(createVerticalHeaderLabels());
    ui->secondMatrix->setHorizontalHeaderLabels(createHorizontalHeaderLabels());
    ui->aboveFirstMatrix->setText("Adjacency");
    ui->aboveSecondMatrix->setText("Incidence");
    ui->secondMatrix->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Y->setEnabled(false);
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

void MainWindow::on_Y_valueChanged()
{
    on_operation_currentIndexChanged(ui->operation->currentIndex());
}

void MainWindow::on_clear_clicked()
{
    ui->firstMatrix->clear();
    ui->secondMatrix->clear();
    // clear tables with rows and columns ???????
    ui->X->clear();
    ui->Y->clear();
    ui->operation->setCurrentIndex(0);
    ui->aboveFirstMatrix->clear();
    ui->aboveSecondMatrix->clear();
    ui->Y->setEnabled(true);
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
        fromAtoIor();
        break;
    case 4:
        // check for symmetric
        fromAtoInor();
        break;
    default:
        break;
    }
    fillMatrixWith0(false);
}
