#include "GraphicNode.h"
#include <iostream>

GraphicNode::GraphicNode(MindMapGUI* mainWindow, GUIPresentModel* presentModel, Component* node, QFont font)
{
    this->_presentModel = presentModel;
    this->_node = node;
    this->_mainWindow = mainWindow;
    this->_font = font;
    this->setFlags(QGraphicsItem::ItemIsSelectable);
}

QRectF GraphicNode::boundingRect() const
{
    Rect rect = this->_node->getBoundingRect();
    return QRectF(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}

QRectF GraphicNode::textRect() const
{
    int width = this->_node->getWidth() - 2 * INNER_PADDING;
    int height = this->_node->getHeight() - 2 * INNER_PADDING;
    int x = this->_node->getX() + INNER_PADDING;
    int y = this->_node->getY() - height / 2;
    return QRectF(x, y, width, height);
}

QLine GraphicNode::getConnectLine() const
{
    int side = this->_node->getSide();
    QRectF rect = this->boundingRect();
    int startX = side == LEFT ? rect.right() : rect.left();
    int startY = rect.center().y();
    Component* parentNode = _node->getParent();
    if (parentNode)
    {
        int endX = parentNode->getX() + (side == RIGHT ? parentNode->getWidth() : 0);
        int endY = parentNode->getY();
        return QLine(startX, startY, endX, endY);
    }
    return QLine(startX, startY, startX, startY);
}

void GraphicNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setFont(this->_font);
    painter->drawText(this->textRect(), Qt::TextWordWrap, QString::fromStdString(this->_node->getDescription()));
}

void GraphicNode::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    this->_presentModel->clickGraphicNode(this->_node);
}

void GraphicNode::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    if (clock() - this->_lastClickTime <= MIN_DOUBLE_CLICK_TIME)
        this->_mainWindow->editNodeDescription();
    else
    {
        this->_lastClickTime = clock();
        this->_presentModel->clickGraphicNode(this->_node);
    }
}

GraphicNode::~GraphicNode()
{
}