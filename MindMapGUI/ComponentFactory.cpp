#include "stdafx.h"
#include "ComponentFactory.h"
#include "Root.h"
#include "Node.h"

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
            _createId = 0;
            component = new Root(_createId, description);
            break;
        case ComponentType::NODE:
            component = new Node(_createId, description);
            break;
    }
    _createId++;
    return component;
}

ComponentFactory::~ComponentFactory()
{
}