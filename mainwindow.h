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
#include <map>
#include <windows.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    vector<pair<int,int>> coordVertice;

public:
    QStringList createVerticalHeaderLabels(int);
    QStringList createHorizontalHeaderLabels(int);
    void setSizeForTables();
    void fillFirstMatrix();
    void clearFirstMatrix();

    void receiveNodesMap();
    void fromAToGraph();
    void fromGraphToA();
    void SetMatrix();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_vertice_valueChanged(int);
    void on_clear_clicked();
    void on_build_clicked();
    void on_matrix_clicked();
    void on_day_pressed();
    void on_night_clicked();
    void on_exit_clicked();

    void on_find_clicked();

private:
    Ui::MainWindow *ui;
    GraphVisualisingButtons *graphButtons;
    NodesMap nodes;
    EdgesMap edges;

};

#endif // MAINWINDOW_H
