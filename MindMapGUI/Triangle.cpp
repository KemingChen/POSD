#include "Triangle.h"
#include "ComponentFactory.h"

Triangle::Triangle(int id, Component* node) : Decorate(id, node)
{
}

Component* Triangle::clone()
{
    return ComponentFactory::getInstance()->createDecorate(ComponentType::ELLIPSE, this->_node->clone());
}

string Triangle::getTypeName()
{
    return "Triangle";
}

void Triangle::draw(IGraphic* painter)
{
    painter->drawTriangle(this->getBoundingRect());
}

Triangle::~Triangle()
{
}