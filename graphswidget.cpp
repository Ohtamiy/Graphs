#include "graphswidget.h"

graphsWidget::graphsWidget(QWidget *parent) : QWidget(parent)
{
}

void graphsWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setPen(QPen(Qt::red,1,Qt::SolidLine));

    for(int i = 0, a = 10, b = 20, c = 10; i < this->vertice; i++, a+=70, b+=70)
    {
        if(i % 2 == 0)
        {
            QRect ellipse(a,c,50,50);
            p.drawEllipse(ellipse);
        }
        else
        {
            p.drawEllipse(a,b,50,50);
        }
    }
}
