#pragma once
#include "Decorate.h"

class Triangle : public Decorate
{
    public:
        Triangle(int id, Component* node);
        Component* clone();
        string getTypeName();
        void draw(IGraphic* painter);
        ~Triangle();
};