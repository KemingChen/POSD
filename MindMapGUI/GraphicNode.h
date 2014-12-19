#pragma once
#include "stdafx.h"
#include <QGraphicsItem>
#include <QPainter>
#include <time.h>
#include "Subject.h"

class GraphicNode : public Subject, public QGraphicsItem
{
    private:
        // Basic
        int const PADDING = 5;
        int const RECT_WIDTH = 70;
        int const RECT_HEIGHT = 50;

        // Variable
        int _x;
        int _y;
        Component* _node;
        GraphicNode* _parent;
        clock_t _lastClickTime;

    public:
        GraphicNode(Component* node, GraphicNode* parent = NULL);
        QRectF boundingRect() const;
        QLineF getConnectLine() const;
        QPoint* getConnectPoint();
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        void setPosition(int x, int y);
        Component* getComponent();
        ~GraphicNode();

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};