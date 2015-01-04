#include "GraphicNode.h"
#include <iostream>

GraphicNode::GraphicNode(QPaintDevice* device, GUIPresentModel* presentModel, Component* node)
{
    this->_presentModel = presentModel;
    this->_node = node;
    this->_device = device;
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->calculateTextRectSize();
}

QRectF GraphicNode::boundingRect() const
{
    return QRectF(this->_node->getX(), this->_node->getX(), this->_node->getWidth() + 2 * INNER_PADDING, this->_node->getHeight() + 2 * INNER_PADDING);
}

QRectF GraphicNode::textRect() const
{
    return QRectF(this->_node->getX() + INNER_PADDING, this->_node->getX() + INNER_PADDING, this->_node->getWidth(), this->_node->getHeight());
}

void GraphicNode::calculateTextRectSize()
{
    QFontMetrics fontMetrics = QFontMetrics(this->getFont());
    QRect rect = fontMetrics.boundingRect(QRect(0, 0, MAX_WIDTH, 0), _flags, QString::fromStdString(this->_node->getDescription()));
    this->_node->setPosition(0, 0);
    this->_node->setRectSize(rect.width(), rect.height());
}

QFont GraphicNode::getFont() const
{
    return QFont("Helvetica", 10, QFont::Bold);
}

void GraphicNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setFont(this->getFont());
    painter->drawRect(this->boundingRect());
    painter->drawText(this->textRect(), _flags, QString::fromStdString(this->_node->getDescription()));
    if (_node->getIsSelected())
    {
        painter->setPen(Qt::red);
        painter->drawRect(this->boundingRect());
    }
}

void GraphicNode::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

GraphicNode::~GraphicNode()
{
}