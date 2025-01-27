#include "ofigure.h"
#include <Qt>
#include <QColor>
#include <QPainter>
#include <QDebug>
#include <QBrush>


OFigure::OFigure()
{
    // инициализация полей
    m_i = 0;
    m_k = 0;
    arrayColor.resize(1);
    type = TYPE::O;
    size = SIZE::O;
    // заполнение палитры цветов
    palitra.push_back(QColor(255,0,0));
    palitra.push_back(QColor(255,128,0));
    palitra.push_back(QColor(255,255,0));
    palitra.push_back(QColor(0,255,0));
    palitra.push_back(QColor(0,0,255));
    palitra.push_back(QColor(255,0,255));
}

void OFigure::goLeft() // сдвинуть в лево
{
    if(m_i >= 1)
        m_i -=1;
}

void OFigure::goRight()  // сдвинуть в право
{
    if(m_i < 10)
        m_i+=1;
}

void OFigure::goDown(int y)  // уронить в низ
{
    m_k = y - 2;
}

int OFigure::getFirstI() // координата первой клетки
{
    return  m_i;
}


int OFigure::getFirstK()
{
    return m_k;
}

int OFigure::getLastI()  //координата нижней клетки
{
    return m_i + 1;
}

int OFigure::getLastK()
{
    return m_k + 1;
}

void OFigure::rotateColors(int)  // изменение цвета внктри фигуры
{}

void OFigure::makeRandomColors()  // заполнение фигуры рандомными цветами
{
    arrayColor[0] = palitra[rand() % (palitra.size() -1)];
}

void OFigure::paintFigure(QPainter &painter) // рисуем фигуру в стакане
{
    QBrush brush1(Qt::red, Qt::SolidPattern);
    painter.setBrush(brush1);

    QRect rect(0, 0, m_W, m_W);

    int squareSize = 2; // квадрат 3x3

    for (int i = 0; i < squareSize; ++i) // строки
    {
        for (int j = 0; j < squareSize; ++j) // столбцы
        {
            rect.moveTopLeft(QPoint((m_i + j) * m_W, (m_k + i) * m_W));
            brush1.setColor(arrayColor[0]);
            painter.setBrush(brush1);
            painter.drawRect(rect);
        }
    }


    //painter.end();

}

void OFigure::setpos(int x, int y)  // установка координаты
{
    m_i = x;
    m_k = y;
}
