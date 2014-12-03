#include "stdafx.h"
#include "Node.h"

Node::Node(int id, string description) : Composite(id, description)
{
    _typeName = "Node";
    setParent(NULL);
}

Component* Node::getParent()
{
    return _parentNode;
}

void Node::setParent(Component* node)
{
    _parentNode = node;
}

void Node::addParent(Component* node)
{
    if (node != NULL)
    {
        Component* parent = this->_parentNode;
        parent->addChild(node, this);
        parent->removeChild(this);
        node->addChild(this);
    }
}

void Node::addSibling(Component* node)
{
    if (node != NULL)
    {
        Component* parent = this->_parentNode;
        parent->addChild(node, this);
    }
}

bool Node::isSelfAreParentLastNode()
{
    Component* parent = this->_parentNode;
    NodeList* nodeList = parent->getNodeList();
    return nodeList->back()->getId() == this->getId();
}

Node::~Node()
{
}