#include "GUIDisplayVisitor.h"
#include <iostream>
#include <algorithm>
#include "Root.h"
#include "Node.h"
using namespace std;

#define LEVEL_X_WIDTH 120
#define OUTTER_PADDING 5

GUIDisplayVisitor::GUIDisplayVisitor()
{
    this->_yLeft = 0;
    this->_yRight = 0;
    this->_nowLevel = 0;
}

int GUIDisplayVisitor::calculateLevel(Component* node)
{
    return node->getLevel() * node->getSide();
}

void GUIDisplayVisitor::visit(Root* node)
{
    this->backupLastElementAndClean(&this->_nodeCollection);
    std::sort(this->_rootCollection.begin(), this->_rootCollection.end());
    int x = this->calculateLevel(node) * LEVEL_X_WIDTH;
    int y = this->averageCollection(&this->_rootCollection);
    node->setPosition(x, y);
    this->_rootCollection.clear();
}

void GUIDisplayVisitor::visit(Node* node)
{
    int* nowY = node->getSide() == RIGHT ? &this->_yRight : &this->_yLeft;
    int nowLevel = this->calculateLevel(node);

    int x = node->getSide() == RIGHT ? nowLevel * LEVEL_X_WIDTH : (nowLevel) * LEVEL_X_WIDTH + (MAX_WIDTH - node->getWidth());
    int y;
    if (this->_nowLevel == 0 || this->_nowLevel * nowLevel < 0 || abs(this->_nowLevel) <= abs(nowLevel))
    {
        y = *nowY + node->getHeight() / 2;
        *nowY += node->getHeight() / 2 + OUTTER_PADDING;
    }
    else
    {
        y = this->averageCollection(&this->_nodeCollection);
        this->_nodeCollection.clear();
    }

    if (this->_nowLevel != 0 && (this->_nowLevel * nowLevel < 0 || abs(this->_nowLevel) < abs(nowLevel)))
    {
        this->backupLastElementAndClean(&this->_nodeCollection);
    }

    node->setPosition(x, y);
    this->_nodeCollection.push_back(y);
    this->_nowLevel = nowLevel;

    int newY = y + node->getHeight() / 2 + OUTTER_PADDING;
    if (newY > *nowY)
        *nowY = newY;
}

int GUIDisplayVisitor::averageCollection(vector<int>* collection)
{
    if (collection->size() == 0)
        return 0;
    int sum = 0;
    sum += collection->front();
    sum += collection->back();
    return sum / 2;
}

void GUIDisplayVisitor::backupLastElementAndClean(vector<int>* collection)
{
    if (collection->size() == 0)
        return;
    this->_rootCollection.push_back(collection->back());
    collection->clear();
}

GUIDisplayVisitor::~GUIDisplayVisitor()
{
}