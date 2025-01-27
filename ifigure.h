#ifndef IFIGURE_H
#define IFIGURE_H

#include <QVector>
#include <figure.h>
class QColor;
class QPainter;
class QPoint;
class Glass;

class IFigure: public Figure
{
public:
    IFigure();
    void goLeft()override;
    void goRight()override;
    void goDown(int )override;
    int getFirstI()override;
    int getFirstK()override;
    int getLastI()override;
    int getLastK()override;
    void rotateColors(int)override;
    void makeRandomColors()override;
    void paintFigure(QPainter &painter)override;
    void setpos(int x, int y)override;

    ~IFigure()override = default;
};

#endif // IFIGURE_H
