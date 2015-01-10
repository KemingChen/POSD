#include "Decorate.h"

Decorate::Decorate(int id, Component* node) : Component(id, node->getDescription())
{
    this->_node = node;
}

Component* Decorate::getBackFromNode()
{
    return this->_node->getBackFromNode();
}

string Decorate::getMap()
{
    return this->getId();
}

void Decorate::addChild(Component* node, Component* backFromNode, int side)
{
    this->_node->addChild(node, backFromNode, side);
}

void Decorate::removeChild(Component* node)
{
    this->_node->removeChild(node);
}

void Decorate::removeAllChild()
{
    this->_node->removeAllChild();
}

Component* Decorate::getParent()
{
    return this->_node->getParent();
}

void Decorate::setParent(Component* node)
{
    this->_node->setParent(node);
}

void Decorate::addParent(Component* node)
{
    this->_node->addParent(node);
}

void Decorate::addSibling(Component* node)
{
    this->_node->addSibling(node);
}

bool Decorate::isSelfAreParentLastNode()
{
    return this->_node->isSelfAreParentLastNode();
}

NodeList* Decorate::getNodeList()
{
    return this->_node->getNodeList();
}

Decorate::~Decorate()
{
}