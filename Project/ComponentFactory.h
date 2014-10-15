#pragma once
#include "Component.h"
#include "TypeConst.h"

class ComponentFactory
{
    private:
        int _createId;
        ComponentFactory();

    public:
        static ComponentFactory* getInstance();
        Component* createComponent(int type);
        void revertCreateId();
        int getCreatedCount();
        ~ComponentFactory();
};