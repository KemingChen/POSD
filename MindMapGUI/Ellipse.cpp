#include "Ellipse.h"
#include "ComponentFactory.h"

Ellipse::Ellipse(int id, Component* node) : Decorate(id, node)
{
}

Component* Ellipse::clone()
{
    return ComponentFactory::getInstance()->createDecorate(ComponentType::ELLIPSE, this->_node->clone());
}

string Ellipse::getTypeName()
{
    return "Ellipse";
}

void Ellipse::draw(IGraphic* painter)
{
    painter->drawEllipse(this->getBoundingRect());
}

Ellipse::~Ellipse()
{
}