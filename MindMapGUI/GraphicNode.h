#pragma once
#include "stdafx.h"
#include <QGraphicsItem>
#include <QPainter>
#include "GUIPresentModel.h"

class GraphicNode : public QGraphicsItem
{
    private:
        // Basic Params
        int _flags = Qt::AlignCenter | Qt::TextWordWrap;
        QPaintDevice* _device;

        // Private Variable
        GUIPresentModel* _presentModel;
        Component* _node;

        // Private Method
        void calculateTextRectSize();
        QFont getFont() const;

    public:
        GraphicNode(QPaintDevice* device, GUIPresentModel* presentModel, Component* node);
        QRectF boundingRect() const;
        QRectF textRect() const;
        QLine getConnectLine() const;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        ~GraphicNode();

    protected:
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};