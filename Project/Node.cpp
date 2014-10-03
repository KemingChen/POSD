#include "stdafx.h"
#include "Node.h"
#include "ConstVariables.h"

Node::Node(Component* node)
{
    _node->setNodeName(TYPE_NODE_NAME);
    _parentNode = node;
}

void Node::addParent(Component* node)
{
    Component* parent = this->_parentNode;
    parent->removeChild(this);
    parent->addChild(node);
    node->addChild(this);
}

void Node::addSibling(Component* node)
{
    Component* parent = this->_parentNode;
    parent->addChild(node);
}

Node::~Node()
{
}