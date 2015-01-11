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
    return this->_rect.getX();
}

int Component::getY()
{
    return this->_rect.getY();
}

void Component::setPosition(int x, int y)
{
    this->_rect.setPosition(x, y);
}

int Component::getWidth()
{
    return this->_rect.getWidth();
}

int Component::getHeight()
{
    return this->_rect.getHeight();
}

void Component::setRectSize(int width, int height)
{
    this->_rect.setSize(width < MAX_WIDTH ? width : MAX_WIDTH, height);
}

Rect Component::getBoundingRect()
{
    Rect rect = this->_rect;
    rect.setX(rect.getX() - rect.getWidth() / 2);
    rect.setY(rect.getY() - rect.getHeight() / 2);
    return rect;
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

Component* Component::getBackFromNode()
{
    NodeList* nodeList = this->getParent()->getNodeList();
    NodeList::iterator it = find(nodeList->begin(), nodeList->end(), this);
    if (it == nodeList->end())
        return NULL;
    if (it == nodeList->begin())
        return this;
    return *(it - 1);
}

Component::~Component()
{
}