#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsView;
class QGraphicsScene;
class AxisItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent *event);

private:
    double amap(double v, double imin, double imax, double omin, double omax){
        return (v-imin)*(omax-omin)/(imax-imin)+omin;
    }

    QGraphicsView *view;
    QGraphicsScene *scene;
    AxisItem *axis;

    int timerId;
    double x;
};

#endif // MAINWINDOW_H
