#include "stdafx.h"
#include "Component.h"

Component::Component()
{
    static int createdId = 0;
    createdId += 1;
    _node = new NodeMap(createdId);
}

int Component::getId()
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

Component::~Component()
{
}