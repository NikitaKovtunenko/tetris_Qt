#ifndef LFIGURE_H
#define LFIGURE_H
#include <figure.h>

class LFigure:public Figure
{
public:
    LFigure();
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

    ~LFigure()override = default;
};

#endif // LFIGURE_H
