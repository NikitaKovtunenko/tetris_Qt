#ifndef OFIGURE_H
#define OFIGURE_H

#include <figure.h>

class OFigure:public Figure
{
public:
    OFigure();
    void goLeft() override;
    void goRight() override;
    void goDown(int )override;
    int getFirstI()override;
    int getFirstK()override;
    int getLastI()override;
    int getLastK()override;
    void rotateColors(int)override;
    void makeRandomColors()override;
    void paintFigure(QPainter &painter)override;
    void setpos(int x, int y)override;
    ~OFigure() override = default;
};

#endif // OFIGURE_H
