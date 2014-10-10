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

string Component::getTypeName()
{
    return _node->getTypeName();
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

string Component::toString()
{
    return _node->toString();
}

Component::~Component()
{
}