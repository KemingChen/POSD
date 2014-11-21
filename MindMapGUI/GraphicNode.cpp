#include "GraphicNode.h"
#include <iostream>
#include "INotifyGraphics.h"

#define MIN_DOUBLE_CLICK_TIME 20

GraphicNode::GraphicNode(int levelX, int levelY, Component* node, INotifyGraphics* notify, QPoint* parentConnectPoint)
{
    _notify = notify;
    _parentConnectPoint = parentConnectPoint;
    _levelX = levelX;
    _levelY = levelY;
    _node = node;
    _x = _levelX * BOUNDING_WIDTH;
    _y = _levelY * BOUNDING_HEIGHT;
    _isSelected = false;
    setFlags(QGraphicsItem::ItemIsSelectable);
    _lastClickTime = clock();
}

QRectF GraphicNode::boundingRect() const
{
    return  QRectF(BOUNDING_WIDTH * _levelX, BOUNDING_HEIGHT * _levelY, RECT_WIDTH, RECT_HEIGHT);
}

QPoint* GraphicNode::getConnectPoint()
{
    return new QPoint(_x + RECT_WIDTH, _y + RECT_HEIGHT / 2);
}

void GraphicNode::setSelected(bool isSelected)
{
    _isSelected = isSelected;
}

void GraphicNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    const QRectF nodeRect(_x, _y, RECT_WIDTH, RECT_HEIGHT);
    const QRectF textRect(_x + PADDING, _y + PADDING, RECT_WIDTH - 2 * PADDING, RECT_HEIGHT - 2 * PADDING);
    painter->drawRect(nodeRect);
    painter->drawText(textRect, Qt::AlignCenter | Qt::TextWordWrap, QString::fromStdString(_node->getDescription()));
    if (_parentConnectPoint)
        painter->drawLine(QPoint(_x, _y + RECT_HEIGHT / 2), *_parentConnectPoint);
    if (_isSelected)
    {
        painter->setPen(Qt::red);
        painter->drawRect(nodeRect);
    }
}

void GraphicNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);
    _notify->doubleClickGraphicNode(_node);
}

void GraphicNode::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
    _notify->clickGraphicNode(_node);
}

Component* GraphicNode::getComponent()
{
    return _node;
}

GraphicNode::~GraphicNode()
{
}