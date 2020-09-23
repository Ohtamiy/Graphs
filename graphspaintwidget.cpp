#include "graphspaintwidget.h"

#include <QPainter>

graphsPaintWidget::graphsPaintWidget(QWidget *parent) : QWidget(parent)
{
}

void graphsPaintWidget::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);

    QPainter p(this);
    p.setPen(QPen(Qt::black,1,Qt::SolidLine));
    p.drawRect(10,15,10,13);
    p.drawLine(35,38,100,100);
}
