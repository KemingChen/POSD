#include "stdafx.h"
#include "Composite.h"

Composite::Composite(int id, string description) : Component(id, description)
{
}

void Composite::addChild(Component* node)
{
    if (node != NULL)
    {
        node->setParent(this);
        _nodeList.push_back(node);
        _nodeList.sort(CompareComponent());
    }
}

void Composite::removeChild(Component* node)
{
    _nodeList.remove(node);
}

void Composite::removeAllChild()
{
    _nodeList.clear();
}

NodeList* Composite::getNodeList()
{
    return &_nodeList;
}

string Composite::getMap()
{
    string idsMap = "";
    for (NodeList::iterator it = _nodeList.begin(); it != _nodeList.end(); it++)
    {
        idsMap += " " + (*it)->getId();
    }
    return idsMap;
}

Composite::~Composite()
{
}