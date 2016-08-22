#include <QFontMetrics>
#include <QtMath>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>

#include "axisitem.h"

AxisItem::AxisItem(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    _data[0]=0;
}

QRectF AxisItem::boundingRect() const {
    return QRectF(0,0,500,500);
}

void AxisItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    QRect rect=option->rect.adjusted(axisPad, axisPad, -axisPad, -axisPad);
    painter->drawLine(rect.topLeft(), rect.bottomLeft());
    painter->drawLine(rect.bottomLeft(), rect.bottomRight());

    QPainterPath path;
    QList<double> keys=_data.keys();
    qSort(keys);
    for(int i=0; i<keys.length(); i++){
        double key=keys[i];
        double value=_data[key];
        double x=((key-_xmin)/(_xmax-_xmin))*rect.width();
        x+=rect.x();
        double y=((value-_ymin)/(_ymax-_ymin))*rect.height();
        y+=rect.y();

        if(i==0) path.moveTo(x,y);
        else path.lineTo(x,y);
    }
    painter->drawPath(path);
    painter->restore();
}

QMap<double,double> AxisItem::getData(){
    return _data;
}

void AxisItem::setData(QMap<double, double> data){
    _data=data;
    updateMinMax();
    emit dataChanged();
    update();
}

void AxisItem::addDataPoint(double x, double y){
    _data[x]=y;
    updateMinMax();
    emit dataChanged();
    update();
}

void AxisItem::updateMinMax(){
    QList<double> values=_data.keys();
    auto mm=std::minmax_element(values.begin(), values.end());
    _xmin=*mm.first;
    _xmax=*mm.second;

    values=_data.values();
    mm=std::minmax_element(values.begin(), values.end());
    _ymin=qFloor(*mm.first);
    _ymax=qCeil(*mm.second);

    emit dataChanged();
    update();
}
