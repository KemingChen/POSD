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

int MindMapPainter::getFlags() const
{
    return Qt::TextWordWrap;
}

void MindMapPainter::calculateTextRectSize(Component* node)
{
    QFontMetrics fontMetrics = QFontMetrics(this->getFont());
    QRect rect = fontMetrics.boundingRect(QRect(0, 0, MAX_WIDTH - 2 * INNER_PADDING, 0), this->getFlags(), QString::fromStdString(node->getDescription()));
    node->setRectSize(rect.width() + 2 * INNER_PADDING, rect.height() + 2 * INNER_PADDING);
}

void MindMapPainter::drawGraphicNode(Component* node)
{
    GraphicNode* graphicNode = new GraphicNode(this->_guiWindow, this->_presentModel, node, this->getFont(), this->getFlags());
    this->_scene->addItem(graphicNode);
    this->_scene->addLine(graphicNode->getConnectLine());
}

MindMapPainter::~MindMapPainter()
{
}