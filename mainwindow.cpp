#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimerEvent>

#include "mainwindow.h"
#include "axisitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), x(0)
{
    setWindowTitle("QtPlot");

    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,600,600);
    view=new QGraphicsView(scene, this);

    axis=new AxisItem();
    scene->addItem(axis);
    axis->setPos(50,50);

    setCentralWidget(view);

    timerId=startTimer(1000);
}

MainWindow::~MainWindow(){}

void MainWindow::timerEvent(QTimerEvent *event){
    if(timerId!=event->timerId()) return;
    double y=amap((double)qrand(), 0., (double)(RAND_MAX), 0., 1023.);
    axis->addDataPoint(x, y);
    x+=1.;
}
