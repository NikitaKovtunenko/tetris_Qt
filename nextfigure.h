#ifndef NEXTFIGURE_H
#define NEXTFIGURE_H

#include <QWidget>

class Figure;


class NextFigure : public QWidget
{
    Q_OBJECT

    Figure * next;
    bool game =false;


public:
    explicit NextFigure(QWidget *parent = nullptr);

signals:

protected slots:
    void slotChangePattern(Figure*);


    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // NEXTFIGURE_H
