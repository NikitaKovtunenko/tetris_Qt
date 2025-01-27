#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QObject::connect(ui->pushButton_NewGame,SIGNAL(clicked()),ui->glass,SLOT(slotNewGame()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

