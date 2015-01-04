#include "stdafx.h"
#include "Component.h"
#include "ComponentFactory.h"
#include <math.h>
#include <iostream>

Component::Component(int id, string description)
{
    this->setId(id);
    this->setDescription(description);
    this->_isSelected = false;
}

string Component::getId()
{
    return this->_id;
}

void Component::setId(int id)
{
    this->_id = to_string(id);
}

string Component::getDescription()
{
    return this->_description;
}

void Component::setDescription(string description)
{
    this->_description = description;
}

int Component::getX()
{
    return this->_x;
}

int Component::getY()
{
    return this->_y;
}

void Component::setPosition(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

int Component::getWidth()
{
    return this->_width;
}

int Component::getHeight()
{
    return this->_height;
}

void Component::setRectSize(int width, int height)
{
    this->_width = width < MAX_WIDTH ? width : MAX_WIDTH;
    this->_height = height;
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
    return this->_isSelected;
}

void Component::setIsSelected(bool value)
{
    this->_isSelected = value;
}

int Component::getLevel()
{
    return this->_level;
}

void Component::setLevel(int level)
{
    this->_level = level;
}

int Component::getSide()
{
    return this->_side;
}

void Component::setSide(int side)
{
    this->_side = side;
    NodeList* nodeList = this->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        (*iNode)->setSide(side);
    }
}

Component::~Component()
{
}