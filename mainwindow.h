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

public:
    bool orient;
    bool getOrient() const { return orient; }

    QStringList createVerticalHeaderLabels();
    QStringList createHorizontalHeaderLabels(int value);
    void setSizeForTables();
    void doDefault12();
    void doDefault34();
    void fromItoA(int orient);
    void fromAtoI(int orient);
    void fillMatrixWith0(bool choice);
    void set1ForNotOriented();
    void clearSecondMatrix();
    bool checkForOriented();
    int countColumns();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_operation_currentIndexChanged(int index);
    void on_X_valueChanged();
    void on_clear_clicked();
    void on_build_clicked(); 
    void on_vertice_valueChanged(int arg1);
    void on_orientedCheck_stateChanged(int arg1);
    void on_firstMatrix_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::MainWindow *ui;
    GraphVisualisingButtons *graphButtons;
    NodesMap nodes;
    EdgesMap edges;

};

#endif // MAINWINDOW_H
