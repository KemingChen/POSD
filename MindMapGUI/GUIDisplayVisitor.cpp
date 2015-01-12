#include "GUIDisplayVisitor.h"
#include <iostream>
#include <algorithm>
#include "Root.h"
#include "Node.h"
#include "Decorate.h"
using namespace std;

GUIDisplayVisitor::GUIDisplayVisitor(IGraphic* painter, Component* root)
{
    this->_yLeft = 0;
    this->_yRight = 0;
    this->_nowLevel = 0;
    this->_painter = painter;
    if (root != NULL)
    {
        root->accept(this);
        this->finish();
    }
}

int GUIDisplayVisitor::averageChildY(Component* node)
{
    NodeList* nodeList = node->getNodeList();
    int sum = 0;
    if (nodeList->size() > 0)
    {
        vector<int> childsY;
        for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
            childsY.push_back((*iNode)->getY());
        sort(childsY.begin(), childsY.end());

        sum += childsY.front();
        sum += childsY.back();
    }
    return sum / 2;
}

int* GUIDisplayVisitor::getNowY(Component* node)
{
    return node->getSide() == RIGHT ? &this->_yRight : &this->_yLeft;
}

void GUIDisplayVisitor::visit(Root* node)
{
    this->_painter->calculateTextRectSize(node);
    this->saveLevelMaxWidth(node->getLevel(), node->getWidth());

    node->setPosition(0, this->averageChildY(node));
    _components.push_back(node);
}

void GUIDisplayVisitor::visit(Node* node)
{
    if (!node->getIsCollapse())
    {
        this->_painter->calculateTextRectSize(node);
        this->saveLevelMaxWidth(node->getLevel(), node->getWidth());
        int* nowY = this->getNowY(node);

        int y;
        if (this->_nowLevel == 0 || this->_nowLevel * node->getLevel() < 0 || abs(this->_nowLevel) <= abs(node->getLevel()))
        {
            y = *nowY + node->getHeight() / 2;
            *nowY += node->getHeight() / 2 + OUTTER_Y_PADDING;
        }
        else
        {
            y = this->averageChildY(node);
            if (y - node->getHeight() / 2 < this->getLevelBottomY(node->getLevel()))
                y = this->getLevelBottomY(node->getLevel()) + node->getHeight() / 2 + OUTTER_Y_PADDING;
        }

        node->setPosition(0, y);
        this->_components.push_back(node);
        this->saveBottomY(node);
        this->_nowLevel = node->getLevel();
    }
}

void GUIDisplayVisitor::visit(Decorate* node)
{
    if (!node->getIsCollapse())
    {
        Component* originalNode = node->getOriginalComponent();
        node->setRectSize(originalNode->getWidth(), originalNode->getHeight());
        this->saveLevelMaxWidth(node->getLevel(), node->getWidth());

        node->setPosition(originalNode->getX(), originalNode->getY() + DECORATE_PADDING);
        this->_components.push_back(node);
        this->saveBottomY(node);
    }
}

void GUIDisplayVisitor::finish()
{
    //for (map<int, int>::iterator it = this->_maxWidthLevelMap.begin(); it != this->_maxWidthLevelMap.end(); it++)
    //    cout << it->first << ": " << it->second << endl;
    for (vector<Component*>::reverse_iterator iNode = this->_components.rbegin(); iNode != this->_components.rend(); iNode++)
    {
        Component* node = (*iNode);
        node->setPosition(this->getLevelX(node->getLevel()), node->getY());
        node->draw(this->_painter);
    }
}

void GUIDisplayVisitor::saveBottomY(Component* node)
{
    int newY = node->getY() + node->getHeight() / 2 + OUTTER_Y_PADDING;
    int* nowY = this->getNowY(node);
    if (newY > *nowY)
        *nowY = newY;
    this->_yLevelMap[node->getLevel()] = *nowY;
}

int GUIDisplayVisitor::getLevelBottomY(int level)
{
    return this->_yLevelMap[level];
}

void GUIDisplayVisitor::saveLevelMaxWidth(int level, int width)
{
    if (this->_maxWidthLevelMap[level] < width)
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