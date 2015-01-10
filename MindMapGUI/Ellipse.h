#pragma once
#include "Decorate.h"

class Ellipse : public Decorate
{
    public:
        Ellipse(int id, Component* node);
        Component* clone();
        string getTypeName();
        void draw(IGraphic* painter);
        ~Ellipse();
};