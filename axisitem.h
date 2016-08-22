#ifndef AXISITEM_H
#define AXISITEM_H

#include <QGraphicsObject>
#include <QGraphicsItem>

class AxisItem : public QGraphicsObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QMap<double,double> data READ getData WRITE setData NOTIFY dataChanged)

    AxisItem(QGraphicsItem *parent=Q_NULLPTR);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QMap<double,double> getData();

public slots:
    void setData(QMap<double,double> data);
    void addDataPoint(double x, double y);

signals:
    void dataChanged();

private:
    void updateMinMax();

    const int axisPad=20;
    QMap<double,double> _data;
    double _xmin, _xmax, _ymin, _ymax;
};

#endif // AXISITEM_H
