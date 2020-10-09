#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemDelegate>
#include <QLineEdit>
#include <QTableWidget>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QDialog>
#include <QPainter>
#include <graphvisualisingbuttons.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    bool incidence;
    bool orient;

public:
    QStringList createVerticalHeaderLabels(int value);
    QStringList createHorizontalHeaderLabels(int value);
    void setSizeForTables();
    void fromItoA(int orient);
    void fromAtoIor();
    void fromAtoI();
    void fillFirstMatrix();
    void fillSecondMatrix();
    void clearSecondMatrix();
    void clearFirstMatrix();
    int countColumns();

    void receiveNodesMap();
    void fromAToGraph();
    void fromAorToGraph();
    void fromIToGraph();
    void fromIorToGraph();

    void fromGraphToAor();
    void fromGraphToA();
    void fromGraphToIor();
    void fromGraphToI();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_operation_currentIndexChanged(int index);
    void on_arc_valueChanged(int arg1);
    void on_vertice_valueChanged(int arg1);
    void on_clear_clicked();
    void on_build_clicked();
    void on_matrix_clicked();
    void on_orientedCheck_stateChanged(int arg1);
    void on_firstMatrix_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);


private:
    Ui::MainWindow *ui;
    GraphVisualisingButtons *graphButtons;
    NodesMap nodes;
    EdgesMap edges;

};

#endif // MAINWINDOW_H
