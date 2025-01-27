#include "ifigure.h"
#include <Qt>
#include <QColor>
#include <QPainter>
#include <QDebug>
#include <QBrush>


IFigure::IFigure()
{
    // инициализация полей
    m_i = 0;
    m_k = 0;
    arrayColor.resize(3);
    type = Figure::TYPE::I;
    size = Figure::SIZE::I;
    // заполнение палитры цветов
    palitra.push_back(QColor(255,0,0));
    palitra.push_back(QColor(255,128,0));
    palitra.push_back(QColor(255,255,0));
    palitra.push_back(QColor(0,255,0));
    palitra.push_back(QColor(0,0,255));
    palitra.push_back(QColor(255,0,255));
}

void IFigure::goLeft() // сдвинуть в лево
{
    if(m_i >= 1)
        m_i -=1;
}

void IFigure::goRight()  // сдвинуть в право
{
    if(m_i < 11)
        m_i+=1;
}

void IFigure::goDown(int y)  // уронить в низ
{

    m_k = y - 3;
}

int IFigure::getFirstI() // координата первой клетки
{
    return  m_i;
}


int IFigure::getFirstK()
{
    return m_k;
}

int IFigure::getLastI()  //координата нижней клетки
{
    return m_i;
}

int IFigure::getLastK()
{
    return m_k+2;
}

void IFigure::rotateColors(int a)  // изменение цвета внктри фигуры
{
    switch (a) {
    case 1:
    {
        QColor first = arrayColor.first();
        for(int i=0;i<arrayColor.size()-1;++i)
            arrayColor[i] = arrayColor[i+1];
        arrayColor.last() = first;
    }
    break;
    case 2:
    {
        QColor last = arrayColor.last();
        for(int i = arrayColor.size()-1;i > 0;--i)
            arrayColor[i]=arrayColor[i-1];
        arrayColor.first() = last;
    }
    default:
        break;
    }
}

void IFigure::makeRandomColors()  // заполнение фигуры рандомными цветами
{
    for(int i=0;i<arrayColor.size();++i)
    {
        arrayColor[i] = palitra[rand() % (palitra.size() -1)];
    }

}

void IFigure::paintFigure(QPainter &painter) // рисуем фигуру в стакане
{
    QBrush brush1(Qt::red,Qt::SolidPattern);
    painter.setBrush(brush1);
    QRect rect(m_i*m_W,m_k*m_W,m_W,m_W);

    for(int i =0; i < arrayColor.size();++i)
    {
        rect.moveTopLeft(QPoint(m_i*m_W,(m_k+i)*m_W));
        brush1.setColor(arrayColor[i]);
        painter.drawRect(rect);
        painter.fillRect(rect,brush1);
    }

    painter.end();

}

void IFigure::setpos(int x, int y)  // установка координаты
{
    m_i = x;
    m_k = y;
}
