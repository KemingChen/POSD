#pragma once
#include "stdafx.h"
#include <QGraphicsItem>
#include <QPainter>
#include <time.h>
#include "MindMapGUI.h"
#include "GUIPresentModel.h"

class GraphicNode : public QGraphicsItem
{
    private:
        // Basic Params
        int _flags;
        QFont _font;
        MindMapGUI* _mainWindow;

        // Private Variable
        GUIPresentModel* _presentModel;
        Component* _node;
        clock_t _lastClickTime;

        // Private Method
        QRectF boundingRect() const;
        QRectF textRect() const;

    public:
        GraphicNode(MindMapGUI* mainWindow, GUIPresentModel* presentModel, Component* node, QFont font, int flags);
        QLine getConnectLine() const;
        ~GraphicNode();

    protected:
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};