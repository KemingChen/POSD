#include "stdafx.h"
#include "Component.h"

Component::Component(int id)
{
    _node = new NodeMap(id);
}

string Component::getId()
{
    return _node->getId();
}

NodeMap* Component::getMap()
{
    return _node;
}

string Component::getDescription()
{
    return _node->getDescription();
}

void Component::setDescription(string description)
{
    _node->setDescription(description);
}

void Component::setParent(Component* node)
{
    _parentNode = node;
}

Component::~Component()
{
}