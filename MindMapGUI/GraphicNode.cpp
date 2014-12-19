#include "GraphicNode.h"
#include <iostream>

#define MIN_DOUBLE_CLICK_TIME 200

GraphicNode::GraphicNode(Component* node, GraphicNode* parent)
{
    this->_subjectName = "GraphicNode." + node->getDescription();
    _parent = parent;
    _node = node;
    _lastClickTime = clock();
    setFlags(QGraphicsItem::ItemIsSelectable);
}

QRectF GraphicNode::boundingRect() const
{
    return  QRectF(_x, _y, _node->getWidth(), _node->getHeight());
}

QLineF GraphicNode::getConnectLine() const
{
    QPoint start(_x, _y + _node->getHeight() / 2 + INNER_PADDING);
    return QLineF(start, _parent ? * (_parent->getConnectPoint()) : start);
}

QPoint* GraphicNode::getConnectPoint()
{
    return new QPoint(_x + _node->getWidth() + 2 * INNER_PADDING, _y + _node->getHeight() / 2 + INNER_PADDING);
}

void GraphicNode::setPosition(int x, int y)
{
    _x = x;
    _y = y;
}

void GraphicNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    const QRectF nodeRect(_x, _y, _node->getWidth() + 2 * INNER_PADDING, _node->getHeight() + 2 * INNER_PADDING);
    const QRectF textRect(_x + INNER_PADDING, _y + INNER_PADDING, _node->getWidth(), _node->getHeight());
    painter->drawRect(nodeRect);
    painter->drawText(textRect, Qt::AlignCenter | Qt::TextWordWrap, QString::fromStdString(_node->getDescription()));
    if (_node->getIsSelected())
    {
        painter->setPen(Qt::red);
        painter->drawRect(nodeRect);
    }
}

void GraphicNode::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
    notify(SUBJECT_CLICK, _node->getId());
}

void GraphicNode::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    if (clock() - _lastClickTime <= MIN_DOUBLE_CLICK_TIME)
        notify(SUBJECT_DB_CLICK, _node->getId());
    else
        notify(SUBJECT_CLICK, _node->getId());
    _lastClickTime = clock();
}

Component* GraphicNode::getComponent()
{
    return _node;
}

GraphicNode::~GraphicNode()
{
}