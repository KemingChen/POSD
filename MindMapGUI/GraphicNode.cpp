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
    QRectF rect = this->boundingRect();
    int startX = side == LEFT ? rect.right() : rect.left();
    int startY = rect.center().y();
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
    if (this->_node->getIsSelected())
        painter->setPen(Qt::red);
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