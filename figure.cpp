#include "figure.h"
#include <Qt>
#include <QColor>
#include <QPainter>
#include <QDebug>
#include <QBrush>
Figure::Figure()
{
   m_i = 0;
   m_k = 0;
   arrayColor.resize(3);
   palitra.push_back(QColor(255,0,0));  // заполнение палитры цветов
   palitra.push_back(QColor(255,128,0));
   palitra.push_back(QColor(255,255,0));
   palitra.push_back(QColor(0,255,0));
   palitra.push_back(QColor(0,0,255));
   palitra.push_back(QColor(255,0,255));


}

void Figure::goLeft() // сдвинуть в лево
{
  if(m_i >= 1)
      m_i -=1;
}

void Figure::goRight()  // сдвинуть в право
{
    if(m_i < 11)
        m_i+=1;
}

void Figure::goDown(int y)  // уронить в низ
{

        m_k = y - 3;
}

int Figure::getFirstI() // координата первой клетки
{
    return  m_i;
}


int Figure::getFirstK()
{
    return m_k;
}

int Figure::getLastI()  //координата нижней клетки
{
    return m_i;
}

int Figure::getLastK()
{
    return m_k+2;
}

void Figure::rotateColors(int a)  // изменение цвета внктри фигуры
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

void Figure::makeRandomColors()  // заполнение фигуры рандомными цветами
{
   for(int i=0;i<arrayColor.size();++i)
   {
      arrayColor[i] = palitra[rand() % (palitra.size() -1)];

   }



}

void Figure::paintFigure(QPainter &painter) // рисуем фигуру в стакане
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

void Figure::setpos(int x, int y)  // установка координаты
{
    m_i = x;
    m_k = y;
}
