#pragma once
#include "stdafx.h"
#include <QGraphicsItem>
#include <QPainter>

class INotifyGraphics;
class GraphicNode : public QGraphicsItem
{
    private:
        int const PADDING = 5;
        int const RECT_WIDTH = 70;
        int const RECT_HEIGHT = 50;
        int const BOUNDING_WIDTH = 120;
        int const BOUNDING_HEIGHT = 80;
        int _levelX;
        int _levelY;
        int _x;
        int _y;
        bool _isSelected;
        Component* _node;
        QPoint* _parentConnectPoint;
        INotifyGraphics* _notify;

    public:
        GraphicNode(int levelX, int levelY, Component* node, INotifyGraphics* notify, QPoint* parentConnectPoint = NULL);
        QRectF boundingRect() const;
        QPoint* getConnectPoint();
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        void setSelected(bool isSelected);
        void click();
        Component* getComponent();
        ~GraphicNode();

    protected:
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
};