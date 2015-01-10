#pragma once
#include "Decorate.h"

class Triangle : public Decorate
{
    public:
        Triangle(int id, Component* node);
        Component* clone();
        string getTypeName();
        void accept(NodeVisitor* visitor);
        void draw(IGraphic* painter);
        ~Triangle();
};