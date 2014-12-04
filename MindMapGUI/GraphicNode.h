#pragma once
#include "stdafx.h"
#include <QGraphicsItem>
#include <QPainter>
#include <time.h>

class INotifyGraphics;
class GraphicNode : public QGraphicsItem
{
    private:
        // Basic
        int const PADDING = 5;
        int const RECT_WIDTH = 70;
        int const RECT_HEIGHT = 50;

        // Variable
        int _x;
        int _y;
        bool _isSelected;
        Component* _node;
        GraphicNode* _parent;
        INotifyGraphics* _notify;
        clock_t _lastClickTime;

    public:
        GraphicNode(Component* node, INotifyGraphics* notify, GraphicNode* parent = NULL);
        QRectF boundingRect() const;
        QLineF getConnectLine() const;
        QPoint* getConnectPoint();
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        void setSelected(bool isSelected);
        void setPosition(int x, int y);
        Component* getComponent();
        ~GraphicNode();

    protected:
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
};