#ifndef GRAPHSPAINTWIDGET_H
#define GRAPHSPAINTWIDGET_H

#include <QWidget>

class graphsPaintWidget : public QWidget
{
    Q_OBJECT
public:
    graphsPaintWidget(QWidget * parent = 0);
protected:
    void paintEvent(QPaintEvent*);
};

#endif // GRAPHSPAINTWIDGET_H
