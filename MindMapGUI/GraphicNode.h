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
        MindMapGUI* _mainWindow;
        QFont _font;

        // Private Variable
        GUIPresentModel* _presentModel;
        Component* _node;
        clock_t _lastClickTime;

        // Private Method
        QRectF boundingRect() const;
        QRectF textRect() const;

    public:
        QLine getConnectLine() const;
        GraphicNode(MindMapGUI* mainWindow, GUIPresentModel* presentModel, Component* node, QFont font);
        ~GraphicNode();

    protected:
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};