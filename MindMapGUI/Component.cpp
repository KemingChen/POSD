#include "stdafx.h"
#include "Component.h"

Component::Component(int id, string description)
{
    setId(id);
    setDescription(description);
}

string Component::getId()
{
    return _id;
}

void Component::setId(int id)
{
    _id = to_string(id);
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

string Component::toString()
{
    string output;
    output += "�ϡ� " + _description;
    output += " (" + _typeName + ", ID: " + _id + ")";
    return output;
}

Component::~Component()
{
}