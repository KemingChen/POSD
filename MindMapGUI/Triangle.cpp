#include "Triangle.h"

Triangle::Triangle(int id, Component* node) : Decorate(id, node)
{
}

Component* Triangle::clone()
{
    return NULL;
}

string Triangle::getTypeName()
{
    return "Triangle";
}

void Triangle::accept(NodeVisitor* visitor)
{
}

void Triangle::draw(IGraphic* painter)
{
}

Triangle::~Triangle()
{
}