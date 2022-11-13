#ifndef FIGURE_H
#define FIGURE_H

#include <QVector>
class QColor;
class QPainter;
class QPoint;
class Glass;
class Figure
{

    QVector<QColor> arrayColor;
    int m_i;
    int m_k;
    const int m_W = 20;
    QVector <QColor> palitra;

public:
    Figure();
    void goLeft();
    void goRight();
    void goDown(int );
    int getFirstI();
    int getFirstK();
    int getLastI();
    int getLastK();
    void rotateColors(int);
    void makeRandomColors();
    void paintFigure(QPainter &painter);
    void setpos(int x, int y);

    ~Figure();

    friend class Glass;

};

#endif // FIGURE_H
