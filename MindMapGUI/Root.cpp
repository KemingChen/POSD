#include "stdafx.h"
#include "Root.h"
#include "ComponentFactory.h"

Root::Root(int id, string description) : Composite(id, description)
{
}

Component* Root::getParent()
{
    return NULL;
}

void Root::setParent(Component* node)
{
    throw string("Root can't set parent node");
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
    Component* node = componentFactory->createComponent(ROOT, this->getDescription());
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

Root::~Root()
{
}