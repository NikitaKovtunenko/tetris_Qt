#ifndef GLASS_H
#define GLASS_H
#include "figure.h"
#include <QWidget>
#include <QVector>


class Figure;
// класс стакана
class Glass : public QWidget
{
    Q_OBJECT

    const int W = 20;
    // интервал
    int m_timerinterval;
    // кол-во строк
    int m_rows;
    // кол-во столбцов
    int m_columns;
    // флаг игры
    bool gameOn = false;
    // счет
    int m_score;
    // матрица стакана
    QVector <QVector<QColor>> m_glassArray;
    // текущая фигура
    Figure *cur;
    // следующая фигура
    Figure *next;
    int id_tm;

    Q_PROPERTY(int rows READ rows WRITE setRows)
    Q_PROPERTY(int columns READ columns WRITE setColumns)

public:
    explicit Glass(QWidget *parent = nullptr);
    void clearGlass();
    void glassInt();
    int rows() const;
    void setRows(int newRows);
    int columns() const;
    void setColumns(int newColumns);
    void acceptColors(int a, int j);
    Figure* getRandomShape();

    ~Glass();

signals:
 void signalChangePattern(Figure*);
 void setScore(int);


public slots:
    void slotNewGame();

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);


    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event);



    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event);

};




#endif // GLASS_H
