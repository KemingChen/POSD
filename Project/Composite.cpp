#include "stdafx.h"
#include "Composite.h"

Composite::Composite()
{
    _nodeList = new NodeList();
}

void Composite::addChild(Component* node)
{
    _nodeList->push_back(node);
}

NodeList* Composite::getNodeList()
{
    return _nodeList;
}

Composite::~Composite()
{
}
