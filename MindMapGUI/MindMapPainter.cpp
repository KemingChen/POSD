#include "MindMapPainter.h"
#include <QFontMetrics>
#include "GraphicNode.h"
#include "MindMapGUI.h"
#include "GUIPresentModel.h"

MindMapPainter::MindMapPainter(QGraphicsScene* scene, MindMapGUI* guiWindow, GUIPresentModel* presentModel)
{
    this->_scene = scene;
    this->_guiWindow = guiWindow;
    this->_presentModel = presentModel;
}

QFont MindMapPainter::getFont() const
{
    return QFont("Helvetica", 10, QFont::Bold);
}

void MindMapPainter::calculateTextRectSize(Component* node)
{
    QFontMetrics fontMetrics = QFontMetrics(this->getFont());
    QRect rect = fontMetrics.boundingRect(QRect(0, 0, MAX_WIDTH - 2 * INNER_PADDING, 0), Qt::TextWordWrap, QString::fromStdString(node->getDescription()));
    node->setRectSize(rect.width() + 2 * INNER_PADDING, rect.height() + 2 * INNER_PADDING);
}

void MindMapPainter::drawNode(Component* node)
{
    GraphicNode* graphicNode = new GraphicNode(this->_guiWindow, this->_presentModel, node, this->getFont());
    this->_scene->addItem(graphicNode);
    this->_scene->addLine(graphicNode->getConnectLine());
}

void MindMapPainter::drawRectangle(Rect rect)
{
    this->_scene->addRect(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}

void MindMapPainter::drawTriangle(Rect rect)
{
    QPoint point1(rect.getX() + rect.getWidth() / 2, rect.getY());
    QPoint point2(rect.getX(), rect.getY() + rect.getHeight());
    QPoint point3(rect.getX() + rect.getWidth(), rect.getY() + rect.getHeight());
    this->_scene->addLine(QLine(point1, point2));
    this->_scene->addLine(QLine(point2, point3));
    this->_scene->addLine(QLine(point3, point1));
}

void MindMapPainter::drawEllipse(Rect rect)
{
    this->_scene->addEllipse(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}

MindMapPainter::~MindMapPainter()
{
}