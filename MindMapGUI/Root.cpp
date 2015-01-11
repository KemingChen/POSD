#include "stdafx.h"
#include "Root.h"
#include "ComponentFactory.h"
#include <iostream>

Root::Root(int id, string description) : Composite(id, description)
{
    this->setSide(NONE);
}

Component* Root::getParent()
{
    return NULL;
}

void Root::setParent(Component* node)
{
    throw string("Root can't set parent node");
}

int Root::getNextSide(int side)
{
    if (side == NONE)
    {
        int count = 0;
        NodeList* nodeList = this->getNodeList();
        for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
        {
            count += (*iNode)->getSide();
        }
        return count > 0 ? LEFT : RIGHT;
    }
    return side;
}

void Root::addChild(Component* node, Component* backFromNode, int side)
{
    if (node != NULL)
    {
        NodeList* nodeList = this->getNodeList();
        node->setParent(this);
        node->setSide(getNextSide(side));
        nodeList->insert(nodeList->begin() + childIndexOf(backFromNode), node);
    }
}

void Root::addParent(Component* node)
{
    throw string("Root can't insert parent node");
}

void Root::addSibling(Component* node)
{
    throw string("Root can't insert sibling node");
}

bool Root::isSelfAreParentLastNode()
{
    return true;
}

Component* Root::clone()
{
    ComponentFactory* componentFactory = ComponentFactory::getInstance();
    Component* node = componentFactory->createComponent(ComponentType::ROOT, this->getDescription());
    NodeList* nodeList = this->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        node->addChild((*iNode)->clone());
    }
    return node;
}

string Root::getTypeName()
{
    return "Root";
}

Component* Root::getBackFromNode()
{
    return this;
}

void Root::accept(NodeVisitor* visitor)
{
    NodeList* nodeList = this->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        Component* node = (*iNode);
        node->setLevel(node->getSide());
        node->accept(visitor);
    }
    this->setLevel(0);
    visitor->visit(this);
}

void Root::draw(IGraphic* painter)
{
    painter->drawNode(this);
    painter->drawEllipse(this->getBoundingRect());
}

Root::~Root()
{
}