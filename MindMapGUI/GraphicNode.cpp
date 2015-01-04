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
    int width = this->_node->getWidth();
    int height = this->_node->getHeight();
    int x = this->_node->getX();
    int y = this->_node->getY() - height / 2;
    return QRectF(x, y, width, height);
}

QRectF GraphicNode::textRect() const
{
    int width = this->_node->getWidth() - 2 * INNER_PADDING;
    int height = this->_node->getHeight() - 2 * INNER_PADDING;
    int x = this->_node->getX() + INNER_PADDING;
    int y = this->_node->getY() - height / 2;
    return QRectF(x, y, width, height);
}

void GraphicNode::calculateTextRectSize()
{
    QFontMetrics fontMetrics = QFontMetrics(this->getFont());
    QRect rect = fontMetrics.boundingRect(QRect(0, 0, MAX_WIDTH, 0), _flags, QString::fromStdString(this->_node->getDescription()));
    this->_node->setRectSize(rect.width() + 2 * INNER_PADDING, rect.height() + 2 * INNER_PADDING);
}

QLine GraphicNode::getConnectLine() const
{
    QRectF rect = this->boundingRect();
    int startX = rect.left();
    int startY = rect.center().y();
    Component* parentNode = _node->getParent();
    if (parentNode)
    {
        int endX = parentNode->getX() + parentNode->getWidth();
        int endY = parentNode->getY();
        return QLine(startX, startY, endX, endY);
    }
    return QLine(startX, startY, startX, startY);
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