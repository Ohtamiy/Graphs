#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H

#include <QWidget>
#include <QPainter>

class graphsWidget : public QWidget
{
    Q_OBJECT
public:
    graphsWidget(QWidget *parent = 0);
    int vertice = 0;
    bool orient = rand() % 1;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // GRAPHSWIDGET_H
