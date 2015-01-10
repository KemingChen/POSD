#include "Rectangle.h"

Rectangle::Rectangle(int id, Component* node) : Decorate(id, node)
{
}

Component* Rectangle::clone()
{
    return NULL;
}

string Rectangle::getTypeName()
{
    return "Rectangle";
}

void Rectangle::accept(NodeVisitor* visitor)
{
}

void Rectangle::draw(IGraphic* painter)
{
}

Rectangle::~Rectangle()
{
}