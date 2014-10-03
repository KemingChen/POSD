#include "stdafx.h"
#include "Composite.h"

Composite::Composite()
{
    _nodeList = new NodeList();
}

void Composite::addChild(Component* node)
{
    node->setParent(node);
    _nodeList->push_back(node);
}

void Composite::removeChild(Component* node)
{
    _nodeList->remove(node);
}

NodeList* Composite::getNodeList()
{
    return _nodeList;
}

Composite::~Composite()
{
}
