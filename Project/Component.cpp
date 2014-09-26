#include "stdafx.h"
#include "Component.h"

Component::Component()
{
}

void Component::setDescription(string description)
{
    _description = description;
}

string Component::getDescription()
{
    return _description;
}

Component::~Component()
{
}
