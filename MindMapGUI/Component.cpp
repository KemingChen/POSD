#include "stdafx.h"
#include "Component.h"
#include "ComponentFactory.h"

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
    output += "¡Ï¡Ð " + _description;
    output += " (" + _typeName + ", ID: " + _id + ")";
    return output;
}

Component* Component::clone()
{
    ComponentFactory* componentFactory = ComponentFactory::getInstance();
    Component* node = componentFactory->createComponent(NODE, _description);
    NodeList* nodeList;
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        node->addChild((*iNode)->clone());
    }
}

Component::~Component()
{
}