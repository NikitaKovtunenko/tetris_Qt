#include "LFigure.h"
#include <Qt>
#include <QColor>
#include <QPainter>
#include <QDebug>
#include <QBrush>


LFigure::LFigure()
{
    // инициализация полей
    m_i = 0;
    m_k = 0;
    arrayColor.resize(3);
    type = Figure::TYPE::L;
    size = Figure::SIZE::L;
    // заполнение палитры цветов
    palitra.push_back(QColor(255,0,0));
    palitra.push_back(QColor(255,128,0));
    palitra.push_back(QColor(255,255,0));
    palitra.push_back(QColor(0,255,0));
    palitra.push_back(QColor(0,0,255));
    palitra.push_back(QColor(255,0,255));
}

void LFigure::goLeft() // сдвинуть в лево
{
    if(m_i >= 1)
        m_i -=1;
}

void LFigure::goRight()  // сдвинуть в право
{
    if(m_i < 10)
        m_i+=1;
}

void LFigure::goDown(int y)  // уронить в низ
{

    m_k = y - 2;
}

int LFigure::getFirstI() // координата первой клетки
{
    return  m_i;
}


int LFigure::getFirstK()
{
    return m_k;
}

int LFigure::getLastI()  //координата нижней клетки
{
    return m_i +1;
}

int LFigure::getLastK()
{
    return m_k+1;
}

void LFigure::rotateColors(int a)  // изменение цвета внктри фигуры
{
}

void LFigure::makeRandomColors()  // заполнение фигуры рандомными цветами
{
    arrayColor[0] = palitra[rand() % (palitra.size() -1)];
}

void LFigure::paintFigure(QPainter &painter) // рисуем фигуру в стакане
{
    QBrush brush1(Qt::red, Qt::SolidPattern);
    painter.setBrush(brush1);
    QRect rect(m_i * m_W, m_k * m_W, m_W, m_W);

    // Определяем длины вертикальной и горизонтальной линий
    int verticalLength = 2;     // Высота вертикальной линии в квадратах
    int horizontalLength = 1;   // Длина горизонтальной линии в квадратах

    // Проверяем, что в arrayColor достаточно цветов
    if (arrayColor.size() < (verticalLength + horizontalLength)) {
        // Заполняем недостающие цвета по умолчанию или возвращаем ошибку
        // Здесь для простоты добавим недостающие цвета красного
        while (arrayColor.size() < (verticalLength + horizontalLength)) {
            arrayColor.push_back(Qt::red);
        }
    }

    // Рисуем вертикальную линию (столбец)
    for (int i = 0; i < verticalLength; ++i)
    {
        rect.moveTopLeft(QPoint(m_i * m_W, (m_k + i) * m_W));
        brush1.setColor(arrayColor[0]);
        painter.setBrush(brush1);
        painter.drawRect(rect);
    }

    // Рисуем горизонтальную линию (верхняя перекладина)
    for (int j = 1; j <= horizontalLength; ++j)
    {
        rect.moveTopLeft(QPoint((m_i + j) * m_W, m_k * m_W));
        brush1.setColor(arrayColor[0]);
        painter.setBrush(brush1);
        painter.drawRect(rect);
    }

}

void LFigure::setpos(int x, int y)  // установка координаты
{
    m_i = x;
    m_k = y;
}
