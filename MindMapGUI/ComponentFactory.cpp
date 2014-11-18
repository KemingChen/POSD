#include "stdafx.h"
#include "ComponentFactory.h"

ComponentFactory::ComponentFactory()
{
}

ComponentFactory* ComponentFactory::getInstance()
{
    static ComponentFactory factoryInstance;
    return &factoryInstance;
}

Component* ComponentFactory::createComponent(int type, string description)
{
    Component* component = NULL;
    switch (type)
    {
        case ROOT:
            _createId = 0;
            component = new Root(_createId, description);
            break;
        case NODE:
            component = new Node(_createId, description);
            break;
    }
    _createId++;
    return component;
}

ComponentFactory::~ComponentFactory()
{
}