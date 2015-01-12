#include "Rectangle.h"
#include "ComponentFactory.h"

Rectangle::Rectangle(int id, Component* node) : Decorate(id, node)
{
}

Component* Rectangle::clone()
{
    return ComponentFactory::getInstance()->createDecorate(ComponentType::RECTANGLE, this->_node->clone());
}

string Rectangle::getTypeName()
{
    return "Rectangle";
}

void Rectangle::draw(IGraphic* painter)
{
    painter->drawRectangle(this->getBoundingRect());
}

Rectangle::~Rectangle()
{
}