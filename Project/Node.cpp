#include "stdafx.h"
#include "Node.h"

Node::Node(int id, string description) : Composite(id)
{
    _typeName = "Node";
    _description = description;
}

void Node::addParent(Component* node)
{
    if (node != NULL)
    {
        Component* parent = this->_parentNode;
        parent->removeChild(this);
        parent->addChild(node);
        node->addChild(this);
    }
}

void Node::addSibling(Component* node)
{
    if (node != NULL)
    {
        Component* parent = this->_parentNode;
        parent->addChild(node);
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