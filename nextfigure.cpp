#include "nextfigure.h"
#include "figure.h"
#include <QPainter>


NextFigure::NextFigure(QWidget *parent)
    : QWidget{parent}
{
    next = nullptr;
}

void NextFigure::slotChangePattern(Figure * pfig)
{
    next = pfig;
    game = true;
    this->update();
}

void NextFigure::paintEvent(QPaintEvent *event)
{

    QPainter paint(this);

    paint.drawRect(this->rect());

    if(game)
    {
     paint.translate(100,20);
     next->paintFigure(paint);
    }

}
