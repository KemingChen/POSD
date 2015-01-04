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
        int _flags = Qt::AlignCenter | Qt::TextWordWrap;
        MindMapGUI* _mainWindow;

        // Private Variable
        GUIPresentModel* _presentModel;
        Component* _node;
        clock_t _lastClickTime;

        // Private Method
        void calculateTextRectSize();
        QFont getFont() const;

    public:
        GraphicNode(MindMapGUI* mainWindow, GUIPresentModel* presentModel, Component* node);
        QRectF boundingRect() const;
        QRectF textRect() const;
        QLine getConnectLine() const;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        ~GraphicNode();

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};