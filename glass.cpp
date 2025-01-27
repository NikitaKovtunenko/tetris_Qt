#include "glass.h"
#include <QColor>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <random>
#include <ifigure.h>
#include <ofigure.h>
#include <lfigure.h>

Glass::Glass(QWidget *parent)
    : QWidget{parent}
{
    cur = getRandomShape();
    next = getRandomShape();
    m_rows = 25;
    m_columns = 12;
    glassInt();
    clearGlass();

}

Figure* Glass::getRandomShape() {
    // Создаем устройство-генератор случайных чисел
    std::random_device rd;
    // Используем Mersenne Twister псевдослучайный генератор
    std::mt19937 gen(rd());
    // Определяем равномерное распределение от 0 до 2 включительно
    std::uniform_int_distribution<> distrib(0, 2);

    int randomValue = distrib(gen);

        switch (randomValue) {
        case 0:
            return new IFigure;
        case 1:
            return new LFigure;
        case 2:
            return new OFigure;
        default:
            return nullptr;
        }


}
// очистка стакана
void Glass::clearGlass()
{
    for(int i = 0; i < m_rows;++i)
    {
        for (int k = 0; k < m_columns; ++k) {
            m_glassArray[i][k] = QColor(160,160,160);
        }
    }
    m_score =0;
    m_timerinterval = 100;
}
// инициализация стакана
void Glass::glassInt()
{

    m_glassArray.resize(m_rows);

    for (int var = 0; var < m_rows; ++var) {

        m_glassArray[var].resize(m_columns);
    }

}
// ко-во строк
int Glass::rows() const
{
    return m_rows;
}
// установить ко-во строк
void Glass::setRows(int newRows)
{
    m_rows = newRows;
}
// ко-во столбцов
int Glass::columns() const
{
    return m_columns;
}
// установить ко-во столбцов
void Glass::setColumns(int newColumns)
{
    m_columns = newColumns;
}
// установка цвета
void Glass::acceptColors(int a, int j)
{
    if(gameOn && (a >= 0 && j >=0))
    {
        for(int i = 0; i < (int)cur->getSize();++i)
        {
            if(cur->getType() == Figure::TYPE::O)
            {
                m_glassArray[a+i][j ] =
                    cur->arrayColor[0];
                m_glassArray[a+i][j+1] =
                    cur->arrayColor[0];
            }else if(cur->getType() == Figure::TYPE::I) {
                m_glassArray[a+i][j] =
                    cur->arrayColor[i];
            }else if(cur->getType() == Figure::TYPE::L){
                m_glassArray[a+i][j] =
                    cur->arrayColor[0];
                if(i == 0){
                    m_glassArray[a+i][j + 1] =
                        cur->arrayColor[0];
                }

            }
        }

        // обработка горизонтальных совпадений
        for (int i = a; i < a + (int)cur->getSize(); ++i)
        {
            for(int k = 0; k < m_columns-2 ; ++k)
            {
                if(m_glassArray[i][k] != QColor(160,160,160) && (m_glassArray[i][k] == m_glassArray[i][k+1] && m_glassArray[i][k] == m_glassArray[i][k+2]))
                {
                    for (int var = i  ; var > 1; --var)
                    {
                        m_glassArray[var][k] = m_glassArray[var-1][k];
                        m_glassArray[var][k+1] = m_glassArray[var-1][k+1];
                        m_glassArray[var][k+2] = m_glassArray[var-1][k+2];
                        continue;
                    }
                    m_score += 3;
                }
            }
        }

        // обработка вертикальных совпадений
        for(int i = a ; i< m_rows-2;++i)
        {
            if(m_glassArray[i][j] != QColor(160,160,160) && m_glassArray[i][j] == m_glassArray[i+1][j] && m_glassArray[i+1][j]== m_glassArray[i+2][j])
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

        delete cur;
        cur = next;
        next = getRandomShape();

        next->setpos(0,0);
        cur->setpos(5,0);
        next->makeRandomColors();
        emit signalChangePattern(next);
    }
}

Glass::~Glass()
{
    //delete cur;
    // delete next;
}
// запуск новой игры
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
// отрисовка стакана
void Glass::paintEvent(QPaintEvent *)
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

    if(gameOn)
    {

        cur->paintFigure(painter);
    }

    painter.end();
}
// обработка пользовательского ввода
void Glass::keyPressEvent(QKeyEvent *event)
{
    if(gameOn)
    {
        switch (event->key()) {
        case Qt::Key_Left:
        {
            if(cur->getType() == Figure::I || cur->getType() == Figure::L){
                if(cur->getLastI() != 0)
                    if(m_glassArray[cur->getLastK()][cur->getLastI()-1] == QColor(160,160,160))
                        cur->goLeft();
            }else if(cur->getType() == Figure::O){
                if(cur->getLastI() != 1)
                    if(m_glassArray[cur->getLastK()][cur->getLastI()-2] == QColor(160,160,160))
                        cur->goLeft();
            }
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

            for(int i = cur->getLastK() + 1; i< m_rows ;++i)
            {

                if(cur->getType() == Figure::O){
                    if(m_glassArray[i][cur->getLastI()] != QColor(160,160,160) || m_glassArray[i][cur->getFirstI()] != QColor(160,160,160))
                    {
                        cur->goDown(i);
                        break;
                    }else if(m_glassArray[m_rows-1][cur->getLastI()]==QColor(160,160,160) && m_glassArray[m_rows-1][cur->getFirstI()]==QColor(160,160,160))
                    {
                        cur->goDown(m_rows);
                        break;
                    }

                }else if(cur->getType() == Figure::I){
                    if(m_glassArray[i][cur->getLastI()] != QColor(160,160,160))
                    {
                        cur->goDown(i);
                        break;
                    }else if(m_glassArray[m_rows-1][cur->getLastI()]==QColor(160,160,160))
                    {
                        cur->goDown(m_rows);
                        break;
                    }

                }else if(cur->getType() == Figure::L){

                    if(m_glassArray[i][cur->getLastI()] != QColor(160,160,160))
                    {
                        cur->goDown(i +1);
                        break;
                    }
                    else if( m_glassArray[i][cur->getFirstI()] != QColor(160,160,160))
                    {
                        cur->goDown(i );
                        break;
                    }else if(m_glassArray[m_rows-1][cur->getLastI()]==QColor(160,160,160) && m_glassArray[m_rows-1][cur->getFirstI()]==QColor(160,160,160))
                    {
                        cur->goDown(m_rows);
                        break;
                    }
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

    }  else
        QWidget::keyPressEvent(event);
}
// обработка события таймера
void Glass::timerEvent(QTimerEvent *)
{


    if (m_glassArray[3][cur->getFirstI()] != QColor(160,160,160))
    {
        QMessageBox sms;
        sms.setText("Конец игры!");

        sms.exec();
        this->killTimer(id_tm);
        gameOn = false;

    } else {

        if(cur->getType() == Figure::I){
            if(cur->getLastK()==m_rows-1)
                acceptColors(cur->getFirstK(),cur->getFirstI());
            else if(m_glassArray[cur->getLastK()+1][cur->getLastI()] == QColor(160,160,160) )
            {
                cur->m_k += 1;
                this->update();

            } else
            {
                acceptColors(cur->getFirstK(),cur->getFirstI());
            }
        }else if(cur->getType() == Figure::O){
            if(cur->getLastK()==m_rows-1)
                acceptColors(cur->getFirstK(),cur->getFirstI());
            else if(m_glassArray[cur->getLastK()+1][cur->getLastI()] == QColor(160,160,160) &&  m_glassArray[cur->getLastK()+1][cur->getLastI() -1] == QColor(160,160,160))
            {
                cur->m_k += 1;
                this->update();

            } else
            {
                acceptColors(cur->getFirstK(),cur->getFirstI());
            }
        }else if (cur->getType() == Figure::L){
            if(cur->getLastK()==m_rows-1)
                acceptColors(cur->getFirstK(),cur->getFirstI());
            else if(m_glassArray[cur->getFirstK() + 1][cur->getLastI()] == QColor(160,160,160) &&  m_glassArray[cur->getLastK()+1][cur->getLastI() -1] == QColor(160,160,160))
            {
                cur->m_k += 1;
                this->update();

            } else
            {
                acceptColors(cur->getFirstK(),cur->getFirstI());
            }
        }

    }
    this->update();
}



