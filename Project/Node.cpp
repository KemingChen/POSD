#include "stdafx.h"
#include "Node.h"
#include "ConstVariables.h"
#include <iostream>

Node::Node(int id) : Composite(id)
{
    _node->setNodeName(TYPE_NODE_NAME);
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

bool Node::isSelfAreParentLastNode()
{
    Component* parent = this->_parentNode;
    NodeList* nodeList = parent->getNodeList();
    return nodeList->back()->getId() == this->getId();
}

Node::~Node()
{
}