#include "GraphicNode.h"

GraphicNode::GraphicNode(int levelX, int levelY, Component* node, QPoint* parentConnectPoint)
{
    _parentConnectPoint = parentConnectPoint;
    _levelX = levelX;
    _levelY = levelY;
    _node = node;
    _x = _levelX * BOUNDING_WIDTH;
    _y = _levelY * BOUNDING_HEIGHT;
    _isSelected = false;
}

QRectF GraphicNode::boundingRect() const
{
    return QRectF(0, 0, BOUNDING_WIDTH * (_levelX + 1), BOUNDING_HEIGHT * (_levelY + 1));
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
    painter->drawText(textRect, Qt::AlignCenter | Qt::TextWordWrap, "Title");
    if (_parentConnectPoint)
        painter->drawLine(QPoint(_x, _y + RECT_HEIGHT / 2), *_parentConnectPoint);
    if (_isSelected)
    {
        painter->setPen(Qt::red);
        painter->drawRect(nodeRect);
    }
}

GraphicNode::~GraphicNode()
{
}