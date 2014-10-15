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

Component* ComponentFactory::createComponent(int type)
{
    Component* component = NULL;
    switch (type)
    {
        case ROOT:
            _createId = 0;
            component = new Root(_createId);
            break;
        case NODE:
            component = new Node(_createId);
            break;
    }
    _createId++;
    return component;
}

void ComponentFactory::revertCreateId()
{
    _createId--;
}

int ComponentFactory::getCreatedCount()
{
    return _createId;
}

ComponentFactory::~ComponentFactory()
{
}