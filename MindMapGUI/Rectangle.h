#pragma once
#include "Decorate.h"

class Rectangle : public Decorate
{
    public:
        Rectangle(int id, Component* node);
        Component* clone();
        string getTypeName();
        void draw(IGraphic* painter);
        ~Rectangle();
};