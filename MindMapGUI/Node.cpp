#include "stdafx.h"
#include "Node.h"
#include "ComponentFactory.h"
#include <algorithm>
#include <iostream>

Node::Node(int id, string description) : Composite(id, description)
{
    setParent(NULL);
    this->setSide(NONE);
}

Component* Node::getParent()
{
    return _parentNode;
}

void Node::setParent(Component* node)
{
    _parentNode = node;
}

void Node::addChild(Component* node, Component* backFromNode, int side)
{
    if (node != NULL)
    {
        NodeList* nodeList = this->getNodeList();
        node->setParent(this);
        node->setSide(this->getSide());
        nodeList->insert(nodeList->begin() + childIndexOf(backFromNode), node);
    }
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

Component* Node::clone()
{
    ComponentFactory* componentFactory = ComponentFactory::getInstance();
    Component* node = componentFactory->createComponent(NODE, this->getDescription());
    NodeList* nodeList = this->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        node->addChild((*iNode)->clone());
    }
    return node;
}

string Node::getTypeName()
{
    return "Node";
}

Component* Node::getBackFromNode()
{
    NodeList* nodeList = _parentNode->getNodeList();
    NodeList::iterator it = find(nodeList->begin(), nodeList->end(), this);
    if (it == nodeList->end())
        return NULL;
    if (it == nodeList->begin())
        return this;
    return *(it - 1);
}

void Node::accept(NodeVisitor* visitor)
{
    NodeList* nodeList = this->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        (*iNode)->setLevel(this->getLevel() + 1);
        (*iNode)->accept(visitor);
    }
    visitor->visit(this);
}

void Node::draw(IGraphic* painter)
{
    painter->drawGraphicNode(this);
}

Node::~Node()
{
}