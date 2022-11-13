#include "glass.h"
#include <QColor>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>

Glass::Glass(QWidget *parent)
    : QWidget{parent}
{
    cur = new Figure;
    next = new Figure;
    m_rows = 25;
    m_columns = 12;
    glassInt();
    clearGlass();



}

void Glass::clearGlass()
{
    for(int i = 0; i < m_rows;++i)
    {
        for (int k = 0; k < m_columns; ++k) {
            m_glassArray[i][k] = QColor(160,160,160);
        }
    }
    m_score =0;
    m_timerinterval = 500;
}

void Glass::glassInt()
{

    m_glassArray.resize(m_rows);

    for (int var = 0; var < m_rows; ++var) {

        m_glassArray[var].resize(m_columns);
    }

}

int Glass::rows() const
{
    return m_rows;
}

void Glass::setRows(int newRows)
{
    m_rows = newRows;
}

int Glass::columns() const
{
    return m_columns;
}

void Glass::setColumns(int newColumns)
{
    m_columns = newColumns;
}

void Glass::acceptColors(int a, int j)
{
    for(int i = 0; i < 3;++i)
    {
        m_glassArray[a+i][j] =
            cur->arrayColor[i];
    }

     //this->killTimer(id_tm);

    for (int i = a; i < a + 3; ++i)
    {
       for(int k = 0; k < m_columns-2 ; ++k)
       {
           if(m_glassArray[i][k] == m_glassArray[i][k+1] && m_glassArray[i][k] == m_glassArray[i][k+2])
           {
               for (int var = i  ; var > 1; --var)
               {
                   m_glassArray[var][k] = m_glassArray[var-1][k];
                   m_glassArray[var][k+1] = m_glassArray[var-1][k+1];
                   m_glassArray[var][k+2] = m_glassArray[var-1][k+2];

                   continue;
               }



           }
       }
    }


   for(int i = a ; i< m_rows-2;++i)
   {
       if(m_glassArray[i][j] == m_glassArray[i+1][j] && m_glassArray[i][j]== m_glassArray[i+2][j])
       {
               m_glassArray[i+2][j] = m_glassArray[i-1][j];
               m_glassArray[i+1][j] = m_glassArray[i-2][j];
               m_glassArray[i][j] = QColor(160,160,160);
               m_glassArray[i-1][j] = QColor(160,160,160);
               m_glassArray[i-2][j] = QColor(160,160,160);
               m_score += 3;
               continue;


       }
   }

emit setScore(m_score);

    Figure *tmp = cur;
    cur = next;
    next = tmp;
    tmp = nullptr;

    next->setpos(0,0);
    cur->setpos(5,0);
    next->makeRandomColors();
    emit signalChangePattern(next);
}

Glass::~Glass()
{
    //delete cur;
   // delete next;
}

void Glass::slotNewGame()
{
    gameOn = true;
    clearGlass();
    cur->setpos(5,0);
    cur->makeRandomColors();
    next->setpos(0,0);
    next->makeRandomColors();
    id_tm = this->startTimer(m_timerinterval);
    this->setFocus();
    this->repaint();
    emit signalChangePattern(next);
}

void Glass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);


    QPen pen(QColor(255,255,255));
    painter.setPen(pen);
    QRect rect(0,0,W,W);
    painter.drawRect(rect);

    QBrush brush;


    for (int i = 0; i < m_columns; ++i) {

        for (int k = 0; k < m_rows; ++k) {
            brush = m_glassArray[k][i];
            rect.moveTopLeft(QPoint(i*W,k*W));
            painter.drawRect(rect);
            painter.fillRect(rect,brush);

        }

    }
 painter.brushOrigin();

    if(gameOn)
    {

        cur->paintFigure(painter);
    }

}

void Glass::keyPressEvent(QKeyEvent *event)
{
    if(gameOn)
    {
        switch (event->key()) {
        case Qt::Key_Left:
        {
             if(cur->getLastI() != 0)
            if(m_glassArray[cur->getLastK()][cur->getLastI()-1] == QColor(160,160,160))
            cur->goLeft();
        }
            break;
        case Qt::Key_Right:
        {
            if(cur->getLastI() != 11)
            if(m_glassArray[cur->getLastK()][cur->getLastI()+1] == QColor(160,160,160))
            cur->goRight();
        }
            break;
        case Qt::Key_Up:
            cur->rotateColors(1);
            break;
        case Qt::Key_Down:
            cur->rotateColors(2);
            break;
        case Qt::Key_Space:
        {

           for(int i =0; i< m_rows ;++i)
           {

               if(m_glassArray[i][cur->getLastI()] != QColor(160,160,160))
               {
                   cur->goDown(i);
                   break;
               }else if(m_glassArray[m_rows-1][cur->getLastI()]==QColor(160,160,160))
               {
                   cur->goDown(m_rows);
                   break;
               }

           }

            acceptColors(cur->getFirstK(),cur->getFirstI());
            break;
        }
            break;
        default:
            QWidget::keyPressEvent(event);
            break;
        }

    } else
        QWidget::keyPressEvent(event);
}

void Glass::timerEvent(QTimerEvent *event)
{

    if (m_glassArray[3][cur->getFirstI()] != QColor(160,160,160))
    {
        QMessageBox sms;
        sms.setText("Конец игры!");
        sms.exec();
        this->killTimer(id_tm);

    } else {

        if(cur->getLastK()==m_rows-1)
        acceptColors(cur->getFirstK(),cur->getFirstI());
        else if(m_glassArray[cur->getLastK()+1][cur->getLastI()] == QColor(160,160,160))
        {
            //if(cur->getLastK()==m_rows-1)
          //  acceptColors(cur->getFirstK(),cur->getFirstI());
           // else
               cur->m_k += 1;
            this->update();

        } else
        {
            acceptColors(cur->getFirstK(),cur->getFirstI());
        }

   }

   this->update();
}



