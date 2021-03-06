#pragma once
#include "Component.h"

class ComponentFactory
{
    private:
        int _createId;
        ComponentFactory();

    public:
        static ComponentFactory* getInstance();
        Component* createComponent(ComponentType type, string description);
        Component* createDecorate(ComponentType type, Component* node);
        Component* createDecorate(string type, Component* node);
        ~ComponentFactory();
};