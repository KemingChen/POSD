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
    return  QRectF(_x, _y, RECT_WIDTH, RECT_HEIGHT);
}

QLineF GraphicNode::getConnectLine() const
{
    QPoint start(_x, _y + RECT_HEIGHT / 2);
    return QLineF(start, _parent ? * (_parent->getConnectPoint()) : start);
}

QPoint* GraphicNode::getConnectPoint()
{
    return new QPoint(_x + RECT_WIDTH, _y + RECT_HEIGHT / 2);
}

void GraphicNode::setPosition(int x, int y)
{
    _x = x;
    _y = y;
}

void GraphicNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    const QRectF nodeRect(_x, _y, RECT_WIDTH, RECT_HEIGHT);
    const QRectF textRect(_x + PADDING, _y + PADDING, RECT_WIDTH - 2 * PADDING, RECT_HEIGHT - 2 * PADDING);
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