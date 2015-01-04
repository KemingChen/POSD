#include "GUIDisplayVisitor.h"
#include <iostream>
#include "Root.h"
#include "Node.h"
using namespace std;

#define LEVEL_X_WIDTH 120
#define OUTTER_PADDING 30

GUIDisplayVisitor::GUIDisplayVisitor()
{
    this->_yLeft = 0;
    this->_yRight = 0;
    this->_nowLevel = 0;
}

void GUIDisplayVisitor::visit(Root* node)
{
    cout << "now level: " << this->_nowLevel << endl;
    cout << "  " << node->getDescription() << ", " << node->getLevel() << endl;

    this->backupLastElementAndClean(&this->_nodeCollection);
    int x = node->getLevel() * LEVEL_X_WIDTH;
    int y = this->averageCollection(&this->_rootCollection);
    node->setPosition(x, y);
    this->_rootCollection.clear();
}

void GUIDisplayVisitor::visit(Node* node)
{
    cout << "now level: " << this->_nowLevel << endl;
    cout << "  " << node->getDescription() << ", " << node->getLevel() << endl;
    int x = node->getLevel() * LEVEL_X_WIDTH;
    int y;
    if (this->_nowLevel == 0 || this->_nowLevel <= node->getLevel())
    {
        y = this->_yRight;
        this->_yRight += node->getHeight() + OUTTER_PADDING;
        cout << "    y: " << y << endl;
    }
    else
    {
        y = this->averageCollection(&this->_nodeCollection);
        int newY = y + node->getHeight() + OUTTER_PADDING;
        cout << "    new y: " << newY << ", _yRight: " << this->_yRight << endl;
        if (newY > this->_yRight)
            this->_yRight = newY;
        this->_nodeCollection.clear();
    }
    if (this->_nowLevel != 0 && this->_nowLevel < node->getLevel())
    {
        this->backupLastElementAndClean(&this->_nodeCollection);
    }

    node->setPosition(x, y);
    this->_nodeCollection.push_back(y);
    this->_nowLevel = node->getLevel();
    cout << endl;
}

int GUIDisplayVisitor::averageCollection(vector<int>* collection)
{
    if (collection->size() == 0)
        return 0;
    int sum = 0;
    cout << "    avg" << endl;
    cout << "    " << collection->front() << endl;
    cout << "    " << collection->back() << endl;
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