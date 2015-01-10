#include "GUIDisplayVisitor.h"
#include <iostream>
#include <algorithm>
#include "Root.h"
#include "Node.h"
using namespace std;

#define LEVEL_X_WIDTH 120
#define OUTTER_PADDING 5

GUIDisplayVisitor::GUIDisplayVisitor(IGraphic* painter)
{
    this->_yLeft = 0;
    this->_yRight = 0;
    this->_nowLevel = 0;
    this->_painter = painter;
}

int GUIDisplayVisitor::calculateLevel(Component* node)
{
    return node->getLevel() * node->getSide();
}

void GUIDisplayVisitor::visit(Root* node)
{
    this->_painter->calculateTextRectSize(node);
    int x = this->calculateLevel(node) * LEVEL_X_WIDTH;
    int y = this->averageChildY(node);
    node->setPosition(x, y);
    _components.push_back(node);
    this->finish();
}

void GUIDisplayVisitor::visit(Node* node)
{
    this->_painter->calculateTextRectSize(node);
    int* nowY = node->getSide() == RIGHT ? &this->_yRight : &this->_yLeft;
    int nowLevel = this->calculateLevel(node);

    int x = nowLevel * LEVEL_X_WIDTH;
    int y;
    if (this->_nowLevel == 0 || this->_nowLevel * nowLevel < 0 || abs(this->_nowLevel) <= abs(nowLevel))
    {
        y = *nowY + node->getHeight() / 2;
        *nowY += node->getHeight() / 2 + OUTTER_PADDING;
    }
    else
    {
        y = this->averageChildY(node);
        if (y - node->getHeight() / 2 < this->getLevelBottomY(nowLevel))
            y = this->getLevelBottomY(nowLevel) + node->getHeight() / 2 + OUTTER_PADDING;
    }

    node->setPosition(x, y);
    _components.push_back(node);
    this->_nowLevel = nowLevel;

    int newY = y + node->getHeight() / 2 + OUTTER_PADDING;
    if (newY > *nowY)
        *nowY = newY;
    this->saveLevelBottomY(nowLevel, y + node->getHeight() / 2);
}

void GUIDisplayVisitor::visit(Decorate* node)
{
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

void GUIDisplayVisitor::finish()
{
    for (vector<Component*>::iterator iNode = this->_components.begin(); iNode != this->_components.end(); iNode++)
    {
        (*iNode)->draw(this->_painter);
    }
}

GUIDisplayVisitor::~GUIDisplayVisitor()
{
}