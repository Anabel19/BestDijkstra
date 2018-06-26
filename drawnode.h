#ifndef DRAWNODE_H
#define DRAWNODE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "BigGraph.h"

class DrawNode : public QGraphicsItem{
public:
    QPointF &point;
    CBigGraph::Node * realNode;
    bool pressed;

    DrawNode(CBigGraph::Node *node): point(node->value){
        realNode = node;
    }
    QRectF boundingRect() const{
        return QRectF(point.x()-3,point.y()-3, 6,6);
    }
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget ){
        QRectF rect = boundingRect();

        painter->setBrush(Qt::red);
        QPen pen(Qt::black, 1);
        painter->setPen(pen);
        painter->drawEllipse(point,3,3);

    }
    //QRectF boundingRect() const;
    //void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);


};
/*
QRectF DrawNode::boundingRect() const{
    return QRectF(point.x()-3,point.y()-3, 6,6);
}

void DrawNode::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget ){
    QRectF rect = boundingRect();

    painter->setBrush(Qt::red);
    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    painter->drawEllipse(point,3,3);

}
*/
#endif // DRAWNODE_H
