#include "stdafx.h"
#include "ComponentFactory.h"
#include "Root.h"
#include "Node.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Ellipse.h"

ComponentFactory::ComponentFactory()
{
}

ComponentFactory* ComponentFactory::getInstance()
{
    static ComponentFactory factoryInstance;
    return &factoryInstance;
}

Component* ComponentFactory::createComponent(ComponentType type, string description)
{
    Component* component = NULL;
    switch (type)
    {
        case ComponentType::ROOT:
            this->_createId = 0;
            component = new Root(this->_createId, description);
            break;
        case ComponentType::NODE:
            component = new Node(this->_createId, description);
            break;
    }
    this->_createId++;
    return component;
}

Component* ComponentFactory::createDecorate(ComponentType type, Component* node)
{
    Component* component = NULL;
    switch (type)
    {
        case ComponentType::ELLIPSE:
            component = new Ellipse(node->getId(), node);
            break;
        case ComponentType::TRIANGLE:
            component = new Triangle(node->getId(), node);
            break;
        case ComponentType::RECTANGLE:
            component = new Rectangle(node->getId(), node);
            break;
    }
    return component;
}

ComponentFactory::~ComponentFactory()
{
}