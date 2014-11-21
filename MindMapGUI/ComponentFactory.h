#pragma once
#include "Component.h"

class ComponentFactory
{
    private:
        int _createId;
        ComponentFactory();

    public:
        static ComponentFactory* getInstance();
        Component* createComponent(int type, string description);
        ~ComponentFactory();
};