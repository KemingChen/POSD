#include "stdafx.h"
#include "Root.h"

Root::Root(int id, string description) : Composite(id)
{
    _typeName = "Root";
    _description = description;
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