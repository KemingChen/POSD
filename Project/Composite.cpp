#include "stdafx.h"
#include "Composite.h"

Composite::Composite(int id) : Component(id)
{
}

void Composite::addChild(Component* node)
{
    node->setParent(this);
    _nodeList.push_back(node);
}

void Composite::removeChild(Component* node)
{
    _nodeList.remove(node);
}

NodeList* Composite::getNodeList()
{
    return &_nodeList;
}

list<int>* Composite::getMap()
{
    list<int>* intList = new list<int>();
    for (NodeList::iterator it = _nodeList.begin(); it != _nodeList.end(); it++)
    {
        intList->push_back(atoi((*it)->getId().c_str()));
    }
    return intList;
}

Composite::~Composite()
{
}
