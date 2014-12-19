#include "stdafx.h"
#include "Component.h"
#include "ComponentFactory.h"
#include <math.h>
#include <iostream>

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
    cout << description << ", size: " << description.size() << endl;
    _width = description.size() * CHAR_WIDTH;
    _height = CHAR_HEIGHT;
    if (_width > MAX_WIDTH_SIZE)
    {
        _height = ceil(float(_width) / float(MAX_WIDTH_SIZE)) * CHAR_HEIGHT;
        _width = MAX_WIDTH_SIZE;
    }
}

int Component::getWidth()
{
    return _width;
}

int Component::getHeight()
{
    return _height;
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