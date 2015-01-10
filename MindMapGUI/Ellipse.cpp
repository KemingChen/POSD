#include "Ellipse.h"

Ellipse::Ellipse(int id, Component* node) : Decorate(id, node)
{
}

Component* Ellipse::clone()
{
    return NULL;
}

string Ellipse::getTypeName()
{
    return "Ellipse";
}

void Ellipse::accept(NodeVisitor* visitor)
{
}

void Ellipse::draw(IGraphic* painter)
{
}

Ellipse::~Ellipse()
{
}