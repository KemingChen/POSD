#include "GUIDisplayVisitor.h"
#include <iostream>
#include <algorithm>
#include "Root.h"
#include "Node.h"
#include "Decorate.h"
using namespace std;

GUIDisplayVisitor::GUIDisplayVisitor(IGraphic* painter)
{
    this->_yLeft = 0;
    this->_yRight = 0;
    this->_nowLevel = 0;
    this->_painter = painter;
}

int GUIDisplayVisitor::averageChildY(Component* node)
{
    NodeList* nodeList = node->getNodeList();
    if (nodeList->size() == 0)
        return 0;
    vector<int> childsY;
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        childsY.push_back((*iNode)->getY());
    }
    sort(childsY.begin(), childsY.end());
    int sum = 0;
    sum += childsY.front();
    sum += childsY.back();
    return sum / 2;
}

int GUIDisplayVisitor::calculateLevel(Component* node)
{
    return node->getLevel() * node->getSide();
}

void GUIDisplayVisitor::visit(Root* node)
{
    this->_painter->calculateTextRectSize(node);
    int y = this->averageChildY(node);
    node->setPosition(0, y);
    this->saveLevelMaxWidth(node->getLevel(), node->getWidth());
    _components.push_back(node);
}

void GUIDisplayVisitor::visit(Node* node)
{
    this->_painter->calculateTextRectSize(node);
    int* nowY = node->getSide() == RIGHT ? &this->_yRight : &this->_yLeft;
    int nowLevel = this->calculateLevel(node);

    int y;
    if (this->_nowLevel == 0 || this->_nowLevel * nowLevel < 0 || abs(this->_nowLevel) <= abs(nowLevel))
    {
        y = *nowY + node->getHeight() / 2;
        *nowY += node->getHeight() / 2 + OUTTER_Y_PADDING;
    }
    else
    {
        y = this->averageChildY(node);
        if (y - node->getHeight() / 2 < this->getLevelBottomY(nowLevel))
            y = this->getLevelBottomY(nowLevel) + node->getHeight() / 2 + OUTTER_Y_PADDING;
    }

    node->setPosition(0, y);
    this->saveLevelMaxWidth(nowLevel, node->getWidth());
    _components.push_back(node);
    this->_nowLevel = nowLevel;

    int newY = y + node->getHeight() / 2 + OUTTER_Y_PADDING;
    if (newY > *nowY)
        *nowY = newY;
    this->saveLevelBottomY(nowLevel, y + node->getHeight() / 2);
}

void GUIDisplayVisitor::visit(Decorate* node)
{
    Component* originalNode = node->getOriginalComponent();
    node->setRectSize(originalNode->getWidth(), originalNode->getHeight());
    this->saveLevelMaxWidth(this->calculateLevel(node), node->getWidth());
    node->setPosition(originalNode->getX(), originalNode->getY());
    this->_components.push_back(node);
}

void GUIDisplayVisitor::finish()
{
    for (vector<Component*>::reverse_iterator iNode = this->_components.rbegin(); iNode != this->_components.rend(); iNode++)
    {
        Component* node = (*iNode);
        node->setPosition(this->getLevelX(this->calculateLevel(node)), node->getY());
        node->draw(this->_painter);
    }
}

void GUIDisplayVisitor::saveLevelBottomY(int level, int y)
{
    this->_yLevelMap[level] = y;
}

int GUIDisplayVisitor::getLevelBottomY(int level)
{
    if (this->_yLevelMap[level])
        return this->_yLevelMap[level];
    return -1000;
}

void GUIDisplayVisitor::saveLevelMaxWidth(int level, int width)
{
    int levelWidth = this->_maxWidthLevelMap[level];
    if (!levelWidth || levelWidth < width)
        this->_maxWidthLevelMap[level] = width;
}

int GUIDisplayVisitor::getLevelX(int level)
{
    int sum = 0;
    if (level == 0)
        return 0;
    else if (level > 0)
        for (int nowLevel = 0; nowLevel < level; nowLevel++)
            sum += (this->_maxWidthLevelMap[nowLevel] / 2 + OUTTER_X_PADDING + this->_maxWidthLevelMap[nowLevel + 1] / 2);
    else
        for (int nowLevel = 0; nowLevel > level; nowLevel--)
            sum -= (this->_maxWidthLevelMap[nowLevel] / 2 + OUTTER_X_PADDING + this->_maxWidthLevelMap[nowLevel - 1] / 2);
    return sum;
}

GUIDisplayVisitor::~GUIDisplayVisitor()
{
}