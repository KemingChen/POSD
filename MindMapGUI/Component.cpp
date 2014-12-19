#include "stdafx.h"
#include "Component.h"
#include "ComponentFactory.h"

Component::Component(int id, string description)
{
    setId(id);
    setDescription(description);
    _isSelected = false;
}

string Component::getId()
{
    return _id;
}

void Component::setId(int id)
{
    _id = to_string(id);
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
    output += "¡Ï¡Ð " + this->getDescription();
    output += " (" + this->getTypeName() + ", ID: " + this->getId() + ")";
    return output;
}

bool Component::getIsSelected()
{
    return _isSelected;
}

void Component::setIsSelected(bool value)
{
    _isSelected = value;
}

Component::~Component()
{
}