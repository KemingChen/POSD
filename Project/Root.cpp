#include "stdafx.h"
#include "Root.h"
#include "ConstVariables.h"

Root::Root(int id) : Composite(id)
{
    _node->setTypeName(TYPE_ROOT_NAME);
    _parentNode = NULL;
}

void Root::addParent(Component* node)
{
    throw string(ROOT_CANNOT_INSERT_PARENT);
}

void Root::addSibling(Component* node)
{
    throw string(ROOT_CANNOT_INSERT_SIBLING);
}

bool Root::isSelfAreParentLastNode()
{
    return true;
}

Root::~Root()
{
}