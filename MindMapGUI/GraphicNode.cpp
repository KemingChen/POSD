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
    Rect rect = this->_presentModel->tryFindNode(this->_node->getId())->getBoundingRect();
    return QRectF(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}

QRectF GraphicNode::textRect() const
{
    Rect rect = this->_node->getBoundingRect();
    rect.setWidth(rect.getWidth() - 2 * INNER_PADDING);
    rect.setHeight(rect.getHeight() - 2 * INNER_PADDING);
    rect.setX(rect.getX() + INNER_PADDING);
    rect.setY(rect.getY() + INNER_PADDING);
    return QRectF(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}

QLine GraphicNode::getConnectLine() const
{
    int side = this->_node->getSide();
    Rect rect = this->_node->getBoundingRect();
    int startX = side == LEFT ? rect.getX() + rect.getWidth() : rect.getX();
    int startY = rect.getY() + rect.getHeight() / 2;
    Component* parentNode = _node->getParent();
    if (parentNode)
    {
        Rect rect = parentNode->getBoundingRect();
        int endX = rect.getX() + (side == RIGHT ? rect.getWidth() : 0);
        int endY = rect.getY() + rect.getHeight() / 2;
        return QLine(startX, startY, endX, endY);
    }
    return QLine(startX, startY, startX, startY);
}

void GraphicNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (this->_node == this->_node->getRealComponent())
    {
        if (this->_presentModel->isSelectedNode(this->_node->getId()))
            painter->setPen(Qt::red);
        painter->setFont(this->_font);
        painter->drawText(this->textRect(), Qt::TextWordWrap, QString::fromStdString(this->_node->getDescription()));
    }
}

void GraphicNode::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    this->_presentModel->clickGraphicNode(this->_node->getId());
}

void GraphicNode::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    if (clock() - this->_lastClickTime <= MIN_DOUBLE_CLICK_TIME)
        this->_mainWindow->editNodeDescription();
    else
    {
        this->_lastClickTime = clock();
        this->_presentModel->clickGraphicNode(this->_node->getId());
    }
}

GraphicNode::~GraphicNode()
{
}