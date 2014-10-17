#include "stdafx.h"
#include "Component.h"

Component::Component(int id)
{
    _id = to_string(id);
    _parentNode = NULL;
}

string Component::getId()
{
    return _id;
}

string Component::getTypeName()
{
    return _typeName;
}

string Component::getDescription()
{
    return _description;
}

void Component::setDescription(string description)
{
    _description = description;
}

void Component::setParent(Component* node)
{
    _parentNode = node;
}

Component* Component::getParent()
{
    return _parentNode;
}

string Component::toString()
{
    string output;
    output += "¡Ï¡Ð " + _description;
    output += " (" + _typeName + ", ID: " + _id + ")";
    return output;
}

Component::~Component()
{
}