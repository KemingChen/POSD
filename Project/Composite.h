#pragma once
#include "Component.h"

class Composite :
    public Component
{
    protected:
        // Protected Variable
        string _type;

    public:
        // Public Method
        Composite();
        virtual ~Composite();
};

