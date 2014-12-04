#include "stdafx.h"
#include "Root.h"

Root::Root(int id, string description) : Composite(id, description)
{
    _type = ROOT;
    _typeName = "Root";
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

Root::~Root()
{
}