#ifndef FIGURE_H
#define FIGURE_H

#include <QVector>
class QColor;
class QPainter;
class QPoint;
class Glass;
class Figure
{
public:
    enum class SIZE{
        O = 2,
        I = 3,
        L = 2
    };
    enum TYPE{
        O,
        I,
        L
    };

public:
    virtual void goLeft() = 0;
    virtual void goRight() = 0;
    virtual void goDown(int) = 0;
    virtual int getFirstI() = 0;
    virtual  int getFirstK() =0;
    virtual int getLastI() = 0 ;
    virtual int getLastK() =0 ;
    virtual SIZE getSize() {return size;};
    virtual void rotateColors(int) =0;
    virtual void makeRandomColors() =0;
    virtual void paintFigure(QPainter &painter) =0;
    virtual  void setpos(int x, int y) =0;
    virtual TYPE getType(){return type;}
    virtual ~Figure() = default;
    friend class Glass;
protected:
    // массив цветов
    QVector<QColor> arrayColor;
    // позиция элемента
    int m_i;
    // позиция элемента
    int m_k;
    // размер клетки
    const int m_W = 20;
    QVector <QColor> palitra;
    SIZE size;
    TYPE type;


};

#endif // FIGURE_H
