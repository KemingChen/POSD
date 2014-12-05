#include "stdafx.h"
#include "Composite.h"

Composite::Composite(int id, string description) : Component(id, description)
{
}

void Composite::addChild(Component* node, Component* backFromNode)
{
    if (node != NULL)
    {
        node->setParent(this);
        _nodeList.insert(_nodeList.begin() + childIndexOf(backFromNode), node);
    }
}

void Composite::removeChild(Component* node)
{
    _nodeList.erase(_nodeList.begin() + childIndexOf(node) - 1);
}

int Composite::childIndexOf(Component* node)
{
    if (node == NULL)
        return _nodeList.size();
    for (int i = 0; i < _nodeList.size(); i++)
    {
        if (_nodeList.at(i) == node)
        {
            return i + 1;
        }
    }
    return -1;
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
    for (NodeList::iterator iNode = _nodeList.begin(); iNode != _nodeList.end(); iNode++)
    {
        delete (*iNode);
    }
}
