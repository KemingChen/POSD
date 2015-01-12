#include "Decorate.h"

Decorate::Decorate(int id, Component* node) : Component(id, node->getDescription())
{
    this->_node = node;
}

string Decorate::getMap()
{
    return SPLITE + to_string(this->getId());
}

void Decorate::setPosition(int x, int y)
{
    this->_rect.setPosition(x, y);
    this->getOriginalComponent()->setPosition(x + DECORATE_PADDING, y);
}

void Decorate::setRectSize(int width, int height)
{
    this->_rect.setSize(width + 2 * DECORATE_PADDING, height + 2 * DECORATE_PADDING);
}

void Decorate::addChild(Component* node, Component* backFromNode, int side)
{
    this->getOriginalComponent()->addChild(node, backFromNode, side);
}

void Decorate::removeChild(Component* node)
{
    this->getOriginalComponent()->removeChild(node);
}

void Decorate::removeAllChild()
{
    this->getOriginalComponent()->removeAllChild();
}

Component* Decorate::getParent()
{
    return this->getOriginalComponent()->getParent();
}

void Decorate::setParent(Component* node)
{
    this->getOriginalComponent()->setParent(node);
}

void Decorate::addParent(Component* node)
{
    this->getOriginalComponent()->addParent(node);
}

void Decorate::addSibling(Component* node)
{
    this->getOriginalComponent()->addSibling(node);
}

bool Decorate::isSelfAreParentLastNode()
{
    return this->getOriginalComponent()->isSelfAreParentLastNode();
}

NodeList* Decorate::getNodeList()
{
    return this->getOriginalComponent()->getNodeList();
}

void Decorate::accept(NodeVisitor* visitor)
{
    this->getOriginalComponent()->accept(visitor);
    this->setLevel(this->getOriginalComponent()->getLevel());
    visitor->visit(this);
}

void Decorate::setDescription(string description)
{
    this->_node->setDescription(description);
    Component::setDescription(description);
}

void Decorate::setLevel(int level)
{
    this->_node->setLevel(level);
    Component::setLevel(level);
}

void Decorate::setSide(int side)
{
    this->_node->setSide(side);
    Component::setSide(side);
}

Component* Decorate::getRealComponent()
{
    return this->getOriginalComponent()->getRealComponent();
}

Component* Decorate::getOriginalComponent()
{
    return this->_node;
}

Decorate::~Decorate()
{
}