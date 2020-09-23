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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QStringList createVerticalHeaderLabels();
    QStringList createHorizontalHeaderLabels();
    void setSizeForTables();
    void doDefault12();
    void doDefault34();
    void fromItoA(int orient);
    void fromAtoIor();
    void fromAtoInor();
    void fillMatrixWith0(bool choice);
    void set1ForNotOriented();
    void clearSecondMatrix();
    bool checkForOriented();

private slots:
    void on_operation_currentIndexChanged(int index);
    void on_X_valueChanged();
    void on_Y_valueChanged();
    void on_clear_clicked();
    void on_build_clicked();

private:
    Ui::MainWindow *ui;
};

class NotOrientedIncidence: public QItemDelegate
{
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & option,
                          const QModelIndex & index) const
    {
        QLineEdit *lineEdit = new QLineEdit(parent);
        QIntValidator *validator = new QIntValidator(0,2, lineEdit);
        lineEdit->setValidator(validator);
        return lineEdit;
    }
};

class OrienterIncidence: public QItemDelegate
{
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & option,
                          const QModelIndex & index) const
    {
        QLineEdit *lineEdit = new QLineEdit(parent);
        QIntValidator *validator = new QIntValidator(-1,2, lineEdit);
        lineEdit->setValidator(validator);
        return lineEdit;
    }
};

class NotAndOrientedAdjacency: public QItemDelegate
{
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & option,
                          const QModelIndex & index) const
    {
        QLineEdit *lineEdit = new QLineEdit(parent);
        QIntValidator *validator = new QIntValidator(0,INT_MAX, lineEdit);
        lineEdit->setValidator(validator);
        return lineEdit;
    }
};

#endif // MAINWINDOW_H
