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
        Component* selfNode = this->findSelfFromParent();
        parent->addChild(node, selfNode, selfNode->getSide());
        parent->removeChild(selfNode);
        node->addChild(selfNode);
    }
}

Component* Node::findSelfFromParent()
{
    Component* parentNode = this->getParent();
    if (parentNode)
    {
        NodeList* nodeList = parentNode->getNodeList();
        for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
        {
            if ((*iNode)->getId() == this->getId())
                return (*iNode);
        }
    }
    return NULL;
}

void Node::addSibling(Component* node)
{
    if (node != NULL)
    {
        Component* parent = this->_parentNode;
        parent->addChild(node, this, this->getSide());
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
    Component* node = componentFactory->createComponent(ComponentType::NODE, this->getDescription());
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

void Node::accept(NodeVisitor* visitor)
{
    NodeList* nodeList = this->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        Component* node = (*iNode);
        node->setLevel(this->getLevel() + this->getSide());
        node->accept(visitor);
    }
    visitor->visit(this);
}

void Node::draw(IGraphic* painter)
{
    painter->drawNode(this);
    painter->drawRectangle(this->getBoundingRect());
}

Node::~Node()
{
}